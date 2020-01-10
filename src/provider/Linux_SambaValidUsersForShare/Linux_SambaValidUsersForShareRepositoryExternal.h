// =======================================================================
// Linux_SambaValidUsersForShareRepositoryExternal.h
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
#ifndef Linux_SambaValidUsersForShareRepositoryExternal_h
#define Linux_SambaValidUsersForShareRepositoryExternal_h

#include "Linux_SambaValidUsersForShareInstanceName.h"
#include "Linux_SambaValidUsersForShareRepositoryInstance.h"
#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaValidUsersForShareRepositoryExternal {
     
    private:
    CmpiBroker  m_broker;
    CmpiContext m_context;
    const static char *s_shadowNameSpaceP;
  	
    public:
    Linux_SambaValidUsersForShareRepositoryExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaValidUsersForShareRepositoryExternal();
    
    virtual void enumInstanceNames(
      Linux_SambaValidUsersForShareInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char** aPropertiesPP,
      Linux_SambaValidUsersForShareRepositoryInstanceEnumeration& aRepositoryInstanceEnumeration);
     
    virtual Linux_SambaValidUsersForShareRepositoryInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForShareInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaValidUsersForShareRepositoryInstance& aRepositoryInstance);
     
    virtual Linux_SambaValidUsersForShareInstanceName createInstance(
      const Linux_SambaValidUsersForShareRepositoryInstance& aRepositoryInstance);
     
    virtual void deleteInstance(
      const Linux_SambaValidUsersForShareInstanceName& anInstanceName);
  
  };

}
#endif
