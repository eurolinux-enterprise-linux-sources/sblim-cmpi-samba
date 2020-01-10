// =======================================================================
// Linux_SambaForceGroupForPrinterRepositoryInstance.h
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
#ifndef Linux_SambaForceGroupForPrinterRepositoryInstance_h
#define Linux_SambaForceGroupForPrinterRepositoryInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaForceGroupForPrinterInstanceName.h"


namespace genProvider {

  class Linux_SambaForceGroupForPrinterRepositoryInstance {
       
    private:
    void init();
    void init(const Linux_SambaForceGroupForPrinterRepositoryInstance& anInstance);
    void reset();
       
    Linux_SambaForceGroupForPrinterInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaForceGroupForPrinterRepositoryInstance();
    Linux_SambaForceGroupForPrinterRepositoryInstance(
      const Linux_SambaForceGroupForPrinterRepositoryInstance& anInstance);
    Linux_SambaForceGroupForPrinterRepositoryInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaForceGroupForPrinterRepositoryInstance();
       
    Linux_SambaForceGroupForPrinterRepositoryInstance& operator=(
      const Linux_SambaForceGroupForPrinterRepositoryInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaForceGroupForPrinterInstanceName& anInstanceName);        
    const Linux_SambaForceGroupForPrinterInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement {

    Linux_SambaForceGroupForPrinterRepositoryInstance* m_elementP;
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement* m_nextP;

    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement();
    ~Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement();  

  };
  

  class Linux_SambaForceGroupForPrinterRepositoryInstanceEnumeration {

    private:
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement* m_firstElementP;
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement* m_currentElementP;
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumeration();
    Linux_SambaForceGroupForPrinterRepositoryInstanceEnumeration(
      const Linux_SambaForceGroupForPrinterRepositoryInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaForceGroupForPrinterRepositoryInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaForceGroupForPrinterRepositoryInstance& getNext();
    int getSize() const;
    const Linux_SambaForceGroupForPrinterRepositoryInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaForceGroupForPrinterRepositoryInstance& anInstance);

  };

}

#endif
