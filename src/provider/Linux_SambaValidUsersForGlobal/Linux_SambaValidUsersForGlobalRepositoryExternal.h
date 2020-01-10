// =======================================================================
// Linux_SambaValidUsersForGlobalRepositoryExternal.h
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
#ifndef Linux_SambaValidUsersForGlobalRepositoryExternal_h
#define Linux_SambaValidUsersForGlobalRepositoryExternal_h

#include "Linux_SambaValidUsersForGlobalInstanceName.h"
#include "Linux_SambaValidUsersForGlobalRepositoryInstance.h"
#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaValidUsersForGlobalRepositoryExternal {
     
    private:
    CmpiBroker  m_broker;
    CmpiContext m_context;
    const static char *s_shadowNameSpaceP;
  	
    public:
    Linux_SambaValidUsersForGlobalRepositoryExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaValidUsersForGlobalRepositoryExternal();
    
    virtual void enumInstanceNames(
      Linux_SambaValidUsersForGlobalInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char** aPropertiesPP,
      Linux_SambaValidUsersForGlobalRepositoryInstanceEnumeration& aRepositoryInstanceEnumeration);
     
    virtual Linux_SambaValidUsersForGlobalRepositoryInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForGlobalInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForGlobalRepositoryInstance& aRepositoryInstance);
     
    virtual Linux_SambaValidUsersForGlobalInstanceName createInstance(
      const Linux_SambaValidUsersForGlobalRepositoryInstance& aRepositoryInstance);
     
    virtual void deleteInstance(
      const Linux_SambaValidUsersForGlobalInstanceName& anInstanceName);
  
  };

}
#endif
