// =======================================================================
// Linux_SambaServiceExternal.h
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
#ifndef Linux_SambaServiceExternal_h
#define Linux_SambaServiceExternal_h


#include "Linux_SambaServiceInstance.h"

#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaServiceExternal {
    
    private:
    CmpiBroker m_broker;
    CmpiContext m_context;
  	
    public:
    Linux_SambaServiceExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaServiceExternal();
    
    virtual void enumInstanceNames(
      const char *aNameSpaceP,
      Linux_SambaServiceInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char *anNameSpaceP,
      const char** aPropertiesPP,
      Linux_SambaServiceInstanceEnumeration& anInstanceEnumeration);
     
    virtual Linux_SambaServiceInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaServiceInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaServiceInstance& anInstance);
     
    virtual Linux_SambaServiceInstanceName createInstance(
      const Linux_SambaServiceInstance& anInstance);
     
    virtual void deleteInstance(
      const Linux_SambaServiceInstanceName& anInstanceName);

 
  
  };

}

#endif
