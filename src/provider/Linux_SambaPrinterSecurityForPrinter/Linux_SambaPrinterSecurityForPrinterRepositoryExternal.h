// =======================================================================
// Linux_SambaPrinterSecurityForPrinterRepositoryExternal.h
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
#ifndef Linux_SambaPrinterSecurityForPrinterRepositoryExternal_h
#define Linux_SambaPrinterSecurityForPrinterRepositoryExternal_h

#include "Linux_SambaPrinterSecurityForPrinterInstanceName.h"
#include "Linux_SambaPrinterSecurityForPrinterRepositoryInstance.h"
#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaPrinterSecurityForPrinterRepositoryExternal {
     
    private:
    CmpiBroker  m_broker;
    CmpiContext m_context;
    const static char *s_shadowNameSpaceP;
  	
    public:
    Linux_SambaPrinterSecurityForPrinterRepositoryExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaPrinterSecurityForPrinterRepositoryExternal();
    
    virtual void enumInstanceNames(
      Linux_SambaPrinterSecurityForPrinterInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char** aPropertiesPP,
      Linux_SambaPrinterSecurityForPrinterRepositoryInstanceEnumeration& aRepositoryInstanceEnumeration);
     
    virtual Linux_SambaPrinterSecurityForPrinterRepositoryInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaPrinterSecurityForPrinterInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaPrinterSecurityForPrinterRepositoryInstance& aRepositoryInstance);
     
    virtual Linux_SambaPrinterSecurityForPrinterInstanceName createInstance(
      const Linux_SambaPrinterSecurityForPrinterRepositoryInstance& aRepositoryInstance);
     
    virtual void deleteInstance(
      const Linux_SambaPrinterSecurityForPrinterInstanceName& anInstanceName);
  
  };

}
#endif
