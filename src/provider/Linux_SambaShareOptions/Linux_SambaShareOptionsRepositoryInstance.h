// =======================================================================
// Linux_SambaShareOptionsRepositoryInstance.h
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
#ifndef Linux_SambaShareOptionsRepositoryInstance_h
#define Linux_SambaShareOptionsRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaShareOptionsInstanceName.h"


namespace genProvider {

  class Linux_SambaShareOptionsRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaShareOptionsRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaShareOptionsInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaShareOptionsRepositoryInstance();
    Linux_SambaShareOptionsRepositoryInstance(
      const Linux_SambaShareOptionsRepositoryInstance& anInstance);
    Linux_SambaShareOptionsRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaShareOptionsRepositoryInstance();
       
    Linux_SambaShareOptionsRepositoryInstance& operator=(
      const Linux_SambaShareOptionsRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaShareOptionsInstanceName& anInstanceName);        
    const Linux_SambaShareOptionsInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaShareOptionsRepositoryInstanceEnumerationElement {

    Linux_SambaShareOptionsRepositoryInstance* m_elementP;
    Linux_SambaShareOptionsRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaShareOptionsRepositoryInstanceEnumerationElement();
    ~Linux_SambaShareOptionsRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaShareOptionsRepositoryInstanceEnumeration {

    private:
    Linux_SambaShareOptionsRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaShareOptionsRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaShareOptionsRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaShareOptionsRepositoryInstanceEnumeration();
    Linux_SambaShareOptionsRepositoryInstanceEnumeration(
      const Linux_SambaShareOptionsRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaShareOptionsRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaShareOptionsRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaShareOptionsRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaShareOptionsRepositoryInstance& anInstance);

  };

}

#endif
