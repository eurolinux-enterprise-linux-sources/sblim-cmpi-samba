// =======================================================================
// Linux_SambaValidUsersForShareDefaultImplementation.h
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
#ifndef Linux_SambaValidUsersForShareDefaultImplementation_h
#define Linux_SambaValidUsersForShareDefaultImplementation_h

#include "Linux_SambaValidUsersForShareInstanceName.h"
#include "Linux_SambaValidUsersForShareManualInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiDateTime.h"
#include "CmpiBroker.h"
#include "Linux_SambaUserInstance.h"
#include "Linux_SambaShareOptionsInstance.h"
#include "Linux_SambaUserExternal.h"
#include "Linux_SambaShareOptionsExternal.h"
#include "Linux_SambaValidUsersForShareInterface.h"


namespace genProvider {

  class Linux_SambaValidUsersForShareDefaultImplementation:
   public Linux_SambaValidUsersForShareInterface {
  	
    public:    
    virtual ~Linux_SambaValidUsersForShareDefaultImplementation() { };
    
    /* intrinsic methods */
    
    virtual void enumInstanceNames(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      Linux_SambaValidUsersForShareInstanceNameEnumeration& anInstanceNameEnumeration);
    
  	
    
    virtual void enumInstances(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      const char** aPropertiesPP,
  	  Linux_SambaValidUsersForShareManualInstanceEnumeration& aManualInstanceEnumeration);
  	
  	
    
    virtual Linux_SambaValidUsersForShareManualInstance getInstance(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForShareInstanceName& anInstanceName);
    
  	
    
    virtual void setInstance(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForShareManualInstance& aManualInstance);
    
  	
    
    virtual Linux_SambaValidUsersForShareInstanceName createInstance(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const Linux_SambaValidUsersForShareManualInstance& aManualInstance);
    
  	
    
    virtual void deleteInstance(
      const CmpiContext& aContext,
      const CmpiBroker& aBroker,
      const Linux_SambaValidUsersForShareInstanceName& anInstanceName);
    
	
    
    /* Association Interface */

    
    virtual void referencesPartComponent( 
      const CmpiContext& aContext,  
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaValidUsersForShareManualInstanceEnumeration& aManualInstanceEnumeration);
    

    
    virtual void referencesGroupComponent( 
      const CmpiContext& aContext,  
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaUserInstanceName& aSourceInstanceName,
      Linux_SambaValidUsersForShareManualInstanceEnumeration& aManualInstanceEnumeration);
    

    
    virtual void associatorsPartComponent( 
      const CmpiContext& aContext,  
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaUserInstanceEnumeration& anInstanceEnumeration);
    

    
    virtual void associatorsGroupComponent( 
      const CmpiContext& aContext,  
      const CmpiBroker& aBroker,
      const char* aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaUserInstanceName& aSourceInstanceName,
      Linux_SambaShareOptionsInstanceEnumeration& anInstanceEnumeration);
    

   
    
    /* extrinsic methods */
    
	
  };
  
}
#endif
