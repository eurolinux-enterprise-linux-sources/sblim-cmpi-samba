// =======================================================================
// Linux_SambaCommonSecurityForShareExternal.h
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
#ifndef Linux_SambaCommonSecurityForShareExternal_h
#define Linux_SambaCommonSecurityForShareExternal_h


#include "Linux_SambaCommonSecurityForShareInstance.h"
#include "Linux_SambaCommonSecurityOptionsInstance.h"
#include "Linux_SambaShareOptionsInstance.h"

#include "CmpiBroker.h"

namespace genProvider {

  class Linux_SambaCommonSecurityForShareExternal {
    
    private:
    CmpiBroker m_broker;
    CmpiContext m_context;
  	
    public:
    Linux_SambaCommonSecurityForShareExternal(
      const CmpiBroker& aBroker,
      const CmpiContext& aContext);
    virtual ~Linux_SambaCommonSecurityForShareExternal();
    
    virtual void enumInstanceNames(
      const char *aNameSpaceP,
      Linux_SambaCommonSecurityForShareInstanceNameEnumeration& anInstanceNameEnumeration);
     
    virtual void enumInstances(
      const char *anNameSpaceP,
      const char** aPropertiesPP,
      Linux_SambaCommonSecurityForShareInstanceEnumeration& anInstanceEnumeration);
     
    virtual Linux_SambaCommonSecurityForShareInstance getInstance(
      const char** aPropertiesPP,
      const Linux_SambaCommonSecurityForShareInstanceName& anInstanceName);
     
    virtual void setInstance(
      const char** aPropertiesPP,
      const Linux_SambaCommonSecurityForShareInstance& anInstance);
     
    virtual Linux_SambaCommonSecurityForShareInstanceName createInstance(
      const Linux_SambaCommonSecurityForShareInstance& anInstance);
     
    virtual void deleteInstance(
      const Linux_SambaCommonSecurityForShareInstanceName& anInstanceName);


    //association calls

    void referencesSettingData( 
      const char *aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityForShareInstanceEnumeration& anInstanceEnumeration);

    void referenceNamesSettingData( 
      const char *aNameSpaceP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityForShareInstanceNameEnumeration& anInstanceNameEnumeration);

    void referencesManagedElement( 
      const char *aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaCommonSecurityOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityForShareInstanceEnumeration& anInstanceEnumeration);

    void referenceNamesManagedElement( 
      const char *aNameSpaceP,
      const Linux_SambaCommonSecurityOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityForShareInstanceNameEnumeration& anInstanceNameEnumeration);

    void associatorsSettingData( 
      const char *aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityOptionsInstanceEnumeration& anInstanceEnumeration);

    void associatorNamesSettingData( 
      const char *aNameSpaceP,
      const Linux_SambaShareOptionsInstanceName& aSourceInstanceName,
      Linux_SambaCommonSecurityOptionsInstanceNameEnumeration& anInstanceNameEnumeration);

    void associatorsManagedElement( 
      const char *aNameSpaceP,
      const char** aPropertiesPP,
      const Linux_SambaCommonSecurityOptionsInstanceName& aSourceInstanceName,
      Linux_SambaShareOptionsInstanceEnumeration& anInstanceEnumeration);

    void associatorNamesManagedElement( 
      const char *aNameSpaceP,
      const Linux_SambaCommonSecurityOptionsInstanceName& aSourceInstanceName,
      Linux_SambaShareOptionsInstanceNameEnumeration& anInstanceNameEnumeration); 
  
  };

}

#endif
