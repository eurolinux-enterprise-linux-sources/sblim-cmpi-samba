/*
 * smt_smb_ra_support.c
 *
 * (C) Copyright IBM Corp. 2005
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Eclipse Public License from
 * http://www.opensource.org/licenses/eclipse-1.0.php
 *
 * Author:  Rodrigo Ceron <rceron@br.ibm.com>
 *
 * Contributors:
 *
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "smt_smb_ra_support.h"
#include "smt_smb_ra_path.h"
#include <sblim/smt_libra_execscripts.h>
#include <sblim/smt_libra_conf.h>
#include <sblim/smt_libra_rastr.h>
#include <sblim/smt_libra_monitors.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <dirent.h>

#define SCRIPT_NAME __FUNCTION__

/* fall back values */
#define SMB_DEF  "/etc/init.d/smb"
#define SMBD_PROC "/usr/sbin/smbd"
#define CACHE_DFL 10
#define USERMAP_DFL "/etc/samba/smbusers"

#ifndef CONFFILE
#define CONFFILE "/etc/smt_smb_ra_support.conf"
#endif

extern int errno;

extern struct conf *smb_conf;
extern struct monitor *services_list_monitor;
extern struct monitor *usermap_file_monitor;
extern struct monitor *groupmap_file_monitor;

extern struct smbopt *synonyms;
extern struct smbopt *defaults;
extern char **global_services_list;
extern char **global_shares_list;
extern char **global_printers_list;
extern char **global_samba_users_list;
extern char **global_system_users_list;
extern char **global_samba_groups_list;
extern char **global_system_groups_list;
extern char **cups_printers_list;
extern char *global_overrides[];


extern pthread_mutex_t glob_mutex;
extern pthread_mutex_t services_list_mutex;
extern pthread_mutex_t shares_list_mutex;
extern pthread_mutex_t printers_list_mutex;
extern pthread_mutex_t samba_users_list_mutex;
extern pthread_mutex_t system_users_list_mutex;
extern pthread_mutex_t samba_groups_list_mutex;
extern pthread_mutex_t system_groups_list_mutex;
extern pthread_mutex_t cups_printers_list_mutex;


/* This variable is an auxiliary variable in order not to leak memory */
extern char **user_groups;

extern struct smbcache monitors_cache;
extern struct smbcache usermap_cache;
extern struct smbcache groupmap_cache;

static char *__get_option(const char *share, const char *opt);
static int __set_option(const char *share, const char *key, const char *value);
static int create_service(const char* service);

/* Helper functions */

void free_smbopt_list(struct smbopt *list){
  
  struct smbopt *next;

  while(list){
    next = list->next;
    free(list->key);
    free(list->value);
    free(list);
    list = next;
  }
}


static char *my_script_path(char *script){

  if (!smb_conf)
    smb_conf = read_conf(CONFFILE,CONFFILE);
  return script_path(smb_conf,script);
  
}


static inline int may_override(const char *key){

  int i;
  for (i = 0; global_overrides[i] ; i++)
    if (!strcasecmp(key,global_overrides[i]))
      return 1;
  return 0;
}


static char **add_string_array(char **array, const char *elem){

  int i = 0;

  if (!array){
    array = (char**) realloc(array,(1)*sizeof(char*));
    array[0] = NULL;
  }

  while ( array[i++] );
  
  array = (char**) realloc(array,(i+1)*sizeof(char*));
  if (!array){
    errno = -ENOMEM;
    return NULL;
  }
  
  array[i-1] = strdup(elem);
  if (!array[i-1]){
    errno = -ENOMEM;
    free_string_array(array);
  }

  array[i] = NULL;
  return array;
}


static char **remove_string_array(char **array, const char *name){
  int current = 0;
  int last    = 0;
  int count   = 0;

  if (!array) return NULL;
  if (!name) return array;

  while(array[current]) {
    if ( !strcasecmp(array[current],name) ) {
      free(array[current]);
      count++;
    } else {
      if (last != current) {
        if (array[current]!= NULL) {
          array[last]=strdup(array[current]);
        } else {
          array[last]=NULL;
        }
      }
      last++;
    }
    current++;
  }
  
  array[++last] = NULL;
  /* We need one more element for terminating NULL */
  array = (char**) realloc(array, ((current+1)-count)*sizeof(char*));

  return array;
}


static int __create_path(const char *path){

  char built_path[PATH_MAX], *cur_dir, *mpath = (char*) path;
  int ret=0;
  DIR* shareDirectory;

  strcpy(built_path,"/");

  while (mpath) {
    cur_dir = strsep(&mpath,"/");
    
    if( strlen(cur_dir) ) {
      strcat(built_path,"/");
      strcat(built_path,cur_dir);

      if ((shareDirectory=opendir(built_path))==NULL) {
	return mkdir(built_path,0755);
      } else {
        closedir(shareDirectory);
      }
    }
  }

  return ret;
}


static int __check_path(const char *path){

  struct stat status;
  char *samba_root = __get_option(GLOBAL,ROOT_DIR), *abs_path=NULL;
  char *root_path = NULL;
  int ret = 0;

  if(samba_root)
    asprintf(&root_path,"%s/%s",samba_root,path);
  else
    asprintf(&root_path,"/%s",path);

  abs_path = (char *) limited_canonicalize_path(root_path);
                      
  ret = stat(abs_path,&status);
  if (!ret) goto out; /* path exists */
  
  if (errno == ENOENT )  
    ret = __create_path(abs_path);
  
 out:
  free(root_path);
  free(abs_path);
  return ret;
}


static int start_monitor(struct monitor **monitor, char *filename){

  *monitor = init_monitor(1);
  monitor_file(*monitor,filename);

  return 0;
}


static void free_monitors_cache(struct smbcache *cache){

  struct smbmonitors *tmp, *monitor = (struct smbmonitors*) cache->content;
    
  while (monitor){
    free(monitor->service);
    free_smbopt_list(monitor->opts);
    tmp = monitor;
    monitor = monitor->next;
    free(tmp);
  }

  if (cache->thread_running){
    pthread_cancel(cache->thread);
    pthread_join(cache->thread,NULL);
    cache->thread_running = 0;
  }
  cache->content = NULL;
}


static void free_map_cache(struct smbcache *cache){
  
  struct smbopt *pp, *p = (struct smbopt*) cache->content;

  while(p){
    pp = p;
    free(p->key);
    free(p->value);
    p = p->next;
    free(pp);
  }

  if (cache->thread_running){
    pthread_cancel(cache->thread);
    pthread_join(cache->thread,NULL);
    cache->thread_running = 0;
  }
  cache->content = NULL;
}

static struct smbopt *__create_smbopt(const char *key, const char *value){
  
  struct smbopt *opt = (struct smbopt *) malloc ( sizeof(struct smbopt) );

  if (opt){
    opt->key = strdup(key);
    opt->value = strdup(value);
    if ( !opt->key || !opt->value ){
      free(opt->key); free(opt->value); free(opt);
      opt = NULL;
      errno = -ENOMEM;
    } 
  }

  return opt;
}


static struct smbopt *g_synonyms(int pipefd){

  char *chr, *buf, *buf_ptr = malloc(1024);
  char *official, *syn;
  struct smbopt *head = NULL, *synonym = NULL;
  FILE *fp = fdopen(pipefd,"r");

  struct timeval tv = {2,0};
  fd_set fset;

  FD_ZERO(&fset);
  FD_SET(fileno(fp),&fset);

  if (!select(fileno(fp)+1,&fset,NULL,NULL,&tv)){
    errno = -EAGAIN;
    goto out;
  }

  while(!feof(fp)){
    buf = buf_ptr;
    buf=fgets(buf,1024,fp);

    if (!buf || !strncmp(buf,"EOF",3)) break;
    chr = strrchr(buf,'\n');
    if (chr) *chr = '\0';

    /* here we face a line which has at least two values separated by ";". The
     * first one is the official option name; the others are synonims to it */

    official = strsep(&buf,",;");

    /*synonyms entries */
    for(syn = strsep(&buf,",;"); syn; syn=strsep(&buf,",;")){
      if (!strcasecmp(syn,official)) continue;
      synonym = (struct smbopt*) malloc(sizeof(struct smbopt));
      synonym->key = strdup(syn);
      synonym->value = strdup(official);
      if (!head){
	head = synonym;
	head->next = NULL;
      }else
	list_add(head,synonym);
    }

  }
  
  out:
  free(buf_ptr);
  fclose(fp);
  //close(pipefd);
  return head;
}


static struct smbopt *get_synonyms_array(){

  char *script = my_script_path("smt_smb_ra_get_synonyms.py");
  char *filename = get_conf(smb_conf,SMBSYNONYMS);

  struct smbopt *syn = (struct smbopt*) readData1(script,filename,(void*)g_synonyms);

  free(script);
  free(filename);

  return syn;
}


static struct smbopt *g_map(int pipefd){

  char *chr, *buf, *buf_ptr = malloc(1024);
  char *smb, *sys;
  struct smbopt *head = NULL, *map = NULL;
  FILE *fp = fdopen(pipefd,"r");

  struct timeval tv = {2,0};
  fd_set fset;

  FD_ZERO(&fset);
  FD_SET(fileno(fp),&fset);

