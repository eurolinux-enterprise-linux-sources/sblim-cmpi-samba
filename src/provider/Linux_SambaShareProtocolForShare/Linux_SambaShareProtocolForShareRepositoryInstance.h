// =======================================================================
// Linux_SambaShareProtocolForShareRepositoryInstance.h
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
#ifndef Linux_SambaShareProtocolForShareRepositoryInstance_h
#define Linux_SambaShareProtocolForShareRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaShareProtocolForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaShareProtocolForShareRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaShareProtocolForShareRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaShareProtocolForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaShareProtocolForShareRepositoryInstance();
    Linux_SambaShareProtocolForShareRepositoryInstance(
      const Linux_SambaShareProtocolForShareRepositoryInstance& anInstance);
    Linux_SambaShareProtocolForShareRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaShareProtocolForShareRepositoryInstance();
       
    Linux_SambaShareProtocolForShareRepositoryInstance& operator=(
      const Linux_SambaShareProtocolForShareRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaShareProtocolForShareInstanceName& anInstanceName);        
    const Linux_SambaShareProtocolForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement {

    Linux_SambaShareProtocolForShareRepositoryInstance* m_elementP;
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement();
    ~Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration {

    private:
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration();
    Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration(
      const Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaShareProtocolForShareRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaShareProtocolForShareRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaShareProtocolForShareRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaShareProtocolForShareRepositoryInstance& anInstance);

  };

}

#endif
