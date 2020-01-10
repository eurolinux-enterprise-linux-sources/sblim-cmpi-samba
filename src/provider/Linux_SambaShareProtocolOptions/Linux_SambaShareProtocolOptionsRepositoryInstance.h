// =======================================================================
// Linux_SambaShareProtocolOptionsRepositoryInstance.h
//     created on Mon, 26 Jun 2006 using ECUTE 2.2.1
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
#ifndef Linux_SambaShareProtocolOptionsRepositoryInstance_h
#define Linux_SambaShareProtocolOptionsRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaShareProtocolOptionsInstanceName.h"


namespace genProvider {

  class Linux_SambaShareProtocolOptionsRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaShareProtocolOptionsRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaShareProtocolOptionsInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaShareProtocolOptionsRepositoryInstance();
    Linux_SambaShareProtocolOptionsRepositoryInstance(
      const Linux_SambaShareProtocolOptionsRepositoryInstance& anInstance);
    Linux_SambaShareProtocolOptionsRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaShareProtocolOptionsRepositoryInstance();
       
    Linux_SambaShareProtocolOptionsRepositoryInstance& operator=(
      const Linux_SambaShareProtocolOptionsRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaShareProtocolOptionsInstanceName& anInstanceName);        
    const Linux_SambaShareProtocolOptionsInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement {

    Linux_SambaShareProtocolOptionsRepositoryInstance* m_elementP;
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement();
    ~Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaShareProtocolOptionsRepositoryInstanceEnumeration {

    private:
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumeration();
    Linux_SambaShareProtocolOptionsRepositoryInstanceEnumeration(
      const Linux_SambaShareProtocolOptionsRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaShareProtocolOptionsRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaShareProtocolOptionsRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaShareProtocolOptionsRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaShareProtocolOptionsRepositoryInstance& anInstance);

  };

}

#endif