  if (!select(fileno(fp)+1,&fset,NULL,NULL,&tv)){
    errno = -EAGAIN;
    goto out;
  }

  while(!feof(fp)){
    buf = buf_ptr;
    buf=fgets(buf,1024,fp);

    if (!buf || !strncmp(buf,"EOF",3)) break;
    chr = strrchr(buf,'\n');
    if (chr) *chr = '\0';

    /* here we face a line which has at least two values separated by ";". The
     * first one is the official option name; the others are synonims to it */

    smb = strsep(&buf,",;");

    /*synonyms entries */
    sys = strsep(&buf,",;");
    map = (struct smbopt*) malloc(sizeof(struct smbopt));
    map->key = strdup(smb);
    map->value = strdup(sys);
    if (!head){
      head = map;
      head->next = NULL;
    }else
      list_add(head,map); 
  }
  
  out:
  free(buf_ptr);
  fclose(fp);
  //close(pipefd);
  return head;

}


static char *get_official_name(const char *syn){
  /* Checks the synonym list and returns the official name of the option. If no
   * entry is found in the list, we return the name passed as argument */
  
  struct smbopt *synlist;

  if (!synonyms) synonyms = (struct smbopt*) get_synonyms_array();
  
  synlist = synonyms;
  while(synlist){
    if (!strcasecmp(syn,synlist->key)) return synlist->value;
    synlist = synlist->next;
  }
  
  return (char*) syn;
}


static struct smbopt *g_service(FILE *fp){

  char *chr;
  char *buf,*buf_ptr = malloc(1024);
  struct smbopt *share_opts,*head = NULL;
  
  if (!fp)
    return NULL;
  
  head = NULL;

  while (!feof(fp)){
    buf = buf_ptr;
    buf=fgets(buf,1024,fp);
    if (!buf || !strncmp(buf,"ENDSHARE",8))
      break;
    
    chr = strrchr(buf,';');
    if (!chr)
      break;
    chr = strrchr(buf,'\n');
    if (chr)
      *chr = '\0';
    
    if (!head){
      head = (struct smbopt*)malloc(sizeof(struct smbopt));
      head->key = strdup(get_official_name(strsep(&buf,";")));
      head->value = strdup(buf);
      head->next = NULL;
    }
    else{
      share_opts = (struct smbopt*)malloc(sizeof(struct smbopt));
      share_opts->key = strdup( get_official_name(strsep(&buf,";")) );
      share_opts->value = strdup(buf);
      share_opts->next = NULL;
      list_add(head,share_opts);
    }
  }
  free(buf_ptr);
  return head; 
}


struct smbmonitors *g_cache_info(int pipefd){

  struct smbmonitors *mon,*elem;
  char *chr,*buf,*buf_ptr = malloc(1024);
  FILE *fp = fdopen(pipefd,"r");
  
  struct timeval tv = {2,0};
  fd_set fset;
  
  mon = NULL;
  FD_ZERO(&fset);
  FD_SET(fileno(fp),&fset);

  if (!select(fileno(fp)+1,&fset,NULL,NULL,&tv)){
    errno = -EAGAIN;
    goto out;
  }

  while (!feof(fp)){
    buf = buf_ptr;
    buf = fgets(buf,1024,fp);
    
    if (!buf || !strncmp(buf,"SMBEOF",6))
      break;
    chr = strrchr(buf,'\n');
    if (chr)
      *chr = '\0';
    
    /* There are 2 cases to handle here. In the first, we do not find a 
     * semicolon in the line. It means we're in front of a sharename. Store it.
     * If it's not the case, call a helper function to fill the linked list */

    chr = strchr(buf,';'); 
    if (!chr){
      elem = (struct smbmonitors *)malloc(sizeof(struct smbmonitors));
      elem->service = strdup(buf);
      elem->opts = g_service(fp);
      elem->next = NULL;
      if (!mon)
	mon = elem;
      else
	list_add(mon,elem);
    }
  }
  
 out:
  free(buf_ptr);
  fclose(fp);
  //close(pipefd);
  return mon;
}


static struct smbopt *g_defaults(int pipefd){

  struct smbopt *opts = NULL;
  char *chr,*buf,*buf_ptr = malloc(1024);
  FILE *fp = fdopen(pipefd,"r");
    
  struct timeval tv = {2,0};
  fd_set fset;

  FD_ZERO(&fset);
  FD_SET(fileno(fp),&fset);

  if (!select(fileno(fp)+1,&fset,NULL,NULL,&tv)){
    errno = -EAGAIN;
    goto out;
  }

  while (!feof(fp)){
    buf = buf_ptr;
    buf=fgets(buf,1024,fp);
    
    if (!buf || !strncmp(buf,"SMBEOF",6))
      break;
    chr = strrchr(buf,'\n');
    if (chr)
      *chr = '\0';
    
    /* There are 2 cases to handle here. In the first, we do not find a 
     * semicolon in the line. It means we're in front of a "sharename". The 
     * share name was put into the defaults file in order to reuse the scripts
     * that already existed to read a file with that structure; we just Ignore 
     * the share name. If it's not the case, call a helper function to fill the
     * linked list */

    chr = strchr(buf,';'); 
    if (!chr)
      opts = g_service(fp);
  } 
  
 out:
  free(buf_ptr);
  fclose(fp);
  //close(pipefd);
  return opts;
}


static void *g_single_val_per_line_list(int pipefd){

  char *buf, *buf_ptr = malloc(1024);
  char **list = (char **)malloc(sizeof(char *));
  int i=0;
  FILE *fp = fdopen(pipefd,"r");
    
  struct timeval tv = {2,0};
  fd_set fset;
  
  if (!fp) goto out;
  
  FD_ZERO(&fset);
  FD_SET(fileno(fp),&fset);
  if (!select(fileno(fp)+1,&fset,NULL,NULL,&tv)){
    errno = -EAGAIN;
    goto out;
  }
 
  while (!feof(fp)){
    buf=buf_ptr;
    buf=fgets(buf,1024,fp);
    if (!buf || !strncmp(buf,"EOF",3))
      break;
    list = realloc(list,(i+2)*sizeof(char *));
    list[i++] = strip(buf);
  }

 out:
  list[i] = NULL;
  free(buf_ptr);
  fclose(fp);
  //close(pipefd);
  return (void *) list; 
}


static void f_cache(int pipefd){

  struct smbopt *opt = NULL;
  struct smbmonitors *service = (struct smbmonitors*) monitors_cache.content;
  FILE *fp = fdopen(pipefd,"w");
  char buf[1024];

  if (!monitors_cache.content || !monitors_cache.is_dirty) return;

  while(service){
    sprintf(buf,"[%s]\n",service->service);
    fputs(buf,fp);
    opt = service->opts;
    for(; opt; opt = opt->next ){
      sprintf(buf,"\t%s = %s\n",opt->key,opt->value);
      fputs(buf,fp);
    }
    service = service->next;
  }  
  fclose(fp);
  //close(pipefd);
}


static void f_usermap_cache(int pipefd){

  struct smbopt *p = (struct smbopt*) usermap_cache.content;
  FILE *fp = fdopen(pipefd,"w");
  char buf[1024];

  while(p){
    sprintf(buf,"%s=%s\n",p->key,p->value);
    fputs(buf,fp);
    p = p->next;
  }
  sprintf(buf,"EOF\n");  /*need this or pipe reader will block */
  fputs(buf,fp);
  fclose(fp);
  //close(pipefd);
}


/*
static void f_groupmap_cache(int pipefd){

  struct smbopt *p = (struct smbopt*) groupmap_cache.content;
  FILE *fp = fdopen(pipefd,"w");
  char buf[1024];

  while(p){
    sprintf(buf,"%s=%s\n",p->key,p->value);
    fputs(buf,fp);
    p = p->next;
  }
  fclose(fp);
  //close(pipefd);
}
*/

static int flush_usermap_cache(){
  /* It's easier to use python to put the usermap file back in order */
 
  char *script = my_script_path("smt_smb_ra_set_user_mappings.py");
  int ret = 0;

  if (!usermap_cache.content || !usermap_cache.is_dirty) goto out;
  
  if (writeData1(script,__get_option(GLOBAL,USERNAME_MAP),f_usermap_cache))
    ret = -1;
  
  /* the file has changed on disk because we wrote to it. Check and ignore */
  check_events(usermap_file_monitor);
  usermap_cache.is_dirty = 0;
  
 out:
  free(script);
  return ret;
}


static int flush_smb_cache() {
  /* Here we simply flush the entire cache overwriting the file. We don't
   * use external scripts here because doing so would only bring overhead in
   * this simple case. Returns zero on success */

  int fd;
  char *filename;

  if (!monitors_cache.content || !monitors_cache.is_dirty) return 0;

  if (!smb_conf) smb_conf = read_conf(CONFFILE,CONFFILE);
  filename = get_conf(smb_conf,SMBCONF);

  fd = open(filename,O_WRONLY);
  free(filename);
  if (fd==-1) return errno;
  if ( ftruncate(fd,0) ) return errno;

  f_cache(fd);
  close(fd);

  /* the file has changed on disk because we wrote to it. Check and ignore */
  check_events(services_list_monitor);
  monitors_cache.is_dirty = 0;

  return 0;
}


