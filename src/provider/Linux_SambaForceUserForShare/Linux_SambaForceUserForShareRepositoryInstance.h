// =======================================================================
// Linux_SambaForceUserForShareRepositoryInstance.h
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
#ifndef Linux_SambaForceUserForShareRepositoryInstance_h
#define Linux_SambaForceUserForShareRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaForceUserForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaForceUserForShareRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaForceUserForShareRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaForceUserForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaForceUserForShareRepositoryInstance();
    Linux_SambaForceUserForShareRepositoryInstance(
      const Linux_SambaForceUserForShareRepositoryInstance& anInstance);
    Linux_SambaForceUserForShareRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaForceUserForShareRepositoryInstance();
       
    Linux_SambaForceUserForShareRepositoryInstance& operator=(
      const Linux_SambaForceUserForShareRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaForceUserForShareInstanceName& anInstanceName);        
    const Linux_SambaForceUserForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement {

    Linux_SambaForceUserForShareRepositoryInstance* m_elementP;
    Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement();
    ~Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaForceUserForShareRepositoryInstanceEnumeration {

    private:
    Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaForceUserForShareRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaForceUserForShareRepositoryInstanceEnumeration();
    Linux_SambaForceUserForShareRepositoryInstanceEnumeration(
      const Linux_SambaForceUserForShareRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaForceUserForShareRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaForceUserForShareRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaForceUserForShareRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaForceUserForShareRepositoryInstance& anInstance);

  };

}

#endif
