// =======================================================================
// Linux_SambaForceGroupForShareRepositoryInstance.h
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
#ifndef Linux_SambaForceGroupForShareRepositoryInstance_h
#define Linux_SambaForceGroupForShareRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaForceGroupForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaForceGroupForShareRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaForceGroupForShareRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaForceGroupForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaForceGroupForShareRepositoryInstance();
    Linux_SambaForceGroupForShareRepositoryInstance(
      const Linux_SambaForceGroupForShareRepositoryInstance& anInstance);
    Linux_SambaForceGroupForShareRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaForceGroupForShareRepositoryInstance();
       
    Linux_SambaForceGroupForShareRepositoryInstance& operator=(
      const Linux_SambaForceGroupForShareRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaForceGroupForShareInstanceName& anInstanceName);        
    const Linux_SambaForceGroupForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement {

    Linux_SambaForceGroupForShareRepositoryInstance* m_elementP;
    Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement();
    ~Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaForceGroupForShareRepositoryInstanceEnumeration {

    private:
    Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaForceGroupForShareRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaForceGroupForShareRepositoryInstanceEnumeration();
    Linux_SambaForceGroupForShareRepositoryInstanceEnumeration(
      const Linux_SambaForceGroupForShareRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaForceGroupForShareRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaForceGroupForShareRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaForceGroupForShareRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaForceGroupForShareRepositoryInstance& anInstance);

  };

}

#endif