static void *usermap_cache_flusher(void *arg){
  /* This function is to be used as a thread. We expect a (smbcache*) as
   * argument */ 

  struct smbcache *cache = (struct smbcache*) arg;
  int ret=0, cache_flush_interval;
  char *tmp;

  if (!smb_conf) smb_conf = read_conf(CONFFILE,CONFFILE);
  tmp = get_conf(smb_conf,CACHE_IVAL);
  if (tmp){
    cache_flush_interval = strtol(tmp,NULL,10);
    free(tmp);
  }else
    cache_flush_interval = CACHE_DFL;
  
  printf("Using cache interval of %d for usermap\n",cache_flush_interval);

  while(1){
    pthread_testcancel();
    if (cache->content){
      if (pthread_mutex_trylock(&(cache->mutex)))
	continue;
      ret = flush_usermap_cache(cache);
      if (ret) printf("[!!] Could not flush cache\n");
      pthread_mutex_unlock(&(cache->mutex));
      pthread_testcancel();
    }
    sleep(cache_flush_interval);
  }
}


static void *smb_cache_flusher(void *arg){
  /* This function is to be used as a thread. We expect a (smbcache*) as
   * argument */ 

  int ret=0, cache_flush_interval;
  struct smbcache *cache = (struct smbcache*) arg;
  char *tmp;

  if (!smb_conf) smb_conf = read_conf(CONFFILE,CONFFILE);
  tmp = get_conf(smb_conf,CACHE_IVAL);
  if (tmp){
    cache_flush_interval = strtol(tmp,NULL,10);
    free(tmp);
  }else
    cache_flush_interval = CACHE_DFL;
  
  printf("Using cache interval of %d for smb.conf cache\n",cache_flush_interval);

  while(1){
    pthread_testcancel();
    if (cache->content){
      if (pthread_mutex_trylock(&(cache->mutex)))
	continue;
      ret = flush_smb_cache(cache);
      if (ret) printf("[!!] Could not flush cache\n");
      pthread_mutex_unlock(&(cache->mutex));
      pthread_testcancel();
    }
    sleep(cache_flush_interval);
  }
}


static void flush_all_caches(){

  if (usermap_cache.content){
    pthread_mutex_lock(&(usermap_cache.mutex));
    flush_usermap_cache(&usermap_cache);
    pthread_mutex_unlock(&(usermap_cache.mutex));
  }

  if (monitors_cache.content){
    pthread_mutex_lock(&(monitors_cache.mutex));
    flush_smb_cache(&monitors_cache);
    pthread_mutex_unlock(&(monitors_cache.mutex));
  }

  if (groupmap_cache.content){
    pthread_mutex_lock(&(groupmap_cache.mutex));
    flush_usermap_cache(&groupmap_cache);
    pthread_mutex_unlock(&(groupmap_cache.mutex));
  }

}


static void clean_up(){

  /* free monitors*/
  if (services_list_monitor) destroy_monitor(services_list_monitor);
  if (usermap_file_monitor) destroy_monitor(usermap_file_monitor);
  if (groupmap_file_monitor) destroy_monitor(groupmap_file_monitor);

  /* free lists */
  if (global_services_list){
    free_array_elements(global_services_list);
    free_array(global_services_list);
  }

  if (cups_printers_list){
    free_array_elements(cups_printers_list);
    free_array(cups_printers_list);
  }

  if (global_samba_users_list){
    free_array_elements(global_samba_users_list);
    free_array(global_samba_users_list);
  }

  if (global_system_users_list){
    free_array_elements(global_system_users_list);
    free_array(global_system_users_list);
  }

  if (global_samba_groups_list){
    free_array_elements(global_samba_groups_list);
    free_array(global_samba_groups_list);
  }

  if (global_system_groups_list){
    free_array_elements(global_system_groups_list);
    free_array(global_system_groups_list);
  }

  if (user_groups){
    free_array_elements(user_groups);
    free_array(user_groups);
  }

  if (global_shares_list){
    free_array_elements(global_shares_list);
    free_array(global_shares_list);
  }

  if (global_printers_list){
    free_array_elements(global_printers_list);
    free_array(global_printers_list);
  }
  
  /* free linked lists and conf*/
  if (synonyms) free_smbopt_list(synonyms);
  if (defaults) free_smbopt_list(defaults);
  if (smb_conf) free_conf(smb_conf);

  /* free caches / threads*/
  pthread_mutex_lock(&monitors_cache.mutex);
  free_monitors_cache(&monitors_cache);
  pthread_mutex_unlock(&monitors_cache.mutex);
  pthread_mutex_destroy(&monitors_cache.mutex);
  
  pthread_mutex_lock(&usermap_cache.mutex);
  free_map_cache(&usermap_cache);
  pthread_mutex_unlock(&usermap_cache.mutex);
  pthread_mutex_destroy(&usermap_cache.mutex);

  pthread_mutex_lock(&groupmap_cache.mutex);
  free_map_cache(&groupmap_cache);
  pthread_mutex_unlock(&groupmap_cache.mutex);
  pthread_mutex_destroy(&groupmap_cache.mutex);
}


void terminator(){
  pthread_mutex_lock(&glob_mutex);
  flush_all_caches();
  pthread_mutex_unlock(&glob_mutex);

  pthread_mutex_lock(&services_list_mutex);
  clean_up();
  pthread_mutex_unlock(&services_list_mutex);
}





static struct smbopt *get_usermap_list(){

  char *username_map, *script = my_script_path("smt_smb_ra_get_user_mappings.py");
  struct smbopt *stounix = NULL;
  
  /* we can use g_synonyms to read it because smt_smb_ra_get_user_mappings.py 
   * outputs data in the same format expected by g_synonyms */
  username_map = __get_option(GLOBAL,USERNAME_MAP);
  if (!username_map) goto out;
  stounix = (struct smbopt*) readData1(script,username_map,(void*)g_synonyms);
  
 out:
  free(script);
  return stounix;
}


static struct smbopt *__get_groupmap_list(){

  char *script = my_script_path("smt_smb_ra_get_group_mappings.py");
  
  /* we can use g_synonyms to read it because smt_smb_ra_get_group_mappings.py 
   * outputs data in the same format expected by g_synonyms */
  struct smbopt *stounix = (struct smbopt*) readData1(script,GET_GRPMAP_CMD,
						                      (void*)g_map); 

  free(script);
  return stounix;
}


static int init_usermap_cache(struct smbcache *cache){
  /* Callers of this function should have gotten a lock from the cache mutex 
   * first */ 
  int ret = 0;
  char *map, *usermap_file = __get_option(GLOBAL,USERNAME_MAP);

  if (!usermap_file){
    map = strdup(USERMAP_DFL);
    ret = __set_option(GLOBAL,USERNAME_MAP,map);
    if (ret) goto out;
  }else
    map = strdup(usermap_file);
  
  /* initialize file monitor*/
  if (!usermap_file_monitor)
    start_monitor(&usermap_file_monitor,usermap_file);

  /*set up threading */  
  if (pthread_create(&(cache->thread),NULL,usermap_cache_flusher,&usermap_cache)){
    free(cache);
    goto out;
  }  
  cache->thread_running = 1;
  cache->content = (void *) get_usermap_list();
  cache->is_dirty = 0;

 out:
  free(map);
  return ret;
}


static int init_groupmap_cache(struct smbcache *cache){
  
  char *filename;
  int ret = 0;

  if (!smb_conf) smb_conf = read_conf(CONFFILE,CONFFILE);
  filename = get_conf(smb_conf,SMBGRPMAP);
  if (!filename) filename = strdup(DEF_SMBGRPMAPF);

  /* initialize file monitor*/
  if (!groupmap_file_monitor)
     start_monitor(&groupmap_file_monitor,filename);

  /* we don't need thread for groupmap */

  cache->content = (void *) __get_groupmap_list();
  cache->is_dirty = 0;
  
  free(filename);
  return ret;
}


static int populate_cache(struct smbcache *cache){
  /* We go to the file, and go agressively. Get all the information in the 
   * file, and store it in the cache. This initializes the cache flusher
   * thread. Callers of this function should have gotten a lock from the cache
   * mutex first */

  char *script = my_script_path("smt_smb_ra_get_all_services.py");
  char *filename = get_conf(smb_conf,SMBCONF);
  int ret = 0;

  if (pthread_create(&(cache->thread), NULL, smb_cache_flusher, &monitors_cache)){
    free(cache);
    goto out;
  }
  cache->thread_running = 1;
  cache->content = (void *)readData1(script,filename,(void*)g_cache_info);
  cache->is_dirty = 0;

  if (!services_list_monitor)
    start_monitor(&services_list_monitor,filename);

 out:
  free(filename);
  free(script);
  return ret;
}


static struct smbopt *find_in_cache(struct smbcache *cache, const char *service){
  /* Search the global monitor for a specified cache hit. Finding it in the 
   * structure DOES NOT mean it is up to date. */
	
  struct smbmonitors *monitor = (struct smbmonitors *) cache->content;

  for (; monitor ; monitor = monitor->next){
    if (!strcasecmp(monitor->service,service))
      return monitor->opts;
  }
  
  return NULL;
}


static struct smbcache *__get_usermap_cache(){

  int ret=0;

  pthread_mutex_lock(&(usermap_cache.mutex));

