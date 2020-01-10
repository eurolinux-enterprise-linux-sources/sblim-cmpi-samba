// =======================================================================
// Linux_SambaForceGroupForGlobalInstance.h
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
#ifndef Linux_SambaForceGroupForGlobalInstance_h
#define Linux_SambaForceGroupForGlobalInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaForceGroupForGlobalInstanceName.h"


namespace genProvider {

  class Linux_SambaForceGroupForGlobalInstance {
       
    private:
    void init();
    void init(const Linux_SambaForceGroupForGlobalInstance& anInstance);
    void reset();
       
    Linux_SambaForceGroupForGlobalInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaForceGroupForGlobalInstance();
    Linux_SambaForceGroupForGlobalInstance(
      const Linux_SambaForceGroupForGlobalInstance& anInstance);
    Linux_SambaForceGroupForGlobalInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaForceGroupForGlobalInstance();
       
    Linux_SambaForceGroupForGlobalInstance& operator=(
      const Linux_SambaForceGroupForGlobalInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaForceGroupForGlobalInstanceName& anInstanceName);        
    const Linux_SambaForceGroupForGlobalInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaForceGroupForGlobalInstanceEnumerationElement {

    Linux_SambaForceGroupForGlobalInstance* m_elementP;
    Linux_SambaForceGroupForGlobalInstanceEnumerationElement* m_nextP;

    Linux_SambaForceGroupForGlobalInstanceEnumerationElement();
    ~Linux_SambaForceGroupForGlobalInstanceEnumerationElement();  

  };
  

  class Linux_SambaForceGroupForGlobalInstanceEnumeration {

    private:
    Linux_SambaForceGroupForGlobalInstanceEnumerationElement* m_firstElementP;
    Linux_SambaForceGroupForGlobalInstanceEnumerationElement* m_currentElementP;
    Linux_SambaForceGroupForGlobalInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaForceGroupForGlobalInstanceEnumeration();
    Linux_SambaForceGroupForGlobalInstanceEnumeration(
      const Linux_SambaForceGroupForGlobalInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaForceGroupForGlobalInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaForceGroupForGlobalInstance& getNext();
    int getSize() const;
    const Linux_SambaForceGroupForGlobalInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaForceGroupForGlobalInstance& anInstance);

  };

}

#endif
