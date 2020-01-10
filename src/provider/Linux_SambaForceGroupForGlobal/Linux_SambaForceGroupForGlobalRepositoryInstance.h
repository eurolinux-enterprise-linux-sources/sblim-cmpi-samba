// =======================================================================
// Linux_SambaForceGroupForGlobalRepositoryInstance.h
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
#ifndef Linux_SambaForceGroupForGlobalRepositoryInstance_h
#define Linux_SambaForceGroupForGlobalRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaForceGroupForGlobalInstanceName.h"


namespace genProvider {

  class Linux_SambaForceGroupForGlobalRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaForceGroupForGlobalRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaForceGroupForGlobalInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaForceGroupForGlobalRepositoryInstance();
    Linux_SambaForceGroupForGlobalRepositoryInstance(
      const Linux_SambaForceGroupForGlobalRepositoryInstance& anInstance);
    Linux_SambaForceGroupForGlobalRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaForceGroupForGlobalRepositoryInstance();
       
    Linux_SambaForceGroupForGlobalRepositoryInstance& operator=(
      const Linux_SambaForceGroupForGlobalRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaForceGroupForGlobalInstanceName& anInstanceName);        
    const Linux_SambaForceGroupForGlobalInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement {

    Linux_SambaForceGroupForGlobalRepositoryInstance* m_elementP;
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement();
    ~Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaForceGroupForGlobalRepositoryInstanceEnumeration {

    private:
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumeration();
    Linux_SambaForceGroupForGlobalRepositoryInstanceEnumeration(
      const Linux_SambaForceGroupForGlobalRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaForceGroupForGlobalRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaForceGroupForGlobalRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaForceGroupForGlobalRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaForceGroupForGlobalRepositoryInstance& anInstance);

  };

}

#endif