  if (!usermap_cache.content)
    ret = init_usermap_cache(&usermap_cache);
  else if (!check_events(usermap_file_monitor)){
    free_map_cache(&usermap_cache);
    ret = init_usermap_cache(&usermap_cache);
  }

  pthread_mutex_unlock(&(usermap_cache.mutex));

  if (ret || !usermap_cache.content){
    errno = -ENOMEM;
    return NULL;
  }

  return &usermap_cache;
}


static struct smbcache *__get_groupmap_cache(){
  
  int ret = 0;

  pthread_mutex_lock(&(groupmap_cache.mutex));

  if (!groupmap_cache.content)
    ret = init_groupmap_cache(&groupmap_cache);
  else if (!check_events(groupmap_file_monitor)){
    free_map_cache(&groupmap_cache);
    ret = init_groupmap_cache(&groupmap_cache);
  }

  pthread_mutex_unlock(&(groupmap_cache.mutex));

  if (ret || !groupmap_cache.content){
    errno = -ENOMEM;
    return NULL;
  }

  return &groupmap_cache;
}


static char **__g_samba_groups_list(){
  
  char **list = (char **)malloc(sizeof(char *));
  struct smbcache *cache = (struct smbcache*) __get_groupmap_cache();
  struct smbopt *grp = (struct smbopt*) cache->content;
  int i = 0;

  while(grp){
    list = realloc(list,(i+2)*sizeof(char *));
    list[i++] = strdup(grp->key);
    grp = grp->next;
  }

  list[i] = NULL;
  return list;
}


static struct smbopt *get_defaults_array(void){
  /* If the default values array is null, build it. We use 
   * smt_smb_ra_get_all_services.py to parse it because the default file is 
   * built using the same smb.conf structure */

  char *script = my_script_path("smt_smb_ra_get_all_services.py");
  char *filename = get_conf(smb_conf,SMBDEFAULTS);
  
  struct smbopt *dfl = (struct smbopt*) readData1(script,filename,(void*)g_defaults);

  free(script);
  free(filename);

  return dfl;
} 


static char *get_default_value(const char* opt){

  char *script = NULL; 
  struct smbopt *dfl;
  
  if(!defaults){
    script = my_script_path("smt_smb_ra_get_defaults.sh");
    if ( execScript((const char*)script) ){
	errno = -EINVAL;
	return NULL;
    }
    free(script);
    defaults = (struct smbopt*) get_defaults_array();
  }

  dfl = defaults;

  while (dfl) {
    if ( !strcmp(opt,dfl->key) )
      return dfl->value;
    dfl = dfl->next;
  }
  
  errno = -ENOOPT;
  return NULL;
}


static struct smbcache *__get_monitors_cache(){

  int ret = 0;

  pthread_mutex_lock(&(monitors_cache.mutex));
  
  if (!monitors_cache.content)
    ret = populate_cache(&monitors_cache);
  else if (!check_events(services_list_monitor)) {
    free_monitors_cache(&monitors_cache);
    ret = populate_cache(&monitors_cache);
  }
  pthread_mutex_unlock(&(monitors_cache.mutex));

  if (ret || !monitors_cache.content){
    errno = -ENOMEM;
    return NULL;
  }

  return &monitors_cache;
}


static char **__g_system_users_list(){

  char **ret = NULL;
  char *script = my_script_path("smt_smb_ra_get_sys_users.py");

  /* get users whose uig is higher than 500 */
  ret = (char**) readData1(script,LOWEST_UID,g_single_val_per_line_list);

  free(script);
  return ret;
}


static char **__g_cups_printers_list(){
  
  char **ret = NULL;
  char *script = my_script_path("smt_smb_ra_get_sys_printers.py");

  ret = (char**) readData(script,g_single_val_per_line_list);

  free(script);
  return ret;
}


static char **__g_system_groups_list(){

  char **ret = NULL;
  char *script = my_script_path("smt_smb_ra_get_db_entries.py");

  ret = (char**) readData1(script,GET_SYSGRPS_CMD,g_single_val_per_line_list);
  
  free(script);
  return ret;
}


static char **__g_samba_users_list(){

  char **ret = NULL;
  char *script = my_script_path("smt_smb_ra_get_db_entries.py");
  struct smbopt *p = NULL;
  struct smbcache *cache = __get_usermap_cache();
  int lErrno = 0;
 
  ret = (char**) readData1(script,GET_SMBUSRS_CMD,g_single_val_per_line_list);
  if (!ret) {
    lErrno = errno;
    if (errno) {
        return ret;
    }
  }

  if (!cache) p = NULL;
  else p = (struct smbopt *) cache->content;
 /* by now we have samba users defined in samba. Still need to get the samba
  * users defined in the user mappings */
  //p = (struct smbopt *) cache->content; 
  while(p){
    ret = add_string_array(ret,(const char*)p->key);
    p = p->next;
  }
  
  free(script);
  return ret;
}


static char **get_services_list(){

  struct smbmonitors *monitor;
  char **list = (char **)malloc(sizeof(char *));
  struct smbcache *cache = __get_monitors_cache();
  int i=0;
  
  if (!cache) return NULL;

  pthread_mutex_lock(&cache->mutex);
  monitor = (struct smbmonitors*) cache->content;

  while(monitor){
    if (monitor->service){
      list = realloc(list,(i+2)*sizeof(char *));
      list[i++] = strdup(monitor->service);
    }
    monitor = monitor->next;
  }
  list[i] = NULL;
  pthread_mutex_unlock(&cache->mutex);

  pthread_mutex_lock(&services_list_mutex);
  if (global_services_list){
    free_array_elements(global_services_list);
    free_array(global_services_list);
  }
  global_services_list = list;
  pthread_mutex_unlock(&services_list_mutex);

  return list;
}


static char *__g_option(const char *service, const char *opt){
  /* This functions returns the option value from the cache, if it exists */

  struct smbopt *opt_list;
  struct smbcache *cache = __get_monitors_cache();
  char *value = NULL;

  if (!cache){
    errno = -ENOMEM;
    return NULL;
  }
  if (!opt) {
  	return NULL;
  }
  
  pthread_mutex_lock(&cache->mutex);
  for (opt_list = find_in_cache(cache,service); opt_list; opt_list = opt_list->next)
    if (!strcasecmp(opt_list->key,opt)){
      value = opt_list->value;
      break;
    }
  
  pthread_mutex_unlock(&cache->mutex);
  return value;
}

	
static char *__get_option(const char *service, const char *opt){

  char *official, *value, *gvalue;

  official = get_official_name(opt);
  value = __g_option(service, official);

  if (!value /*|| may_override(official) */){
    gvalue = __g_option(GLOBAL, official);      
    if (gvalue) {
      return gvalue;
//    } else if {
//    	(value) return value
    } else {
      return get_default_value(official);
    }
  }

  return value;
}


char *get_option(const char *service, const char *opt){

  char *value;

  pthread_mutex_lock(&glob_mutex);
  value = __get_option(service,opt);
  pthread_mutex_unlock(&glob_mutex);

  return value;
}

char *get_default_option(const char *opt) {
  char *official, *value;
  
  official = get_official_name(opt);
  value = get_default_value(official);

  return value;
}

char *get_global_option(const char *opt){
  return get_option(GLOBAL,opt);
}


