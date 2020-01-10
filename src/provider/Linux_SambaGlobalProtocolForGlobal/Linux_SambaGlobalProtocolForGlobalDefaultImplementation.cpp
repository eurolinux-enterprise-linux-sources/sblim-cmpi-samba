// =======================================================================
// Linux_SambaGlobalProtocolForGlobalDefaultImplementation.cpp
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

#include "Linux_SambaGlobalProtocolForGlobalDefaultImplementation.h"
#include "Linux_SambaGlobalProtocolForGlobalRepositoryInstance.h"
#include <iostream>

namespace genProvider {

  /* intrinsic methods */
  //----------------------------------------------------------------------------	
  void
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::enumInstanceNames(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    Linux_SambaGlobalProtocolForGlobalInstanceNameEnumeration& anInstanceNameEnumeration) {

#ifdef DEBUG
   	std::cout << "enumInstanceNames not supported for Linux_SambaGlobalProtocolForGlobal" << std::endl;
#endif   	

   	throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "enumInstanceEnumeration",
   	  "Linux_SambaGlobalProtocolForGlobal");   

  }

  //----------------------------------------------------------------------------	
  void 
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::enumInstances(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    Linux_SambaGlobalProtocolForGlobalManualInstanceEnumeration& anInstanceEnumeration) {

#ifdef DEBUG
    std::cout << "Using default enumInstances implementation for Linux_SambaGlobalProtocolForGlobal" << std::endl;
    std::cout << "Let's get the instanceNames" << std::endl;
#endif    

    Linux_SambaGlobalProtocolForGlobalInstanceNameEnumeration namesEnumeration;
    enumInstanceNames(aContext,aBroker,aNameSpaceP,namesEnumeration);

#ifdef DEBUG
    std::cout << "Getting each instance" << std::endl;
#endif    
    
    while (namesEnumeration.hasNext()) {
    
      Linux_SambaGlobalProtocolForGlobalInstanceName instanceName = namesEnumeration.getNext();
    
      Linux_SambaGlobalProtocolForGlobalRepositoryInstance repositoryInstance;

      // try to fetch repository instance
      try {
        Linux_SambaGlobalProtocolForGlobalInstanceName repositoryInstanceName(instanceName);
        repositoryInstanceName.setNamespace("IBMShadow/cimv2");
        CmpiObjectPath repositoryCmpiObjectPath = repositoryInstanceName.getObjectPath();
        CmpiBroker cmpiBroker(aBroker);
        CmpiInstance repositoryCmpiInstance = cmpiBroker.getInstance(
            aContext,
            repositoryCmpiObjectPath,
            aPropertiesPP);
        Linux_SambaGlobalProtocolForGlobalRepositoryInstance localRepositoryInstance(
      	  repositoryCmpiInstance,
          "IBMShadow/cimv2");
        repositoryInstance = localRepositoryInstance;
      } catch (const CmpiStatus& rc) { }                             
    
#ifdef DEBUG
    	std::cout << "Getting an instance for instanceName" << std::endl;
#endif
    	
    	Linux_SambaGlobalProtocolForGlobalManualInstance instance = getInstance(
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
  Linux_SambaGlobalProtocolForGlobalManualInstance 
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::getInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaGlobalProtocolForGlobalInstanceName& anInstanceName) {

#ifdef DEBUG
    std::cout << "getInstance not supported for Linux_SambaGlobalProtocolForGlobal" << std::endl;
#endif
    	

    throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "getInstance",
   	  "Linux_SambaGlobalProtocolForGlobal");

  }
  	
  //----------------------------------------------------------------------------	
  void 
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::setInstance(
    const CmpiContext& aContext,
    const CmpiBroker& aBroker,
    const char** aPropertiesPP,
    const Linux_SambaGlobalProtocolForGlobalManualInstance& aManualInstance) {
  
#ifdef DEBUG
    std::cout << "setInstance not supported for Linux_SambaGlobalProtocolForGlobal" << std::endl;
#endif
    	
   
    throw CmpiErrorFormater::getErrorException(
   	  CmpiErrorFormater::NOT_IMPLEMENTED,
   	  "setInstance",
   	  "Linux_SambaGlobalProtocolForGlobal");
   	 
  }
  	
  //----------------------------------------------------------------------------	
  Linux_SambaGlobalProtocolForGlobalInstanceName  
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::createInstance(
    const CmpiContext& aContext, 
    const CmpiBroker& aBroker,
    const Linux_SambaGlobalProtocolForGlobalManualInstance& aManualInstance) {

#ifdef DEBUG
   	std::cout << "createInstance not supported for Linux_SambaGlobalProtocolForGlobal" << std::endl;
#endif

    throw CmpiErrorFormater::getErrorException(
   	 CmpiErrorFormater::NOT_IMPLEMENTED,
   	 "createInstance",
   	 "Linux_SambaGlobalProtocolForGlobal");

  }

  //----------------------------------------------------------------------------	
  void 
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::deleteInstance(
    const CmpiContext& aContext, 
    const CmpiBroker& aBroker,
    const Linux_SambaGlobalProtocolForGlobalInstanceName& anInstanceName) {

#ifdef DEBUG
   	std::cout << "deleteInstance not supported for Linux_SambaGlobalProtocolForGlobal" << std::endl;
#endif

    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "deleteInstance",
      "Linux_SambaGlobalProtocolForGlobal");

  }

  
  // Association Interface

  //----------------------------------------------------------------------------
  void
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::referencesSettingData( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalOptionsInstanceName& aSourceInstance,
    Linux_SambaGlobalProtocolForGlobalManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "References(SettingData)",
      "Linux_SambaGlobalProtocolForGlobal");

  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::referencesManagedElement( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalProtocolOptionsInstanceName& aSourceInstance,
    Linux_SambaGlobalProtocolForGlobalManualInstanceEnumeration& aManualInstanceEnumeration) {
    
    throw CmpiErrorFormater::getErrorException(
      CmpiErrorFormater::NOT_IMPLEMENTED,
      "References(ManagedElement)",
      "Linux_SambaGlobalProtocolForGlobal");

  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::associatorsSettingData(
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalOptionsInstanceName& aSourceInstance,
    Linux_SambaGlobalProtocolOptionsInstanceEnumeration& anInstanceEnumeration) {
      
#ifdef DEBUG
    std::cout<<"Linux_SambaGlobalProtocolForGlobal : associatorsLinux_SambaGlobalProtocolOptions() ... returns one instance"<<std::endl;
#endif    
      
    Linux_SambaGlobalProtocolForGlobalManualInstanceEnumeration manualInstanceEnumeration;
      
    referencesSettingData(
      aContext,
      aBroker,
      aSourceInstance.getNamespace(), 
      aPropertiesPP,
      aSourceInstance,
      manualInstanceEnumeration);

    Linux_SambaGlobalProtocolOptionsExternal external(aBroker,aContext);

    while (manualInstanceEnumeration.hasNext()) {
      const Linux_SambaGlobalProtocolForGlobalManualInstance manualInstance = manualInstanceEnumeration.getNext();
      const Linux_SambaGlobalProtocolForGlobalInstanceName instanceName = manualInstance.getInstanceName();
      const Linux_SambaGlobalProtocolOptionsInstanceName SettingData = instanceName.getSettingData();
      Linux_SambaGlobalProtocolOptionsInstance instance = external.getInstance(aPropertiesPP,SettingData);
      anInstanceEnumeration.addElement(instance);
    }
  
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaGlobalProtocolForGlobalDefaultImplementation::associatorsManagedElement( 
    const CmpiContext& aContext,  
    const CmpiBroker& aBroker,
    const char* aNameSpaceP,
    const char** aPropertiesPP,
    const Linux_SambaGlobalProtocolOptionsInstanceName& aSourceInstance,
    Linux_SambaGlobalOptionsInstanceEnumeration& anInstanceEnumeration) {
     
#ifdef DEBUG
    std::cout << "Linux_SambaGlobalProtocolForGlobal : associatorsLinux_SambaGlobalOptions() ... returns one instance" << std::endl;
#endif    
      
    Linux_SambaGlobalProtocolForGlobalManualInstanceEnumeration manualInstanceEnumeration;
      
    referencesManagedElement(
      aContext,
      aBroker,
      aSourceInstance.getNamespace(), 
      aPropertiesPP,
      aSourceInstance,
      manualInstanceEnumeration);

    Linux_SambaGlobalOptionsExternal external(aBroker,aContext);

    while(manualInstanceEnumeration.hasNext()) {
      const Linux_SambaGlobalProtocolForGlobalManualInstance manualInstance = manualInstanceEnumeration.getNext();
      const Linux_SambaGlobalProtocolForGlobalInstanceName instanceName = manualInstance.getInstanceName();
      const Linux_SambaGlobalOptionsInstanceName ManagedElement = instanceName.getManagedElement();
      Linux_SambaGlobalOptionsInstance instance = external.getInstance(aPropertiesPP,ManagedElement);
      anInstanceEnumeration.addElement(instance);
    }

  }

  /* extrinsic methods */
  

}
