// =======================================================================
// Linux_SambaScriptingForGlobalRepositoryInstance.h
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
#ifndef Linux_SambaScriptingForGlobalRepositoryInstance_h
#define Linux_SambaScriptingForGlobalRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaScriptingForGlobalInstanceName.h"


namespace genProvider {

  class Linux_SambaScriptingForGlobalRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaScriptingForGlobalRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaScriptingForGlobalInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaScriptingForGlobalRepositoryInstance();
    Linux_SambaScriptingForGlobalRepositoryInstance(
      const Linux_SambaScriptingForGlobalRepositoryInstance& anInstance);
    Linux_SambaScriptingForGlobalRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaScriptingForGlobalRepositoryInstance();
       
    Linux_SambaScriptingForGlobalRepositoryInstance& operator=(
      const Linux_SambaScriptingForGlobalRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaScriptingForGlobalInstanceName& anInstanceName);        
    const Linux_SambaScriptingForGlobalInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement {

    Linux_SambaScriptingForGlobalRepositoryInstance* m_elementP;
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement();
    ~Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaScriptingForGlobalRepositoryInstanceEnumeration {

    private:
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumeration();
    Linux_SambaScriptingForGlobalRepositoryInstanceEnumeration(
      const Linux_SambaScriptingForGlobalRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaScriptingForGlobalRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaScriptingForGlobalRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaScriptingForGlobalRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaScriptingForGlobalRepositoryInstance& anInstance);

  };

}

#endif
