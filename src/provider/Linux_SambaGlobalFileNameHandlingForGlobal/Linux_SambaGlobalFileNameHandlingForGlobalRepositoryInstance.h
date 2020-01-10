// =======================================================================
// Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance.h
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
#ifndef Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance_h
#define Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaGlobalFileNameHandlingForGlobalInstanceName.h"


namespace genProvider {

  class Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaGlobalFileNameHandlingForGlobalInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance();
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance(
      const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& anInstance);
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance();
       
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& operator=(
      const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaGlobalFileNameHandlingForGlobalInstanceName& anInstanceName);        
    const Linux_SambaGlobalFileNameHandlingForGlobalInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement {

    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance* m_elementP;
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement();
    ~Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumeration {

    private:
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumeration();
    Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumeration(
      const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaGlobalFileNameHandlingForGlobalRepositoryInstance& anInstance);

  };

}

#endif