static int __check_default_and_global(const char *service, const char *key, const char *value){
  /* 
     Return 0 Is different to global value and/or default value
     Return 1 Equals to default value and/or global value
   */

  char *global_value = __get_option(GLOBAL,key);
  char *default_value = get_default_value(key);

  if (strcasecmp(GLOBAL,service) == 0) {
    if ( default_value && strcasecmp(value,default_value) == 0 ) { 
      return 1;
    }
    else {
      return 0;
    }
  } else {
    if (global_value && strcasecmp(global_value,value) == 0) {
      return 1;
    }
    else if (default_value && strcasecmp(default_value,value) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
}


static int __set_option_no_cache(const char *service, const char *key, const char *value){

  char *script = my_script_path("smt_smb_ra_set_option.py");
  char *filename = get_conf(smb_conf,SMBCONF);
  
  if (service_exists(service) ) return -EINVAL;

  return execScript4(script,filename,service,key,value);
  
}


static int __set_option_in_cache(struct smbcache *cache, const char *service, const char* key, const char *value){

  struct smbopt *opt, *first, *last = NULL;
  char *oldvalue = NULL;
  struct smbmonitors *monitor = (struct smbmonitors *) cache->content;
  int ret = -ENOSHARE;

  for(; monitor; monitor = monitor->next ){

    if ( !strcasecmp(monitor->service,service) ){
      /* found service */
      first = opt = monitor->opts;
      
      for(; opt; last = opt, opt = opt->next) {
	if ( !strcasecmp(key,opt->key) ) {
	  /* opt exists, update */
	  if (value) {
	    oldvalue = opt->value;
	    opt->value = strdup(value);
	    if (!opt->value){
	      ret = -ENOMEM;
	      opt->value = oldvalue;
	      goto out;
	    }
	    free(oldvalue);
	  }else{
	    if (opt==first) monitor->opts = opt->next;
	    else last->next = opt->next;
	    free(opt->key); free(opt->value); free(opt);
	  }
	  ret = 0;
	  cache->is_dirty = 1;    
	  goto out;
	}
      }

      if (!value){
	ret = 0;
	goto out;
      }

      /* if we are here, we need to create a new option */
      opt = __create_smbopt(key,value);
      if (opt){
	list_add(monitor->opts,opt);
	ret = 0;
	cache->is_dirty = 1;
	goto out;
      }
      break;
    }
  }
  
 out:
  return ret;
}


static int __set_option(const char *service, const char *key, const char *value){
  /* This function returns zero on success and an error code on failure */

  int whattodo = -1,ret;
  char *mvalue = NULL;
  char *official = get_official_name(key);
  struct smbcache *cache = __get_monitors_cache();

//  if (!cache) return -ENOENT;
  
  /* check if the new option is a default. If it is and there's a global opt
   * of the same value, it does not need to be in the opt_list. If there's
   * a global value different from the default, then we need to write the opt
   * anyway. If value is NULL we should remove the entry (-1) */

  if (value) whattodo = __check_default_and_global(service,official,value);
  
  switch(whattodo){
    case 0:
      mvalue = strdup(value);
      break;
    case 1:
      mvalue = NULL;
      break;
    default:
      printf("set_option: No value give\n");
  }

  if (!cache) {
    ret = __set_option_no_cache(service, official, mvalue);
  } else {
    pthread_mutex_lock(&(cache->mutex));
    ret = __set_option_in_cache(cache,service,official, mvalue);
    pthread_mutex_unlock(&(cache->mutex));
  }
  
  return ret;
}


int set_option(const char* service, const char *key, const char *value){
  
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = __set_option(service,key,value);
  pthread_mutex_unlock(&glob_mutex);

  return ret;
}


int set_global_option(const char *key, const char *value){
  
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = __set_option("global",key,value);
  pthread_mutex_unlock(&glob_mutex);

  return ret;
}


static int __delete_service_no_cache(const char *name){
  
  char *filename = get_conf(smb_conf,SMBCONF);
  char *script = my_script_path("smt_smb_ra_delete_service.py");
  int i,ret = -ENOENT;
  char **s_list;
  
  if (!strcasecmp(name,GLOBAL))
    goto out;
  
  for (s_list = get_services_list(), i=0; s_list[i]; i++)
    if (!strcasecmp(s_list[i],name))
      ret = execScript2(script,filename,name);
  
 out:
  return ret;  
}


static int __delete_service_in_cache(struct smbcache *cache, 
				           const char *name ){
  /* This function has to update everything in cache cause the monitors only
   * detect changes in disk files */
  
  struct smbmonitors *first, *cur, *last = NULL;
  struct smbopt *opts, *curopt;
  int ret = -EINVAL;

  if (!strcasecmp(GLOBAL,name)) goto out;

  cur = first = (struct smbmonitors *) cache->content;

  while (cur && strcasecmp(cur->service,name) ){
    last = cur;
    cur = cur->next;
  }

  if (!cur) goto out;
  
  if (cur==first) cache->content = cur->next;
  else last->next = cur->next;

  opts = cur->opts;
  while(opts){
    curopt = opts;
    free(opts->key);
    free(opts->value);
    opts = opts->next;
    free(curopt);
  }
  free(cur->service);
  free(cur);
  cache->is_dirty = 1;

  /* fix global_services_list */
  pthread_mutex_lock(&services_list_mutex);
  global_services_list = remove_string_array(global_services_list,name);
  pthread_mutex_unlock(&services_list_mutex);
  ret = 0;
 out:
  return ret;
  
}


static int delete_service(const char *name){

  int ret = 0;
  struct smbcache *cache = __get_monitors_cache();

  if (!cache) {
    ret = __delete_service_no_cache(name);

  } else {
    pthread_mutex_lock(&(cache->mutex));
    ret = __delete_service_in_cache(cache,name);
    pthread_mutex_unlock(&(cache->mutex));
  }

  return ret;
}


static int __create_service_no_cache(const char *name){

  char *filename = get_conf(smb_conf,SMBCONF);
  char **s_list = NULL;
  int i,ret;
  FILE *fp; 
  
  /* check if a service with this name already exists */
  ret = -EINVAL;
  for (s_list = get_services_list(), i=0; s_list && s_list[i]; i++)
    if (!strcasecmp(s_list[i],name))
      goto out;
  
  fp = fopen(filename,"a");
  if (!fp){
    ret = errno;
    goto out;
  }
  
  fprintf(fp,"[%s]\n",name);  
  fclose(fp);
  ret = 0;
  
 out:
  return ret;
  
}


static int __create_service_in_cache(struct smbcache *cache, const char *name ){
  /* This function has to update everything in cache cause the monitors only
   * detect changes in disk files */

  struct smbopt *found = find_in_cache(cache,name);
  struct smbmonitors *service = NULL;
  int ret = 0;

  /* check if a service with this name already exists */
  if (found) return -EEXIST;

  service = (struct smbmonitors*) malloc( sizeof(struct smbmonitors) );
  if (!service) return -ENOMEM;

  service->service = strdup(name);
  if (!service->service){
    ret = -ENOMEM;
    goto err;
  }

  service->opts = NULL;

  /* update global_service_list */
  pthread_mutex_lock(&services_list_mutex);
  global_services_list = add_string_array(global_services_list,name);
  pthread_mutex_unlock(&services_list_mutex);

  list_add( cache->content, service );
  cache->is_dirty = 1;

  return ret;

 err:
  if(service) { 
    if(service->service) free(service->service);
    free(service);
  }
  return ret;
}


static int create_service(const char *name){

  int ret = 0;
  struct smbcache *cache = __get_monitors_cache();

  if (!cache) {
    ret = __create_service_no_cache(name);
  } else {
    pthread_mutex_lock(&(cache->mutex));
    ret = __create_service_in_cache(cache,name);
    pthread_mutex_unlock(&(cache->mutex));
  }

  return ret;
}


int disable_service(const char *share){
	
  char *filename = get_conf(smb_conf,SMBCONF);
  char *script = my_script_path("smt_smb_ra_disable.py");
  if (!strcasecmp(share,GLOBAL))
    return -EINVAL;
  
  return execScript2(script,filename,share);	
}


int enable_service(const char *share){
  char *filename = get_conf(smb_conf,SMBCONF);
  char *script = my_script_path("smt_smb_ra_enable.py");
  return execScript2(script,filename,share);
}


int service_exists(const char *name){
  
  char **services;
  int i = 0, ret=0;
  
  if (!name) return 0;
  
  pthread_mutex_lock(&glob_mutex);
  services = get_services_list();

  while (services && services[i]) {
    if ( !strcasecmp(name,services[i++]) ){
      ret = 1;
      break;
    }
  }
  
  if(!ret && !strcasecmp(name,"global")) {
    create_service("global");
    ret=1;
  }
    
  pthread_mutex_unlock(&glob_mutex);
  return ret;
}


int share_exists(const char *share_name) {
  char **shares;
  int i=0;
  if (!share_name) return 0;

  pthread_mutex_lock(&glob_mutex);
  shares = get_shares_list();

  if(shares) {
    for(i=0; shares[i]; i++) {
      if(strcasecmp(share_name, shares[i]) == 0)
        return 1;
    }
  }

  pthread_mutex_unlock(&glob_mutex);
  return 0;
}

int printer_exists(const char *printer_name) {
  char **printer;
  int i=0;

  if (!printer_name) return 0;

  pthread_mutex_lock(&glob_mutex);
  printer = get_samba_printers_list();

  if(printer) {
    for(i=0; printer[i]; i++) {
      if(strcasecmp(printer_name, printer[i]) == 0)
        return 1;
    }
  }

  pthread_mutex_unlock(&glob_mutex);
  return 0;
}


int validHostName(const char* host_name) {
  return 1;
}


/* *_share : For a while, simple wrappers for _service functions */

char **get_shares_list(){
  
  char **shares_list = (char **) malloc(sizeof(char *));
  char **all_services;
  char *printable = NULL;
  int i,j=0;

  pthread_mutex_lock(&glob_mutex);

  all_services = get_services_list();

  for(i=0;all_services && all_services[i];i++){
    printable = __get_option(all_services[i],"printable");
    if (strcasecmp(GLOBAL,all_services[i]) && (!printable || !strcasecmp("no",printable))) {
        shares_list = (char**) realloc(shares_list,(j+2)*sizeof(char *));
        shares_list[j++] = strdup(all_services[i]);
    } else {
        continue;
    }
  }

  shares_list[j] = (char *) NULL;

  pthread_mutex_lock(&shares_list_mutex);
  if (global_shares_list){
    free_array_elements(global_shares_list);
    free_array(global_shares_list);
  }
  global_shares_list = shares_list;
  pthread_mutex_unlock(&shares_list_mutex);

  pthread_mutex_unlock(&glob_mutex);

  return global_shares_list;
}


int delete_share(const char *name){
  /* not performing any extra task yet */
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = delete_service(name);
  pthread_mutex_unlock(&glob_mutex);

  return ret;
}


int add_share(const char *name){
  /*Not performing any extra task yet */
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = create_service(name);
  pthread_mutex_unlock(&glob_mutex);
  
  return ret;
}


int set_share_option(const char *share, const char *key, const char *value){
  /* Not performing any extra task yet */
  int ret;
  char *c=NULL;;

  pthread_mutex_lock(&glob_mutex);

  ret = __set_option(share,key,value);
  if (ret) goto out;
  
  if (!strcasecmp(key,PATH) ){
    c = strchr(value,'%');
    if (c) goto out; /*a variable substitution will occur in runtime. Leave it*/

    ret = __check_path(value);
    if (ret) goto out;
  }

 out:
  pthread_mutex_unlock(&glob_mutex);
  return ret;
}


/* printers. For now only get_printers_names */

static char **__get_cups_printer_list(){

  pthread_mutex_lock(&cups_printers_list_mutex);
  if (cups_printers_list){
    free_array_elements(cups_printers_list);
    free_array(cups_printers_list);
  }
  cups_printers_list = __g_cups_printers_list();
  pthread_mutex_unlock(&cups_printers_list_mutex);

  return cups_printers_list;
}


char **get_cups_printer_list(){
  
  char **value;
  
  pthread_mutex_lock(&glob_mutex);
  value = __get_cups_printer_list();
  pthread_mutex_unlock(&glob_mutex);
  
  return value;
}


char **get_samba_printers_list(){
 
  char **printer_list = (char **) malloc(sizeof(char *));
  char **all_services;
  char *printable = NULL;
  int i,j=0;

  pthread_mutex_lock(&glob_mutex);

  all_services = get_services_list();

  for(i=0;all_services && all_services[i];i++){
    printable = __get_option(all_services[i],"printable");
    if (!strcasecmp(GLOBAL,all_services[i]) || !printable || !strcasecmp("no",printable)) continue;
    printer_list = realloc(printer_list,(j+2)*sizeof(char *));
    printer_list[j++] = strdup(all_services[i]);
  }
  printer_list[j] = (char *) NULL;

  pthread_mutex_lock(&printers_list_mutex);  
  if(global_printers_list){
    free_array_elements(global_printers_list);
    free_array(global_printers_list);
  }
  global_printers_list = printer_list;
  pthread_mutex_unlock(&printers_list_mutex);

  pthread_mutex_unlock(&glob_mutex);
  return global_printers_list;
}


int add_samba_printer(const char* name){

  int ret;

  pthread_mutex_lock(&glob_mutex);
  
  ret = create_service(name);
  if (ret) goto out;

 out:
  pthread_mutex_unlock(&glob_mutex);
  return ret;
}


int delete_samba_printer(const char *name){
  /* not performing any extra task yet */
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = delete_service(name);
  pthread_mutex_unlock(&glob_mutex);

  return ret;
}


int set_printer_option(const char *name, const char* key, const char *value){
  /* Not performing any extra task yet */
  int ret;

  pthread_mutex_lock(&glob_mutex);
  ret = __set_option(name,key,value);
  pthread_mutex_unlock(&glob_mutex);

  return ret;
}
 
static int __entry_exists(const char *username, char **list){
  /* Returns 1 if true or 0 if false */

  int i = 0;

  while(list && list[i]){
    if ( !strcmp(username,list[i]) ) return 1;
    i++;
  }
  return 0;
}


static int __remove_usermap_reverse(const char *unix_name){
  /* Returns 0 on success. Returns -1 of no entry was found */

  struct smbopt *p, *last = NULL;
  struct smbcache *cache = __get_usermap_cache();

  pthread_mutex_lock(&(cache->mutex));

  p = (struct smbopt*) cache->content;
  
  while(p){
    
    if ( !strcmp(unix_name,p->value) ){
      if (p==cache->content) 
          cache->content = (void*) p->next;
      else 
          last->next = p->next;
      if(p){
	      if(p->key) free(p->key);
	      if(p->value) free(p->value);
	      free(p);
      }
      p = last->next;
    }else{
      last = p;
      p = p->next;
    }
  }

  cache->is_dirty = 1;
  pthread_mutex_unlock(&(cache->mutex)); 
  return 0;
}


static int __remove_usermap(const char *samba_name){
  /* Returns 0 on success. Returns -1 if no samba user was found with the 
   * specified name */

  struct smbopt *p,*last = NULL;
  struct smbcache *cache = __get_usermap_cache();
  int ret = -1;

  pthread_mutex_lock(&(cache->mutex));

  p = (struct smbopt*) cache->content;
  
  while(p){
    if (!strcmp(samba_name,p->key)) break;
    last = p;
    p = p->next;
  }

  if (p==cache->content) cache->content = (void*) p->next;
  else last->next = p->next;
  
  if(p){
    if(p->key) free(p->key);
    if(p->value) free(p->value);
    free(p);
    ret = 0;
  }

  cache->is_dirty = 1;
  pthread_mutex_unlock(&(cache->mutex));
  return ret;
}


static int __add_usermap(const char *samba_name, const char *unix_name){
  /* Returns 0 on success or an error code on falilure */  

  struct smbopt *newEntry = NULL;
  struct smbcache *cache = __get_usermap_cache();
  int ret = -ENOMEM;
     
  pthread_mutex_lock(&(cache->mutex));

  newEntry = (struct smbopt*) malloc(sizeof(struct smbopt));
  if (!newEntry) goto out;
  
  newEntry->next = NULL;
  newEntry->key = strdup(samba_name);
  newEntry->value = strdup(unix_name);
  if (!newEntry->key || !newEntry->value) goto out;
  
  list_add(cache->content, newEntry);
  cache->is_dirty = 1;
  ret = 0;

 out:
  if (ret && newEntry){
    if(newEntry->key) free(newEntry->key); 
    if(newEntry->value) free(newEntry->value);
    free(newEntry);
  } 
  pthread_mutex_unlock(&(cache->mutex));
  return ret;
}

static int __create_sys_user(const char *user){
  // Creates a user in the system

  char *script = my_script_path("smt_smb_ra_create_sys_user.py");
  int ret;

  ret = execScript1(script,user);
  free(script);
  return ret;
}

static int __create_smb_user(const char *user, const char *password){
  
  char *script = my_script_path("smt_smb_ra_create_samba_user.py");
  int ret;

  ret = execScript2(script,user,password);
  free(script);
  return ret;
} 


static int __delete_smb_user(const char *user){

  char *script = my_script_path("smt_smb_ra_delete_samba_user.py");
  int ret;

  ret = execScript1(script,user);
  free(script);
  return ret;
}

static int __modify_smb_user(const char *user, const char *password) {

  char *script = my_script_path("smt_smb_ra_modify_samba_user.py");
  int ret;

  ret = execScript2(script,user,password);
  free(script);
  return ret;
}

static char *__get_user_unix_name(const char* samba_user){

  struct smbopt *p = NULL;
  struct smbcache *cache;
  char *ret = (char*) samba_user;

  cache = __get_usermap_cache();
  if(cache) p = (struct smbopt *) cache->content;
  else p = NULL;

  while(p){
    if (!strcmp(samba_user,p->key)){
      ret = p->value;
      break;
    }
    else p = p->next;
  }

  return (char *) ret;
}


char *get_user_unix_name(const char* samba_user){

  char *value;
 
  pthread_mutex_lock(&glob_mutex);
  value = __get_user_unix_name(samba_user);
  pthread_mutex_unlock(&glob_mutex);

  return value;
}



static char **__get_samba_users_list(){
  int lErrno = 0;
  /* We don't implement a cache for this function since it will be called few
   * times. Although we don't cache the return array, we need to keep track of
   * it in order not to leak memory */

  pthread_mutex_lock(&samba_users_list_mutex);
 
  if (global_samba_users_list){
    free_array_elements(global_samba_users_list);
    free_array(global_samba_users_list);
  }

  global_samba_users_list = __g_samba_users_list();
  if (!global_samba_users_list) {
    lErrno = errno;
  }
  pthread_mutex_unlock(&samba_users_list_mutex);

  errno = lErrno;
  return global_samba_users_list;
}


char **get_samba_users_list(){
  int lErrno = 0;
  char **value;

  pthread_mutex_lock(&glob_mutex);
  value = __get_samba_users_list();
  if (!value) {
    lErrno = errno;
  }
  pthread_mutex_unlock(&glob_mutex);

  errno = lErrno;
  return value;
}


static char **__get_system_users_list(){
  /* We don't implement a cache for this function since it will be called few
   * times. Although we don't cache the return array, we need to keep track of
   * it in order not to leak memory */

  pthread_mutex_lock(&system_users_list_mutex);  

  if (global_system_users_list){
    free_array_elements(global_system_users_list);
    free_array(global_system_users_list);
  }
  
  global_system_users_list = __g_system_users_list();
  pthread_mutex_unlock(&system_users_list_mutex);  

  return global_system_users_list;
}


char **get_system_users_list(){
  
  char **value;
  
  pthread_mutex_lock(&glob_mutex);
  value = __get_system_users_list();
  pthread_mutex_unlock(&glob_mutex);
 
  return value;
}

int modify_samba_user(const char *samba_name, const char *unix_name_cur, 
                      const char *unix_name_new, const char *password){

     char **system_users, **samba_users;
     int ret = 0;

     pthread_mutex_lock(&glob_mutex);

     system_users = __get_system_users_list();
     samba_users = __get_samba_users_list();
     if (!samba_users && errno) {
        ret = -ENOENT;
        goto out;
     }

     if (!__entry_exists(samba_name,samba_users)) {
        ret = -ENOENT;
        goto out;
     }

     /*if (!unix_name_cur) unix_name_cur = samba_name;
     
     if (!__entry_exists(unix_name_cur,system_users)) {
        ret = -ENOENT;
        goto out;
     }*/

     if (!unix_name_new) unix_name_new = samba_name;

     if (!__entry_exists(unix_name_new,system_users)) {
        ret = -ENOENT;
        goto out;
     }

     /* delete user mapping */
     if (!strcmp(samba_name,unix_name_cur)) {
        ret = __remove_usermap_reverse(unix_name_cur);
        if (ret) goto out;
     } else {
        ret = __remove_usermap(samba_name);
        if (ret) goto out;
     }

     if (!__entry_exists(unix_name_new,samba_users)) {
        ret = __modify_smb_user(unix_name_new,password);
        if (ret) goto out;
     }

     /* create mapping if necessary */
     if (strcmp(samba_name,unix_name_new) )
        ret = __add_usermap(samba_name,unix_name_new);

 out:
  pthread_mutex_unlock(&glob_mutex);
  return ret;

}

int add_samba_user(const char *samba_name, const char *unix_name, 
		                             const char *password){

  char **system_users, **samba_users;
  int ret = 0;

  pthread_mutex_lock(&glob_mutex);

  system_users = __get_system_users_list();
  samba_users = __get_samba_users_list();
  if (!samba_users && errno) {
     ret = -ENOENT;
     goto out;
  }

  if ( __entry_exists(samba_name,samba_users) ){
    ret = -EEXIST;
    goto out;
  }
  
  if (!unix_name) unix_name = strdup(samba_name);

  /* verify if unix_name is a valid system user */
  if (!__entry_exists(unix_name,system_users) ){
    ret = -ENOENT;
    goto out;
  }
  
  /* create unix user if needed. If you want to make it possible to create
     system users, comment the above verification and uncomment this */
  if (!__entry_exists(unix_name,system_users) ){
    ret = __create_sys_user(unix_name);
    if (ret) goto out;
  }
 
  /* add unix user to samba */
  if (!__entry_exists(unix_name,samba_users) ){
    ret = __create_smb_user(unix_name,password);
    if (ret) goto out;
  }

  /* create mapping if necessary */
  if (strcmp(samba_name,unix_name) )
    ret = __add_usermap(samba_name,unix_name);

 out:
  pthread_mutex_unlock(&glob_mutex);
  return ret;
}


int delete_samba_user(const char *samba_user){
  
  char *unix_user;
  char **samba_users;
  int ret = 0;

  pthread_mutex_lock(&glob_mutex);
  samba_users = __get_samba_users_list();
  if (!samba_users && errno) {
    ret = -ENOENT;
    goto out;
  }

  if (!__entry_exists(samba_user,samba_users)){
    ret = -ENOENT;
    goto out;
  }
 
  unix_user = __get_user_unix_name(samba_user);

  if (!strcmp(samba_user,unix_user) ){
    /* This is a samba user that maps directly to a unix user. Take it out from
     * samba database and also any other users that map to it */
    
    ret = __remove_usermap_reverse(unix_user);
    if (ret) goto out;
    
    ret = __delete_smb_user(unix_user);
	
  }else{
    /* This is a usermap name. Delete it from usermap only */
    
    ret = __remove_usermap(samba_user);
  }
  
 out:
  pthread_mutex_unlock(&glob_mutex);
  return ret;
  
}


static char *get_group_mapping_reverse(const char* unix_group){

  struct smbopt *p = NULL;
  struct smbcache *cache = __get_groupmap_cache();
  
  p = (struct smbopt *) cache->content;
  
  while(p){
    if (!strcmp(unix_group,p->value)) return p->key;
    else p = p->next;
  }
  
  return NULL;
}


static char *__get_unix_group_name(const char* samba_group){

  struct smbopt *p = NULL;
  struct smbcache *cache = __get_groupmap_cache();
  char *ret = NULL;

  p = (struct smbopt *) cache->content;

  while(p){
    if (!strcmp(samba_group,p->key)){
      ret = p->value;
      break;
    }
    else p = p->next;
  }

  return ret;
}


char *get_unix_group_name(const char* samba_group){
  
  char *value;

  pthread_mutex_lock(&glob_mutex);
  value = __get_user_unix_name(samba_group);
  pthread_mutex_unlock(&glob_mutex);

  return value;
}


static char **__get_samba_groups_list(){
  /* We don't implement a cache for this function since it will be called few
   * times. Although we don't cache the return array, we need to keep track of
   * it in order not to leak memory. global_samba_groups_list a an array of 
   * references to samba_groupmap_cache; therefore, we NEVER free the contents
   * of each position, we free only the array itself */
  
  pthread_mutex_lock(&samba_groups_list_mutex);

  if (global_samba_groups_list){
    free_array_elements(global_samba_groups_list);
    free_array(global_samba_groups_list);
  }

  global_samba_groups_list = __g_samba_groups_list();
  pthread_mutex_unlock(&samba_groups_list_mutex);

  return global_samba_groups_list;
}


char **get_samba_groups_list(){
  
  char **value;

  pthread_mutex_lock(&glob_mutex); 
  value = __get_samba_groups_list();
  pthread_mutex_unlock(&glob_mutex); 
  
  return value;
}


static char **__get_system_groups_list(){
  /* We don't implement a cache for this function since it will be called few
   * times. Although we don't cache the return array, we need to keep track of
   * it in order not to leak memory */

  pthread_mutex_lock(&system_groups_list_mutex);

  if (global_system_groups_list){
    free_array_elements(global_system_groups_list);
    free_array(global_system_groups_list);
  }
  
  global_system_groups_list = __g_system_groups_list();
  pthread_mutex_unlock(&system_groups_list_mutex);

  return global_system_groups_list;
}


char **get_system_groups_list(){
  
  char **value;
  
  pthread_mutex_lock(&glob_mutex); 
  value = __get_system_groups_list();
  pthread_mutex_unlock(&glob_mutex); 
  
  return value;
}


static char **__get_user_sys_groups(const char *user){

  char *script = my_script_path("smt_smb_ra_get_user_sys_groups.py");
  char **user_sys_groups = (char**) readData1(script,user,
					      g_single_val_per_line_list);

  free(script);
  return user_sys_groups;

}


static char **__get_user_groups(const char *user){

  char **smb_users;
  char **smb_grps = (char **)malloc(2*sizeof(char *));
  char **sys_grps;
  char *unix_username;
  char *tmp;
  int i,j=0;

  smb_users = __get_samba_users_list();
  if (!smb_users && errno) {
      return NULL;
  }
  unix_username = __get_user_unix_name(user);

  if (!__entry_exists(unix_username,smb_users)) return NULL;

  /* user_groups is not an array of pointers to data from other structures. So,
   * we need to free its contents */
  if (user_groups){
    free_array_elements(user_groups);
    free_array(user_groups);
  }
  
  sys_grps = __get_user_sys_groups(unix_username);

  for(i=0; sys_grps && sys_grps[i]; i++){
    tmp = get_group_mapping_reverse(sys_grps[i]);
    if ( !tmp ) continue;
    smb_grps = realloc(smb_grps,(i+2)*sizeof(char*));
    smb_grps[j++] = strdup(tmp);
  }
  smb_grps[j] = NULL;
  user_groups = smb_grps;
  
  free_array_elements(sys_grps);
  free_array(sys_grps);

  return user_groups;
}


char **get_user_groups(const char *user){
  int lErrno = 0;
  char **value;

  pthread_mutex_lock(&glob_mutex);
  value = __get_user_groups(user);
  if (!value && errno) {
    lErrno = errno;
  }
  pthread_mutex_unlock(&glob_mutex);

  errno = lErrno;
  return value;
}


int set_group_mapping(const char *samba_grp, const char *unix_grp){

  char *script = my_script_path("smt_smb_ra_set_group_mapping.py");
  char **smb_grps, **unx_grps;
  int ret = -EINVAL;

  pthread_mutex_lock(&glob_mutex);   
  if (!samba_grp) goto out;
  
  smb_grps = __get_samba_groups_list();
  unx_grps = __get_system_groups_list();


  if (!__entry_exists(samba_grp,smb_grps) ) goto out;
  if (unix_grp && !__entry_exists(unix_grp,unx_grps) ) goto out;
  
  if (unix_grp)
    ret = execScript2(script,samba_grp,unix_grp);
  else
    ret = execScript1(script,samba_grp);

 out: 
  free(script);
  pthread_mutex_unlock(&glob_mutex);   
  return ret;
}

int modify_samba_group(const char* samba_grp,const char* cur_unix_grp, const char *unix_grp){

  char *script = my_script_path("smt_smb_ra_modify_samba_group.py");
  char **smb_grps, **unx_grps;
  char *funix_grp = NULL;
  int ret=0;
  char create_sys_grp[] = "0"; //Leave this as 0 in order NOT to create new
                               //system groups


  pthread_mutex_lock(&glob_mutex);
  smb_grps = __get_samba_groups_list();
  unx_grps = __get_system_groups_list();


  /* check if samba group already exists - else return */
  if (!__entry_exists(samba_grp,smb_grps) ) {
    ret = -ENOENT;
    goto out;
  }

  /*if (!cur_unix_grp) funix_grp = DEF_GRP;
  else funix_grp = (char *) cur_unix_grp;

  if (!__entry_exists((const char*)funix_grp,unx_grps) ){
    ret = -ENOENT;
    goto out;
  }*/

  if (!unix_grp) funix_grp = DEF_GRP;
  else funix_grp = (char *) unix_grp;

  if (!__entry_exists((const char*)funix_grp,unx_grps) ){
    ret = -ENOENT;
    goto out;
  }


  //Use this only if RA is to create a system group if it does not exist
  /*
  if (!__entry_exists((const char*)funix_grp,unx_grps) )
    strcpy(create_sys_grp,"1");
  */

  ret = execScript3(script,samba_grp,funix_grp,create_sys_grp);
 out:
  free(script);
  pthread_mutex_unlock(&glob_mutex);
  return ret;
}

int create_samba_group(const char* samba_grp, const char *unix_grp){

  char *script = my_script_path("smt_smb_ra_create_samba_group.py");
  char **smb_grps, **unx_grps;
  char *funix_grp = NULL;
  int ret;
  char create_sys_grp[] = "0"; //Leave this as 0 in order NOT to create new
                               //system groups

  pthread_mutex_lock(&glob_mutex);   
  smb_grps = __get_samba_groups_list();
  unx_grps = __get_system_groups_list();

  /* check if samba group already exists */
  if (__entry_exists(samba_grp,smb_grps) ) {
    ret = -EEXIST;
    goto out;
  }

  if (!unix_grp) funix_grp = DEF_GRP;
  else funix_grp = (char *) unix_grp;

  if (!__entry_exists((const char*)funix_grp,unx_grps) ){
    ret = -ENOENT;
    goto out;
  }

  //Use this only if RA is to create a system group if it does not exist
  /*
  if (!__entry_exists((const char*)funix_grp,unx_grps) )
    strcpy(create_sys_grp,"1");
  */

  ret = execScript3(script,samba_grp,funix_grp,create_sys_grp);

 out:
  free(script);
  pthread_mutex_unlock(&glob_mutex);   
  return ret;
}


int delete_samba_group(const char* samba_grp){

  char *script = my_script_path("smt_smb_ra_delete_samba_group.py");
  char *groupmap_file = NULL;
  char **smb_grps;
  int ret;

  pthread_mutex_lock(&glob_mutex);   
  smb_grps = __get_samba_groups_list();

  if (!__entry_exists(samba_grp, smb_grps) ) {
    ret = -ENOENT;
    goto out;
  }

  if (!smb_conf) smb_conf = read_conf(CONFFILE,CONFFILE);
    groupmap_file = get_conf(smb_conf,SMBGRPMAP);
  if (!groupmap_file) 
    groupmap_file = strdup(DEF_SMBGRPMAPF);

  ret = execScript2(script,samba_grp,groupmap_file);

 out:
  free(script);
  free(groupmap_file);
  pthread_mutex_unlock(&glob_mutex);   
  return ret;
}



int add_user_to_group(const char *samba_user, const char *samba_group){

  char *script = my_script_path("smt_smb_ra_add_user_to_group.py");
  char *unix_user = NULL, *unix_group = NULL;
  char **usr_grps, **smb_users, **smb_groups;
  int ret = -EINVAL;

  return -EINVAL; //We have disabled this function. It should not  be used for
                  //now. Take this out to start using it again

  pthread_mutex_lock(&glob_mutex);   
  usr_grps = __get_user_groups(samba_user);
  if (!usr_grps && errno) goto out;
  smb_users = __get_samba_users_list();
  if (!smb_users && errno) goto out;
  smb_groups = __get_samba_groups_list();

  if (!__entry_exists(samba_user,smb_users) ) goto out;
  if (!__entry_exists(samba_group,smb_groups) ) goto out;
  if (__entry_exists(samba_group,usr_grps) ) goto out;
 
  unix_user = __get_user_unix_name(samba_user);
  unix_group = __get_unix_group_name(samba_group);

  ret = execScript2(script,unix_user,unix_group);

 out:
  free(script);
  pthread_mutex_unlock(&glob_mutex);   
  return ret;
}


int remove_user_from_group(const char *samba_user, const char *samba_group){

  char *script = my_script_path("smt_smb_ra_remove_user_from_group.py");
  char *unix_user = NULL, *unix_group = NULL;
  char **usr_grps, **smb_users, **smb_groups;
  int ret = -EINVAL;

  return -EINVAL; //We have disabled this function. It should not  be used for
                  //now. Take this out to start using it again

  pthread_mutex_lock(&glob_mutex);   
  usr_grps = __get_user_groups(samba_user);
  if (!usr_grps && errno) goto out;
  smb_users = __get_samba_users_list();
  if (!smb_users && errno) goto out;
  smb_groups = __get_samba_groups_list();
  
  if (!__entry_exists(samba_user,smb_users) ) goto out;
  if (!__entry_exists(samba_group,smb_groups) ) goto out;
  if (!__entry_exists(samba_group,usr_grps) ) goto out;
 
  unix_user = __get_user_unix_name(samba_user);
  unix_group = __get_unix_group_name(samba_group);
  ret = execScript2(script,unix_user,unix_group);

 out:
  free(script);
  pthread_mutex_unlock(&glob_mutex);   
  return ret;
}


int start_server(){
  
  char *configured_service = NULL, *service, *nmb, *dname, *copy;
  struct stat status;
  int ret = 1;

  if ( status_server() ) return 0; /* return success if server already up */ 
  
  configured_service = get_conf(smb_conf,SMB_SERVICE);
  
  if (!configured_service) service = strdup(SMB_DEF); /*fall back to default*/
  else service = strdup(configured_service);

  /* samba version compatibility check. Look for nmb */
  copy = strdup(service);
  dname = dirname(copy);
  nmb = (char*) malloc((strlen(dname)+strlen("/nmb")+1)*sizeof(char));
  sprintf(nmb,"%s/nmb",dname);

  if ( !stat(nmb,&status) ){ 
    ret = execScript1(nmb,"start");
    if (ret) goto out;
  }
  
  /*samba service*/
  if ( stat(service,&status) ){
    ret = 1;
    goto out;
  }else ret = execScript1(service,"start"); 
    
 out:
  free(copy);
  free(service);
  if ( ret ) return ret;
  else if ( !status_server() ) return 1;
  else return 0;
}


int stop_server(){
  
  char *configured_service = NULL, *service, *nmb, *dname, *copy;
  struct stat status;
  int ret = 1;

  if ( !status_server() ) return 0; /* return success if server already down */
  
  configured_service = get_conf(smb_conf,SMB_SERVICE);
  
  if (!configured_service) service = strdup(SMB_DEF); /*fall back to default*/
  else service = strdup(configured_service);

  /* samba version compatibility check. Look for nmb */
  copy = strdup(service);
  dname = dirname(copy);
  nmb = (char*) malloc((strlen(dname)+strlen("/nmb")+1)*sizeof(char));
  sprintf(nmb,"%s/nmb",dname);
  
  if ( !stat(nmb,&status) ){ 
    ret = execScript1(nmb,"stop");
    if (ret) goto out;
  }
  
  /*samba service*/
  if ( stat(service,&status) ){
    ret = 1;
    goto out;
  }else ret = execScript1(service,"stop"); 
    
 out:
  free(copy);
  free(service);
  return ret;
}


int restart_server(){

  char *configured_service = NULL, *service, *nmb, *dname, *copy;
  struct stat status;
  int ret = 1;
  
  configured_service = get_conf(smb_conf,SMB_SERVICE);
  
  if (!configured_service) service = strdup(SMB_DEF); /*fall back to default*/
  else service = strdup(configured_service);

  /* samba version compatibility check. Look for nmb */
  copy = strdup(service);
  dname = dirname(copy);
  nmb = (char*) malloc((strlen(dname)+strlen("/nmb")+1)*sizeof(char));
  sprintf(nmb,"%s/nmb",dname);
  if ( !stat(nmb,&status) ){ 
    ret = execScript1(nmb,"restart");
    if (ret) goto out;
  }
  
  /*samba service*/
  if ( stat(service,&status) ){
    ret = 1;
    goto out;
  }else ret = execScript1(service,"restart"); 
    
 out:
  free(copy);
  free(service);
  return ret;
}

  
int status_server(){

  char *configured_service = NULL, *service, *nmb, *dname, *copy;
  struct stat status;
  int nret = 1, sret, ret=0;
  
  configured_service = get_conf(smb_conf,SMB_SERVICE);
  
  if (!configured_service) service = strdup(SMB_DEF); /*fall back to default*/
  else service = strdup(configured_service);
  
  /* samba version compatibility check. Look for nmb */
  copy = strdup(service);
  dname = dirname(copy);
  nmb = (char*) malloc((strlen(dname)+strlen("/nmb")+1)*sizeof(char));
  sprintf(nmb,"%s/nmb",dname);
  
  if ( !stat(nmb,&status) ){ 
    nret = !execScript1(nmb,"status");
  }
  
  /*samba service*/
  if ( stat(service,&status) ){
    sret = 0;
    goto out;
  }else sret = !execScript1(service,"status"); 
  
  if (nret*sret!=0) ret = 1;
  
 out:
  free(copy);
  free(service);
  return ret;
}

