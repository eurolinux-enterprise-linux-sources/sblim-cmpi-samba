// =======================================================================
// Linux_SambaForceUserForPrinterResourceAccess.cpp
//     created on Fri, 23 Jun 2006 using ECUTE 2.2.1
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
#include "Linux_SambaForceUserForPrinterResourceAccess.h"

#include <errno.h>
#include <string>
#include <list>

#include "smt_smb_ra_support.h"
#include "smt_smb_defaultvalues.h"
#include "smt_smb_array.h"

extern int errno;

namespace genProvider {
  
  //----------------------------------------------------------------------------
  // manual written methods

  static bool validUser(const char* user) {
    char ** users = get_samba_users_list();
    if (!users && errno)
      throw CmpiStatus(CMPI_RC_ERR_FAILED, "Failed to retrieve Samba user list!");
    if(users){
      for (int i=0; users[i]; i++){
	if(!strcmp(users[i],user))
	  return true;
      }
    }
    return false;
  };
  

  //----------------------------------------------------------------------------


  //----------------------------------------------------------------------------
  //Linux_SambaForceUserForPrinterResourceAccess::Linux_SambaForceUserForPrinterResourceAccess();

  //----------------------------------------------------------------------------
  Linux_SambaForceUserForPrinterResourceAccess::~Linux_SambaForceUserForPrinterResourceAccess() {
    terminator();
  }
    
  // intrinsic methods

  //----------------------------------------------------------------------------
  void
  Linux_SambaForceUserForPrinterResourceAccess::enumInstanceNames(
     const CmpiContext& aContext,
     const CmpiBroker& aBroker,
     const char* aNameSpaceP,
     Linux_SambaForceUserForPrinterInstanceNameEnumeration& anInstanceNameEnumeration) {
      
    char ** printers = get_samba_printers_list();
    if(printers){
      for (int i=0; printers[i]; i++){
	
	Linux_SambaPrinterOptionsInstanceName printerInstName;
	printerInstName.setNamespace(aNameSpaceP);
	printerInstName.setName(printers[i]);
	printerInstName.setInstanceID(DEFAULT_INSTANCE_ID);
	
	char* user = get_option(printers[i],"force user");
	
	if(user && validUser(user)){
	  Linux_SambaForceUserForPrinterInstanceName assocName;
	  assocName.setNamespace(aNameSpaceP);
	  assocName.setGroupComponent(printerInstName);
	  
	  Linux_SambaUserInstanceName userInstName;
	  userInstName.setNamespace(aNameSpaceP);
	  userInstName.setSambaUserName( user );
	  
	  assocName.setPartComponent(userInstName);
	  
	  anInstanceNameEnumeration.addElement(assocName);
	}
      }
    }
  }
  
  
  //----------------------------------------------------------------------------

  void
  Linux_SambaForceUserForPrinterResourceAccess::enumInstances(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    Linux_SambaForceUserForPrinterManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    char ** printers = get_samba_printers_list();
    if(printers){
      for (int i=0; printers[i]; i++){
	
	Linux_SambaPrinterOptionsInstanceName printerInstName;
	printerInstName.setNamespace(aNameSpaceP);
	printerInstName.setName(printers[i]);
	printerInstName.setInstanceID(DEFAULT_INSTANCE_ID);
	
	char* user = get_option(printers[i],"force user");
	
	if(user && validUser(user)){
	  Linux_SambaForceUserForPrinterManualInstance manualInstance;
	  
	  Linux_SambaForceUserForPrinterInstanceName instName;
	  instName.setNamespace(aNameSpaceP);
	  instName.setGroupComponent(printerInstName);
	  
	  Linux_SambaUserInstanceName userInstName;
	  userInstName.setNamespace(aNameSpaceP);
	  userInstName.setSambaUserName( user );
	  
	  instName.setPartComponent(userInstName);
	  
	  manualInstance.setInstanceName(instName);
	  aManualInstanceEnumeration.addElement(manualInstance);
	}
      }      
    }
  }
  
  
  //----------------------------------------------------------------------------

