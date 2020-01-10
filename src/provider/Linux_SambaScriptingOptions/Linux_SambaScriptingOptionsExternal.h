// =======================================================================
// Linux_SambaScriptingOptionsExternal.h
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
#ifndef Linux_SambaScriptingOptionsExternal_h
#define Linux_SambaScriptingOptionsExternal_h


#include "Linux_SambaScriptingOptionsInstance.h"

#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaScriptingOptionsExternal {
    
    private:
    CmpiBroker m_broker;
    CmpiContext m_context;
  	
    public:
    Linux_SambaScriptingOptionsExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaScriptingOptionsExternal();
    
    virtual void enumInstanceNames(
      const char *aNameSpaceP,
      Linux_SambaScriptingOptionsInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char *anNameSpaceP,
      const char** aPropertiesPP,
      Linux_SambaScriptingOptionsInstanceEnumeration& anInstanceEnumeration);
     
    virtual Linux_SambaScriptingOptionsInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaScriptingOptionsInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaScriptingOptionsInstance& anInstance);
     
    virtual Linux_SambaScriptingOptionsInstanceName createInstance(
      const Linux_SambaScriptingOptionsInstance& anInstance);
     
    virtual void deleteInstance(
      const Linux_SambaScriptingOptionsInstanceName& anInstanceName);

 
  
  };

}

#endif
