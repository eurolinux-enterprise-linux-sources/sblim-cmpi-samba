// =======================================================================
// CmpiLinux_SambaGlobalOptionsProvider.cpp
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
//                Riyashmon Haneefa  <riyashh1@in.ibm.com>
//
// =======================================================================
#include "CmpiLinux_SambaGlobalOptionsProvider.h"
#include "ArrayConverter.h"
#include "Linux_SambaGlobalOptionsManualInstance.h"
#include "Linux_SambaGlobalOptionsRepositoryInstance.h"


#include <iostream>
#include <strings.h>

namespace genProvider {

  //----------------------------------------------------------------------------
  CmpiLinux_SambaGlobalOptionsProvider::CmpiLinux_SambaGlobalOptionsProvider(
    const CmpiBroker& aBroker, 
    const CmpiContext& aContext)
    : CmpiBaseMI(aBroker,aContext), 
    CmpiInstanceMI(aBroker,aContext),
    CmpiMethodMI(aBroker,aContext),
    m_cmpiBroker(aBroker) {
      
    m_interfaceP = Linux_SambaGlobalOptionsFactory::getImplementation();           

#ifdef DEBUG 
    std::cout << "Provider was constructed" << std::endl;
#endif    
  
  }
        
  //----------------------------------------------------------------------------
  CmpiLinux_SambaGlobalOptionsProvider::~CmpiLinux_SambaGlobalOptionsProvider() {
    delete m_interfaceP;
  }
  
  //----------------------------------------------------------------------------
  int 
  CmpiLinux_SambaGlobalOptionsProvider::isUnloadable() const {
    return 0;
  }
	
  //----------------------------------------------------------------------------
  void 
  CmpiLinux_SambaGlobalOptionsProvider::completeInstance(
    const Linux_SambaGlobalOptionsInstanceName& anInstanceName,
    CmpiInstance& anInstance, 
    const CmpiContext& aContext) {
	  	
    Linux_SambaGlobalOptionsInstanceName shadowInstanceName(anInstanceName);
    shadowInstanceName.setNamespace("IBMShadow/cimv2");
    CmpiObjectPath cmpiObjectPath = shadowInstanceName.getObjectPath();
	  
    try {
      const char* propertiesP = 0;
      CmpiInstance shadowInstance = m_cmpiBroker.getInstance(
        aContext, 
        cmpiObjectPath,
        &propertiesP);
      copyShadowData(&shadowInstance,&anInstance);
    } catch (const CmpiStatus& rc) {}                             
  
  }
	
  //----------------------------------------------------------------------------
  void 
  CmpiLinux_SambaGlobalOptionsProvider::copyShadowData(
    const CmpiInstance* aSourceInstanceP, 
    CmpiInstance* aTargetInstanceP) {

    if (aSourceInstanceP && aTargetInstanceP) {
      
    }

  }

  //----------------------------------------------------------------------------
  CmpiInstance* 
  CmpiLinux_SambaGlobalOptionsProvider::getShadowInstance(
    const CmpiInstance& anInstance,
    const Linux_SambaGlobalOptionsInstanceName& anInstanceName) {
     
    Linux_SambaGlobalOptionsInstanceName shadowInstanceName(anInstanceName);
    shadowInstanceName.setNamespace("IBMShadow/cimv2");
    CmpiObjectPath cmpiObjectPath = shadowInstanceName.getObjectPath();
      
    CmpiInstance* targetP = new CmpiInstance(cmpiObjectPath);
      
    if (targetP) {
      copyShadowData(&anInstance,targetP);
      if (0 == targetP->getPropertyCount()) {
        delete targetP;
        targetP = 0;
      }
    }
  
    return targetP;
  
  }

  //----------------------------------------------------------------------------
  void
  CmpiLinux_SambaGlobalOptionsProvider::removeDanglingShadowInstances (
   const Linux_SambaGlobalOptionsInstanceNameEnumeration& anInstanceNameEnumerations) {
	
    // TODO: enumerate shadow instance names and remove those not included
	  // in anInstanceNameEnumeration
	
  }
	
  //----------------------------------------------------------------------------
  //                          Provider Factory
  //----------------------------------------------------------------------------
  CMProviderBase(CmpiLinux_SambaGlobalOptionsProvider);

  CMInstanceMIFactory(
    CmpiLinux_SambaGlobalOptionsProvider, 
    CmpiLinux_SambaGlobalOptionsProvider);

