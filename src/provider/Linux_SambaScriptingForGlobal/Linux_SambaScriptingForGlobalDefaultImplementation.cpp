// =======================================================================
// Linux_SambaScriptingForGlobalDefaultImplementation.cpp
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

#include "Linux_SambaScriptingForGlobalDefaultImplementation.h"
#include "Linux_SambaScriptingForGlobalRepositoryInstance.h"
#include <iostream>

namespace genProvider {

  /* intrinsic methods */
  //----------------------------------------------------------------------------	
  void
  Linux_SambaScriptingForGlobalDefaultImplementation::enumInstanceNames(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    Linux_SambaScriptingForGlobalInstanceNameEnumeration& anInstanceNameEnumeration) {

#ifdef DEBUG
   	std::cout << "enumInstanceNames not supported for Linux_SambaScriptingForGlobal" << std::endl;
#endif   	

   	throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "enumInstanceEnumeration",
   	  "Linux_SambaScriptingForGlobal");   

  }

  //----------------------------------------------------------------------------	
  void 
  Linux_SambaScriptingForGlobalDefaultImplementation::enumInstances(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    Linux_SambaScriptingForGlobalManualInstanceEnumeration& anInstanceEnumeration) {

#ifdef DEBUG
    std::cout << "Using default enumInstances implementation for Linux_SambaScriptingForGlobal" << std::endl;
    std::cout << "Let's get the instanceNames" << std::endl;
#endif    

    Linux_SambaScriptingForGlobalInstanceNameEnumeration namesEnumeration;
    enumInstanceNames(aContext,aBroker,aNameSpaceP,namesEnumeration);

#ifdef DEBUG
    std::cout << "Getting each instance" << std::endl;
#endif    
    
    while (namesEnumeration.hasNext()) {
    
      Linux_SambaScriptingForGlobalInstanceName instanceName = namesEnumeration.getNext();
    
      Linux_SambaScriptingForGlobalRepositoryInstance repositoryInstance;

      // try to fetch repository instance
      try {
        Linux_SambaScriptingForGlobalInstanceName repositoryInstanceName(instanceName);
        repositoryInstanceName.setNamespace("IBMShadow/cimv2");
        CmpiObjectPath repositoryCmpiObjectPath = repositoryInstanceName.getObjectPath();
        CmpiBroker cmpiBroker(aBroker);
        CmpiInstance repositoryCmpiInstance = cmpiBroker.getInstance(
            aContext,
            repositoryCmpiObjectPath,
            aPropertiesPP);
        Linux_SambaScriptingForGlobalRepositoryInstance localRepositoryInstance(
      	  repositoryCmpiInstance,
          "IBMShadow/cimv2");
        repositoryInstance = localRepositoryInstance;
      } catch (const CmpiStatus& rc) { }                             
    
#ifdef DEBUG
    	std::cout << "Getting an instance for instanceName" << std::endl;
#endif
    	
    	Linux_SambaScriptingForGlobalManualInstance instance = getInstance(
    	  aContext,
    	  aBroker,
    	  aPropertiesPP,
    	  instanceName);

      // add the static data


#ifdef DEBUG
    	std::cout << "adding instance to enum" << std::endl;
#endif
    	
    	anInstanceEnumeration.addElement(instance);

#ifdef DEBUG
    	std::cout << "Added!" << std::endl;
#endif
    	
    }

  }

  //----------------------------------------------------------------------------	
  Linux_SambaScriptingForGlobalManualInstance 
  Linux_SambaScriptingForGlobalDefaultImplementation::getInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaScriptingForGlobalInstanceName& anInstanceName) {

#ifdef DEBUG
    std::cout << "getInstance not supported for Linux_SambaScriptingForGlobal" << std::endl;
#endif
    	

    throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "getInstance",
   	  "Linux_SambaScriptingForGlobal");

  }
  	
  //----------------------------------------------------------------------------	
  void 
  Linux_SambaScriptingForGlobalDefaultImplementation::setInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaScriptingForGlobalManualInstance& aManualInstance) {
  
#ifdef DEBUG
    std::cout << "setInstance not supported for Linux_SambaScriptingForGlobal" << std::endl;
#endif
    	
   
    throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "setInstance",
   	  "Linux_SambaScriptingForGlobal");
   	 
  }
  	
  //----------------------------------------------------------------------------	
  Linux_SambaScriptingForGlobalInstanceName  
  Linux_SambaScriptingForGlobalDefaultImplementation::createInstance(
    const CmpiContext& aContext, 
    const CmpiBroker& aBroker,
    const Linux_SambaScriptingForGlobalManualInstance& aManualInstance) {

#ifdef DEBUG
   	std::cout << "createInstance not supported for Linux_SambaScriptingForGlobal" << std::endl;
#endif

    throw CmpiErrorFormater::getErrorException(
   	 CmpiErrorFormater::NOT_IMPLEMENTED,
   	 "createInstance",
   	 "Linux_SambaScriptingForGlobal");

  }

  //----------------------------------------------------------------------------	
  void 
  Linux_SambaScriptingForGlobalDefaultImplementation::deleteInstance(
    const CmpiContext& aContext, 
    const CmpiBroker& aBroker,
    const Linux_SambaScriptingForGlobalInstanceName& anInstanceName) {

#ifdef DEBUG
   	std::cout << "deleteInstance not supported for Linux_SambaScriptingForGlobal" << std::endl;
#endif

    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "deleteInstance",
      "Linux_SambaScriptingForGlobal");

  }

  
  // Association Interface

  //----------------------------------------------------------------------------
  void
  Linux_SambaScriptingForGlobalDefaultImplementation::referencesManagedElement( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaScriptingOptionsInstanceName& aSourceInstance,
    Linux_SambaScriptingForGlobalManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "References(ManagedElement)",
      "Linux_SambaScriptingForGlobal");

  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaScriptingForGlobalDefaultImplementation::referencesSettingData( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalOptionsInstanceName& aSourceInstance,
    Linux_SambaScriptingForGlobalManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "References(SettingData)",
      "Linux_SambaScriptingForGlobal");

  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaScriptingForGlobalDefaultImplementation::associatorsManagedElement(
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaScriptingOptionsInstanceName& aSourceInstance,
    Linux_SambaGlobalOptionsInstanceEnumeration& anInstanceEnumeration) {
      
#ifdef DEBUG
    std::cout<<"Linux_SambaScriptingForGlobal : associatorsLinux_SambaGlobalOptions() ... returns one instance"<<std::endl;
#endif    
      
    Linux_SambaScriptingForGlobalManualInstanceEnumeration manualInstanceEnumeration;
      
    referencesManagedElement(
      aContext,
      aBroker,
      aSourceInstance.getNamespace(), 
      aPropertiesPP,
      aSourceInstance,
      manualInstanceEnumeration);

    Linux_SambaGlobalOptionsExternal external(aBroker,aContext);

    while (manualInstanceEnumeration.hasNext()) {
      const Linux_SambaScriptingForGlobalManualInstance manualInstance = manualInstanceEnumeration.getNext();
      const Linux_SambaScriptingForGlobalInstanceName instanceName = manualInstance.getInstanceName();
      const Linux_SambaGlobalOptionsInstanceName ManagedElement = instanceName.getManagedElement();
      Linux_SambaGlobalOptionsInstance instance = external.getInstance(aPropertiesPP,ManagedElement);
      anInstanceEnumeration.addElement(instance);
    }
  
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaScriptingForGlobalDefaultImplementation::associatorsSettingData( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalOptionsInstanceName& aSourceInstance,
    Linux_SambaScriptingOptionsInstanceEnumeration& anInstanceEnumeration) {
     
#ifdef DEBUG
    std::cout << "Linux_SambaScriptingForGlobal : associatorsLinux_SambaScriptingOptions() ... returns one instance" << std::endl;
#endif    
      
    Linux_SambaScriptingForGlobalManualInstanceEnumeration manualInstanceEnumeration;
      
    referencesSettingData(
      aContext,
      aBroker,
      aSourceInstance.getNamespace(), 
      aPropertiesPP,
      aSourceInstance,
      manualInstanceEnumeration);

    Linux_SambaScriptingOptionsExternal external(aBroker,aContext);

    while(manualInstanceEnumeration.hasNext()) {
      const Linux_SambaScriptingForGlobalManualInstance manualInstance = manualInstanceEnumeration.getNext();
      const Linux_SambaScriptingForGlobalInstanceName instanceName = manualInstance.getInstanceName();
      const Linux_SambaScriptingOptionsInstanceName SettingData = instanceName.getSettingData();
      Linux_SambaScriptingOptionsInstance instance = external.getInstance(aPropertiesPP,SettingData);
      anInstanceEnumeration.addElement(instance);
    }

  }

  /* extrinsic methods */
  

}
