// =======================================================================
// Linux_SambaGlobalForServiceManualInstance.h
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
#ifndef Linux_SambaGlobalForServiceManualInstance_h
#define Linux_SambaGlobalForServiceManualInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaGlobalForServiceInstanceName.h"


namespace genProvider {

  class Linux_SambaGlobalForServiceManualInstance {
       
    private:
    void init();
    void init(const Linux_SambaGlobalForServiceManualInstance& anInstance);
    void reset();
       
    Linux_SambaGlobalForServiceInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaGlobalForServiceManualInstance();
    Linux_SambaGlobalForServiceManualInstance(
      const Linux_SambaGlobalForServiceManualInstance& anInstance);
    Linux_SambaGlobalForServiceManualInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaGlobalForServiceManualInstance();
       
    Linux_SambaGlobalForServiceManualInstance& operator=(
      const Linux_SambaGlobalForServiceManualInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaGlobalForServiceInstanceName& anInstanceName);        
    const Linux_SambaGlobalForServiceInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaGlobalForServiceManualInstanceEnumerationElement {

    Linux_SambaGlobalForServiceManualInstance* m_elementP;
    Linux_SambaGlobalForServiceManualInstanceEnumerationElement* m_nextP;

    Linux_SambaGlobalForServiceManualInstanceEnumerationElement();
    ~Linux_SambaGlobalForServiceManualInstanceEnumerationElement();  

  };
  

  class Linux_SambaGlobalForServiceManualInstanceEnumeration {

    private:
    Linux_SambaGlobalForServiceManualInstanceEnumerationElement* m_firstElementP;
    Linux_SambaGlobalForServiceManualInstanceEnumerationElement* m_currentElementP;
    Linux_SambaGlobalForServiceManualInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaGlobalForServiceManualInstanceEnumeration();
    Linux_SambaGlobalForServiceManualInstanceEnumeration(
      const Linux_SambaGlobalForServiceManualInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaGlobalForServiceManualInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaGlobalForServiceManualInstance& getNext();
    int getSize() const;
    const Linux_SambaGlobalForServiceManualInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaGlobalForServiceManualInstance& anInstance);

  };

}

#endif