  CMMethodMIFactory(
    CmpiLinux_SambaGlobalOptionsProvider, 
    CmpiLinux_SambaGlobalOptionsProvider);
	
	
  //----------------------------------------------------------------------------
  //                      Instance Provider Interface
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  CmpiStatus 
  CmpiLinux_SambaGlobalOptionsProvider::enumInstanceNames(
    const CmpiContext& aContext, 
    CmpiResult& aResult,
    const CmpiObjectPath& aCop) {
      
#ifdef DEBUG 
    std::cout << "enumerating instanceNames" << std::endl;
#endif

    CmpiString nameSpace = aCop.getNameSpace();
    const char* nameSpaceP = nameSpace.charPtr();

    Linux_SambaGlobalOptionsInstanceNameEnumeration enumeration;
    m_interfaceP->enumInstanceNames(
      aContext,
      m_cmpiBroker,
      nameSpaceP,
      enumeration);
                   
    while (enumeration.hasNext() ){
      const Linux_SambaGlobalOptionsInstanceName& instanceName = enumeration.getNext();
      CmpiObjectPath objectPath = instanceName.getObjectPath();
      aResult.returnData(objectPath);
    }
      
    // we make housekeeping
    removeDanglingShadowInstances(enumeration);
      
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);

  }

  //----------------------------------------------------------------------------
  CmpiStatus 
  CmpiLinux_SambaGlobalOptionsProvider::enumInstances(
    const CmpiContext& aContext,
    CmpiResult& aResult,
    const CmpiObjectPath& aCop, 
    const char** aPropertiesPP) {
     
#ifdef DEBUG 
    std::cout << "enumerating instances" << std::endl;
#endif

    CmpiString nameSpace = aCop.getNameSpace();
    const char* nameSpaceP = nameSpace.charPtr();
      
    Linux_SambaGlobalOptionsManualInstanceEnumeration enumeration;
    m_interfaceP->enumInstances(
      aContext, 
      m_cmpiBroker, 
      nameSpaceP, 
      aPropertiesPP,
      enumeration);

#ifdef DEBUG 
    std::cout << "enumerated" << std::endl;
#endif
      
    while (enumeration.hasNext()) {
   	  const Linux_SambaGlobalOptionsManualInstance& instance = enumeration.getNext();
      	
#ifdef DEBUG 
      std::cout << "enumerating getNext" << std::endl;
#endif
      	
      CmpiInstance cmpiInstance = instance.getCmpiInstance(aPropertiesPP);

#ifdef DEBUG 
      std::cout << "transformed" << std::endl;
#endif
      	
      //add the static data
      // MJ: No, this is done in the implementation (or DefaultImplementation)
      // completeInstance(instance.getInstanceName(),cmpiInstance,aContext);
      	
      aResult.returnData(cmpiInstance);
    
    }
      
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);
  
  }
    
  //----------------------------------------------------------------------------
  CmpiStatus 
  CmpiLinux_SambaGlobalOptionsProvider::getInstance (
    const CmpiContext& aContext, 
    CmpiResult& aResult,
    const CmpiObjectPath& aCop,
    const char** aPropertiesPP) {
     	
    // convert to instanceName
    Linux_SambaGlobalOptionsInstanceName instanceName(aCop);
    
    /*
    CmpiInstance* repositoryCmpiInstanceP = 0;
    
    // try to fetch repository instance
    try {
      Linux_SambaGlobalOptionsInstanceName repositoryInstanceName(instanceName);
      repositoryInstanceName.setNamespace("IBMShadow/cimv2");
      CmpiObjectPath repositoryCmpiObjectPath = repositoryInstanceName.getObjectPath();
      repositoryCmpiInstanceP = new CmpiInstance(
        m_cmpiBroker.getInstance(
          aContext, 
          repositoryCmpiObjectPath,
          aPropertiesPP));
    } catch (const CmpiStatus& rc) { }                             
    */

    // get instance for instanceName
    Linux_SambaGlobalOptionsManualInstance instance;
    instance = m_interfaceP->getInstance(
      aContext,
      m_cmpiBroker,
      aPropertiesPP,
      instanceName);
      
    // convert the instance in a cmpiInstance
    CmpiInstance cmpiInstance = instance.getCmpiInstance(aPropertiesPP);
      
    /*
    // add the static data 
    copyShadowData(repositoryCmpiInstanceP,&cmpiInstance);
    
    if (repositoryCmpiInstanceP) {
      delete repositoryCmpiInstanceP;
    }
    */

    aResult.returnData(cmpiInstance);
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);

  }
    
  //----------------------------------------------------------------------------
  CmpiStatus 
  CmpiLinux_SambaGlobalOptionsProvider::createInstance (
    const CmpiContext& aContext,
    CmpiResult& aResult,
    const CmpiObjectPath& aCop,
    const CmpiInstance& aCmpiInstance) {
   	
   	Linux_SambaGlobalOptionsManualInstance manualInstance(
      aCmpiInstance,
      aCop.getNameSpace().charPtr());
    
    //REPOSITORY DATA    
//    CmpiInstance* backupShadowInstanceP = 0;
//   	CmpiInstance shadowInstance = 
//   	  Linux_SambaGlobalOptionsRepositoryInstance(aCmpiInstance,"IBMShadow/cimv2").getCmpiInstance(0);     
//     
//   	//We keep a backup of the existing data for recovering previous
//   	//state if the resource access raise an exception
//   	CmpiObjectPath shadowOp = shadowInstance.getObjectPath();
//    try {
//   	  backupShadowInstanceP = new CmpiInstance(
//        m_cmpiBroker.getInstance(aContext,shadowOp,0));
//   	  //if the shadow instance exist we delete it
//   	  m_cmpiBroker.deleteInstance(aContext,shadowOp);   	    
//   	} catch (CmpiStatus& rc) {}   	
//    m_cmpiBroker.createInstance(aContext,shadowOp,shadowInstance);     
//    
    // resource access data (manual instance)   
    try { 
			aResult.returnData(m_interfaceP->createInstance(aContext, m_cmpiBroker, manualInstance).
			getObjectPath());
    } catch (CmpiStatus& rc) {
//      //If something went wrong we recover the previous state
//      m_cmpiBroker.deleteInstance(aContext,shadowOp);
//      if (backupShadowInstanceP) {
//        m_cmpiBroker.createInstance(aContext,shadowOp,*backupShadowInstanceP);
//      }
      throw rc;
    }
    
//    if (backupShadowInstanceP) {
//      delete(backupShadowInstanceP);
//    }
    
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);
  
  }
    
  //----------------------------------------------------------------------------
  CmpiStatus 
  CmpiLinux_SambaGlobalOptionsProvider::setInstance (
    const CmpiContext& aContext,
    CmpiResult& aResult,
    const CmpiObjectPath& aCop,
    const CmpiInstance& aCmpiInstance,
    const char** aPropertiesPP) {
   	
   	Linux_SambaGlobalOptionsManualInstance manualInstance(
      aCmpiInstance,
      aCop.getNameSpace().charPtr());
    
    //REPOSITORY DATA    
//    CmpiInstance* backupShadowInstanceP = 0;
//    CmpiInstance shadowInstance =
//      Linux_SambaGlobalOptionsRepositoryInstance(aCmpiInstance,"IBMShadow/cimv2").getCmpiInstance(0);     
//     
//   	//We keep a backup of the existing data for recovering previous
//   	//state if the resource access raise an exception
//   	CmpiObjectPath shadowOp = shadowInstance.getObjectPath();
//    try {
//   	  backupShadowInstanceP = new CmpiInstance(
//   	   m_cmpiBroker.getInstance(aContext,shadowOp,0));
//   	} catch (CmpiStatus& rc) {}   	
//    
//    //if the instance existed before we delete it
//    //(setInstance is buggy in Pegasus)
//    if (backupShadowInstanceP) {
//      m_cmpiBroker.setInstance(aContext,shadowOp,shadowInstance,aPropertiesPP);
//    } else {
//      m_cmpiBroker.createInstance(aContext,shadowOp,shadowInstance);
//    }
    
    // resource access data (manual instance)   
    try {
      m_interfaceP->setInstance(aContext,m_cmpiBroker,aPropertiesPP,manualInstance);
    } catch (CmpiStatus& rc) {
      //If something went wrong we recover the previous state
//      m_cmpiBroker.deleteInstance(aContext,shadowOp);
//      if (backupShadowInstanceP) {
//        m_cmpiBroker.createInstance(aContext,shadowOp,*backupShadowInstanceP);
//      }
      throw rc;
    }
      
//    if (backupShadowInstanceP) {
//      delete backupShadowInstanceP;
//    }
        
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);
    
  }
    
  //----------------------------------------------------------------------------
  CmpiStatus
  CmpiLinux_SambaGlobalOptionsProvider::deleteInstance(
    const CmpiContext& aContext,
    CmpiResult& aResult,
    const CmpiObjectPath& aCop) {
      
    Linux_SambaGlobalOptionsInstanceName instanceName = Linux_SambaGlobalOptionsInstanceName(aCop);
    m_interfaceP->deleteInstance(aContext,m_cmpiBroker,instanceName);

//    instanceName.setNamespace("IBMShadow/cimv2");
//    CmpiObjectPath op = instanceName.getObjectPath();
//      
//    try { // The instance could not have static data
//      m_cmpiBroker.deleteInstance(aContext,op);
//    } catch (CmpiStatus& rc) {}
      
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);
  
  }
    
  //----------------------------------------------------------------------------
  CmpiStatus
  CmpiLinux_SambaGlobalOptionsProvider::invokeMethod(
    const CmpiContext& aContext,
    CmpiResult& aResult,
    const CmpiObjectPath& aCop,
    const char* aMethodNameP,
    const CmpiArgs& in,
    CmpiArgs& out) {
     	
    Linux_SambaGlobalOptionsInstanceName instanceName = Linux_SambaGlobalOptionsInstanceName(aCop);
     
     {

      aResult.returnDone();
      return CmpiErrorFormater::getErrorException(
        CmpiErrorFormater::METHOD_NOT_FOUND,
        aMethodNameP,
        "Linux_SambaGlobalOptions");

    }
      
    aResult.returnDone();
    return CmpiStatus(CMPI_RC_OK);      

  }

 
}	

