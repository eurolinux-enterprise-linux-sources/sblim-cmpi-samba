// =======================================================================
// Linux_SambaShareProtocolForShareRepositoryExternal.h
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
#ifndef Linux_SambaShareProtocolForShareRepositoryExternal_h
#define Linux_SambaShareProtocolForShareRepositoryExternal_h

#include "Linux_SambaShareProtocolForShareInstanceName.h"
#include "Linux_SambaShareProtocolForShareRepositoryInstance.h"
#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaShareProtocolForShareRepositoryExternal {
     
    private:
    CmpiBroker  m_broker;
    CmpiContext m_context;
    const static char *s_shadowNameSpaceP;
  	
    public:
    Linux_SambaShareProtocolForShareRepositoryExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaShareProtocolForShareRepositoryExternal();
    
    virtual void enumInstanceNames(
      Linux_SambaShareProtocolForShareInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char** aPropertiesPP,
      Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration& aRepositoryInstanceEnumeration);
     
    virtual Linux_SambaShareProtocolForShareRepositoryInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaShareProtocolForShareInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaShareProtocolForShareRepositoryInstance& aRepositoryInstance);
     
    virtual Linux_SambaShareProtocolForShareInstanceName createInstance(
      const Linux_SambaShareProtocolForShareRepositoryInstance& aRepositoryInstance);
     
    virtual void deleteInstance(
      const Linux_SambaShareProtocolForShareInstanceName& anInstanceName);
  
  };

}
#endif