  Linux_SambaForceUserForPrinterManualInstance 
  Linux_SambaForceUserForPrinterResourceAccess::getInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaForceUserForPrinterInstanceName& anInstanceName) {

    Linux_SambaForceUserForPrinterManualInstance aManualInstance;
    aManualInstance.setInstanceName(anInstanceName);

    char ** printers = get_samba_printers_list();
    if(printers) {
    int valid_printer = false;
        for(int i=0;printers[i];i++) {
           if(strcasecmp(anInstanceName.getGroupComponent().getName(),printers[i])==0 &&
              strcasecmp(anInstanceName.getGroupComponent().getInstanceID(),DEFAULT_INSTANCE_ID)==0)
                valid_printer = true;
        }
        if(!valid_printer) {
           throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified printer is unknown!");
        }
    } else {
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist!");
    }

    if (!validUser(anInstanceName.getPartComponent().getSambaUserName())) {
      throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified Samba user does not exist!");
    }

   SambaArray array = SambaArray();
   char * user_list = get_option(anInstanceName.getGroupComponent().getName(),"force user");

   if(!user_list) {
     throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified Samba user does not have force user enabled for the specified printer instance!");
   }

   array.populate(user_list);
   if(!array.isPresent(anInstanceName.getPartComponent().getSambaUserName())) {
     throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified Samba user does not have force user enabled for the specified printer instance!");
   }    

    return aManualInstance;
  }

  //----------------------------------------------------------------------------
  /*
  void
  Linux_SambaForceUserForPrinterResourceAccess::setInstance(
     const CmpiContext& aContext,
     const CmpiBroker& aBroker,
     const char** aPropertiesPP,
     const Linux_SambaForceUserForPrinterManualInstance& aManualInstance) { }
  */
  
  //----------------------------------------------------------------------------

  Linux_SambaForceUserForPrinterInstanceName
  Linux_SambaForceUserForPrinterResourceAccess::createInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaForceUserForPrinterManualInstance& aManualInstance) {
    
    char ** printers = get_samba_printers_list();
    if(printers) {
        int valid_printer = false;
        for(int i=0;printers[i];i++) {
           if(strcasecmp(aManualInstance.getInstanceName().getGroupComponent().getName(),printers[i])==0 &&
              strcasecmp(aManualInstance.getInstanceName().getGroupComponent().getInstanceID(),DEFAULT_INSTANCE_ID)==0)
                valid_printer = true;
        }
        if(!valid_printer) {
           throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified printer is unknown!");
        }
    } else {
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist!");
    }

    if(!validUser(aManualInstance.getInstanceName().getPartComponent().getSambaUserName())){
      throw CmpiStatus(CMPI_RC_ERR_INVALID_PARAMETER,"The specified Samba user does not exist!");
    }

    char* user = get_option(aManualInstance.getInstanceName().getGroupComponent().getName(),"force user");
    char* g_user = get_global_option("force user");

    if (!user || (g_user && strcasecmp(user,g_user)==0)) {
      set_printer_option(aManualInstance.getInstanceName().getGroupComponent().getName(),"force user",aManualInstance.getInstanceName().getPartComponent().getSambaUserName());
    } else {
      throw CmpiStatus(CMPI_RC_ERR_ALREADY_EXISTS,"There is an existent instance already!");
    }
    
    return aManualInstance.getInstanceName();
  }

  
  //----------------------------------------------------------------------------

  void
  Linux_SambaForceUserForPrinterResourceAccess::deleteInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const Linux_SambaForceUserForPrinterInstanceName& anInstanceName) {
    
    char ** printers = get_samba_printers_list();
    if(printers) {
    int valid_printer = false;
        for(int i=0;printers[i];i++) {
           if(strcasecmp(anInstanceName.getGroupComponent().getName(),printers[i])==0 &&
              strcasecmp(anInstanceName.getGroupComponent().getInstanceID(),DEFAULT_INSTANCE_ID)==0)
                valid_printer = true;
        }
        if(!valid_printer) {
           throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified printer is unknown!");
        }
    } else {
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist!");
    }

    if (!validUser(anInstanceName.getPartComponent().getSambaUserName())) {
      throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist. The specified Samba user does not exist!");
    }

    set_printer_option(anInstanceName.getGroupComponent().getName(),"force user",NULL);
  }

	

  // Association Interface
  //----------------------------------------------------------------------------

  void Linux_SambaForceUserForPrinterResourceAccess::referencesPartComponent( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaPrinterOptionsInstanceName& aSourceInstanceName,
    Linux_SambaForceUserForPrinterManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    char ** printers = get_samba_printers_list();
    if(printers) {
    int valid_printer = false;
        for(int i=0;printers[i];i++) {
           if(strcasecmp(aSourceInstanceName.getName(),printers[i])==0 &&
              strcasecmp(aSourceInstanceName.getInstanceID(), DEFAULT_INSTANCE_ID)==0)
                valid_printer = true;
        }
        if(!valid_printer) {
           throw CmpiStatus(CMPI_RC_ERR_INVALID_PARAMETER,"The Instance does not exist. The specified printer is unknown!");
        }
    } else {
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist!");
    }

    char* user = get_option(aSourceInstanceName.getName(),"force user");
    
    if(user && validUser(user)){
      Linux_SambaForceUserForPrinterManualInstance manualInstance;
      
      Linux_SambaForceUserForPrinterInstanceName instName;
      instName.setNamespace(aNameSpaceP);
      instName.setGroupComponent(aSourceInstanceName);
      
      Linux_SambaUserInstanceName userInstName;
      userInstName.setNamespace(aNameSpaceP);
      userInstName.setSambaUserName( user );
      
      instName.setPartComponent(userInstName);
      
      manualInstance.setInstanceName(instName);
      aManualInstanceEnumeration.addElement(manualInstance);
    }
  }

  
  //----------------------------------------------------------------------------

  void Linux_SambaForceUserForPrinterResourceAccess::referencesGroupComponent( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaUserInstanceName& aSourceInstanceName,
    Linux_SambaForceUserForPrinterManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    char ** printers = get_samba_printers_list();
    
    if(printers){
      for (int i=0; printers[i]; i++){
	char* user = get_option(printers[i],"force user");
	
	if(user && validUser(user)){
	  if(!strcmp(user,aSourceInstanceName.getSambaUserName())){
	    Linux_SambaForceUserForPrinterManualInstance manualInstance;
	    
	    Linux_SambaForceUserForPrinterInstanceName instName;
	    instName.setNamespace(aNameSpaceP);
	    instName.setPartComponent(aSourceInstanceName);
	    
	    Linux_SambaPrinterOptionsInstanceName printerInstName;
	    printerInstName.setNamespace(aNameSpaceP);
	    printerInstName.setName(printers[i]);
	    printerInstName.setInstanceID(DEFAULT_INSTANCE_ID);
	    
	    instName.setGroupComponent(printerInstName);
	    
	    manualInstance.setInstanceName(instName);
	    aManualInstanceEnumeration.addElement(manualInstance);
	  }
	}
      }
    } else {
       throw CmpiStatus(CMPI_RC_ERR_INVALID_PARAMETER,"The Instance does note exist. The specified Samba user is unknown!");
    }
  }

  
  //----------------------------------------------------------------------------

  void Linux_SambaForceUserForPrinterResourceAccess::associatorsPartComponent( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaPrinterOptionsInstanceName& aSourceInstanceName,
    Linux_SambaUserInstanceEnumeration& anInstanceEnumeration) {
    
    char ** printers = get_samba_printers_list();
    if(printers) {
    int valid_printer = false;
        for(int i=0;printers[i];i++) {
           if(strcasecmp(aSourceInstanceName.getName(),printers[i])==0 &&
              strcasecmp(aSourceInstanceName.getInstanceID(),DEFAULT_INSTANCE_ID)==0)
                valid_printer = true;
        }
        if(!valid_printer) {
           throw CmpiStatus(CMPI_RC_ERR_INVALID_PARAMETER,"The Instance does not exist. The specified printer is unknown!");
        }
    } else {
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND,"The Instance does not exist!");
    }

    char* user = get_option(aSourceInstanceName.getName(),"force user");
    
    if(user && validUser(user)){
      Linux_SambaUserInstance instance;
      
      Linux_SambaUserInstanceName userInstName;
      userInstName.setNamespace(aNameSpaceP);
      userInstName.setSambaUserName( user );
      
      instance.setInstanceName(userInstName);
      char* option;
      
      option = get_user_unix_name( user );
      if ( option )
	instance.setSystemUserName( option );
      
      anInstanceEnumeration.addElement(instance);
    }
  }

  
  //----------------------------------------------------------------------------

  void Linux_SambaForceUserForPrinterResourceAccess::associatorsGroupComponent( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaUserInstanceName& aSourceInstanceName,
    Linux_SambaPrinterOptionsInstanceEnumeration& anInstanceEnumeration) {
    
    char ** printers = get_samba_printers_list();
    
    if(printers){
      for (int i=0; printers[i]; i++){
	char* user = get_option(printers[i],"force user");
	if(user && validUser(user)){
	  if(!strcmp(user,aSourceInstanceName.getSambaUserName())) {
	    Linux_SambaPrinterOptionsInstance instance;
	    
	    Linux_SambaPrinterOptionsInstanceName printerInstName;
	    printerInstName.setNamespace(aNameSpaceP);
	    printerInstName.setName(printers[i]);
	    printerInstName.setInstanceID(DEFAULT_INSTANCE_ID);
	    
	    instance.setInstanceName(printerInstName);
	    
	    char *option;
	    
	    option = get_option(printers[i],"available");	
	    if ( option )
	      if(strcasecmp(option,"yes") == 0)
		instance.setAvailable( true );
	      else
		instance.setAvailable( false );
	      
	    option = get_option(printers[i],"comment");
	    if ( option )
	      instance.setComment(option);
	    
	    option = get_option(printers[i],"path");
	    if ( option )
	      instance.setPath(option);
	    
	    option = get_option(printers[i],"printable");	
	    if ( option )
	      if(strcasecmp(option,"yes") == 0)
		instance.setPrintable( true );
	      else
		instance.setPrintable( false );
	    
	    option = get_option(printers[i],"printer name");	
	    if ( option )
	      instance.setSystemPrinterName( option );
	    
	    anInstanceEnumeration.addElement(instance);
	  }
	}
      }
    } else {
       throw CmpiStatus(CMPI_RC_ERR_INVALID_PARAMETER,"The Instance does note exist. The specified Samba user is unknown!");
    }
  }
  
   
  
  // extrinsic methods

	
}


