// =======================================================================
// Linux_SambaShareFileNameHandlingOptionsRepositoryExternal.h
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
#ifndef Linux_SambaShareFileNameHandlingOptionsRepositoryExternal_h
#define Linux_SambaShareFileNameHandlingOptionsRepositoryExternal_h

#include "Linux_SambaShareFileNameHandlingOptionsInstanceName.h"
#include "Linux_SambaShareFileNameHandlingOptionsRepositoryInstance.h"
#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaShareFileNameHandlingOptionsRepositoryExternal {
     
    private:
    CmpiBroker  m_broker;
    CmpiContext m_context;
    const static char *s_shadowNameSpaceP;
  	
    public:
    Linux_SambaShareFileNameHandlingOptionsRepositoryExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaShareFileNameHandlingOptionsRepositoryExternal();
    
    virtual void enumInstanceNames(
      Linux_SambaShareFileNameHandlingOptionsInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char** aPropertiesPP,
      Linux_SambaShareFileNameHandlingOptionsRepositoryInstanceEnumeration& aRepositoryInstanceEnumeration);
     
    virtual Linux_SambaShareFileNameHandlingOptionsRepositoryInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaShareFileNameHandlingOptionsInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaShareFileNameHandlingOptionsRepositoryInstance& aRepositoryInstance);
     
    virtual Linux_SambaShareFileNameHandlingOptionsInstanceName createInstance(
      const Linux_SambaShareFileNameHandlingOptionsRepositoryInstance& aRepositoryInstance);
     
    virtual void deleteInstance(
      const Linux_SambaShareFileNameHandlingOptionsInstanceName& anInstanceName);
  
  };

}
#endif
