// =======================================================================
// Linux_SambaUserResourceAccess.cpp
//     created on Mon, 26 Jun 2006 using ECUTE 2.2.1
//
// Copyright (c) 2006, 2009, International Business Machines
//
// THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
// ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
// CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
//
// You can obtain a current copy of the Eclipse Public License from
// http://www.opensource.org/licenses/eclipse-1.0.php
//
// Author:        generated
//
// Contributors:
//                Wolfgang Taphorn   <taphorn@de.ibm.com>
//                Mukunda Chowdaiah  <cmukunda@in.ibm.com>
//                Ashoka S Rao       <ashoka.rao@in.ibm.com>
//                Rodrigo Ceron      <rceron@br.ibm.com>
//
// =======================================================================
//
// 
#include "Linux_SambaUserResourceAccess.h"

#include <errno.h>

#include "smt_smb_ra_support.h"
#include "smt_smb_defaultvalues.h"

extern int errno;

namespace genProvider {

  
  //----------------------------------------------------------------------------
  // manual written methods
  
  static bool validUser(const char* user) {
    char ** users = get_samba_users_list();
    if (!users && errno) 
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Failed to retrieve Samba user list");
    if(users){
      for (int i=0; users[i]; i++){
	if(!strcmp(users[i],user))
	  return true;
      }
    }
    return false;
  };

  
  //----------------------------------------------------------------------------


  static void setInstanceNameProperties(
      const char* aNameSpaceP, 
      char *instanceName, 
      Linux_SambaUserInstanceName& anInstanceName) {
    
    anInstanceName.setNamespace(aNameSpaceP);
    anInstanceName.setSambaUserName(instanceName);
  };

  
  //----------------------------------------------------------------------------
  
  
  //----------------------------------------------------------------------------
  //Linux_SambaUserResourceAccess::Linux_SambaUserResourceAccess();

  //----------------------------------------------------------------------------
  Linux_SambaUserResourceAccess::~Linux_SambaUserResourceAccess() {
    terminator();
  }
    
  // intrinsic methods

  //----------------------------------------------------------------------------
  void
  Linux_SambaUserResourceAccess::enumInstanceNames(
     const CmpiContext& aContext,
     const CmpiBroker& aBroker,
     const char* aNameSpaceP,
     Linux_SambaUserInstanceNameEnumeration& anInstanceNameEnumeration) {
      
    char ** users = get_samba_users_list();
    if (!users && errno) {
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Failed to retrieve Samba user list");
    }
    
    if(users){
      for (int i=0; users[i]; i++){
	Linux_SambaUserInstanceName instanceName;
	setInstanceNameProperties(aNameSpaceP,users[i],instanceName);
	anInstanceNameEnumeration.addElement(instanceName); 
      }
    }
  }

  
  //----------------------------------------------------------------------------

  void
  Linux_SambaUserResourceAccess::enumInstances(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    Linux_SambaUserManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    char ** users = get_samba_users_list();
    if (!users && errno) {
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Failed to retrieve Samba user list");
    }
    
    if(users){
      for (int i=0; users[i]; i++){
	Linux_SambaUserManualInstance aManualInstance;
	Linux_SambaUserInstanceName instanceName;
	
	setInstanceNameProperties(aNameSpaceP,users[i],instanceName);
	aManualInstance.setInstanceName(instanceName);
	
	char* option;
	option = get_user_unix_name(instanceName.getSambaUserName());
	if ( option )
	  aManualInstance.setSystemUserName( option );
	
	aManualInstanceEnumeration.addElement(aManualInstance);
      }
    }
  }

  
  //----------------------------------------------------------------------------

  Linux_SambaUserManualInstance 
  Linux_SambaUserResourceAccess::getInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaUserInstanceName& anInstanceName) {

    if(validUser(anInstanceName.getSambaUserName())){
      Linux_SambaUserManualInstance aManualInstance;
      aManualInstance.setInstanceName(anInstanceName);
      char* option;
      option = get_user_unix_name(anInstanceName.getSambaUserName());
      if ( option )
	aManualInstance.setSystemUserName( option );
      
      return aManualInstance;  
      
    }else
      throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"Instance does not exist!");
  }

  //----------------------------------------------------------------------------
  
  void
  Linux_SambaUserResourceAccess::setInstance(
     const CmpiContext& aContext,
     const CmpiBroker& aBroker,
     const char** aPropertiesPP,
     const Linux_SambaUserManualInstance& aManualInstance) { 
      
     int ret;
     char * option = get_user_unix_name(aManualInstance.getInstanceName().getSambaUserName());

    ret = modify_samba_user(aManualInstance.getInstanceName().getSambaUserName(), option, aManualInstance.getSystemUserName(), aManualInstance.getSambaUserPassword());
    if(ret){
      if (ret==-EEXIST)
	throw CmpiStatus(CMPI_RC_ERR_ALREADY_EXISTS,"Instance already exists!");
      else if(ret==-ENOENT)
        throw CmpiStatus(CMPI_RC_ERR_FAILED,"The specified SystemUserName is not known in the system");
      else
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Instance could not be added!");
    }
  }
  
  //----------------------------------------------------------------------------

  Linux_SambaUserInstanceName
  Linux_SambaUserResourceAccess::createInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaUserManualInstance& aManualInstance) {
    
    int ret;
    
    ret = add_samba_user(aManualInstance.getInstanceName().getSambaUserName(), aManualInstance.getSystemUserName(), aManualInstance.getSambaUserPassword());
    if(ret){
      if (ret==-EEXIST)
	throw CmpiStatus(CMPI_RC_ERR_ALREADY_EXISTS,"Instance already exists!");
      else if(ret==-ENOENT)
        throw CmpiStatus(CMPI_RC_ERR_FAILED,"The specified SystemUserName is not known in the system");
      else
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Instance could not be added!");
    }
    
    return aManualInstance.getInstanceName();
  }

  
  //----------------------------------------------------------------------------

  void
  Linux_SambaUserResourceAccess::deleteInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaUserInstanceName& anInstanceName) {
    
    int ret;
    ret = delete_samba_user(anInstanceName.getSambaUserName());
    if(ret){
      if(ret == -ENOENT)
	throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"Instance does not exist!"); 
      else
	throw CmpiStatus(CMPI_RC_ERR_FAILED,"Instance could not be deleted!");
    }
  }

	

  
  // extrinsic methods


  char* Linux_SambaUserResourceAccess::getAllSystemGroups(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaUserInstanceName& anInstanceName) {
    
    char ** groups = get_system_groups_list();
    char *  ret = NULL;
    int len = 0;
    
    if(groups){
      for (int i=0; groups[i]; i++)
	len = len + strlen(groups[i]) + 4;
      
      ret =(char*) calloc(len,sizeof(char));
      
      for (int i=0; groups[i]; i++){
	if(ret[0]=='\0')
	  sprintf(ret,"%s",groups[i]);
	else
	  sprintf(ret,"%s, %s",ret,groups[i]);
      }
    }
    
    return ret;
  }



  char* Linux_SambaUserResourceAccess::getAllSystemUsers(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaUserInstanceName& anInstanceName) {
    
    char ** users = get_system_users_list();
    char *  ret = NULL;
    int len = 0;
    
    if(users){
      for (int i=0; users[i]; i++)
	len = len + strlen(users[i]) + 4;
      
      ret =(char*) calloc(len,sizeof(char));
      
      for (int i=0; users[i]; i++){
	if(ret[0]=='\0')
	  sprintf(ret,"%s",users[i]);
	else
	  sprintf(ret,"%s, %s",ret,users[i]);
      }
    }
    
    return ret;
  }


	
}

