// =======================================================================
// Linux_SambaReadListForShareInstance.h
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
#ifndef Linux_SambaReadListForShareInstance_h
#define Linux_SambaReadListForShareInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaReadListForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaReadListForShareInstance {
       
    private:
    void init();
    void init(const Linux_SambaReadListForShareInstance& anInstance);
    void reset();
       
    Linux_SambaReadListForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaReadListForShareInstance();
    Linux_SambaReadListForShareInstance(
      const Linux_SambaReadListForShareInstance& anInstance);
    Linux_SambaReadListForShareInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaReadListForShareInstance();
       
    Linux_SambaReadListForShareInstance& operator=(
      const Linux_SambaReadListForShareInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaReadListForShareInstanceName& anInstanceName);        
    const Linux_SambaReadListForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaReadListForShareInstanceEnumerationElement {

    Linux_SambaReadListForShareInstance* m_elementP;
    Linux_SambaReadListForShareInstanceEnumerationElement* m_nextP;

    Linux_SambaReadListForShareInstanceEnumerationElement();
    ~Linux_SambaReadListForShareInstanceEnumerationElement();  

  };
  

  class Linux_SambaReadListForShareInstanceEnumeration {

    private:
    Linux_SambaReadListForShareInstanceEnumerationElement* m_firstElementP;
    Linux_SambaReadListForShareInstanceEnumerationElement* m_currentElementP;
    Linux_SambaReadListForShareInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaReadListForShareInstanceEnumeration();
    Linux_SambaReadListForShareInstanceEnumeration(
      const Linux_SambaReadListForShareInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaReadListForShareInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaReadListForShareInstance& getNext();
    int getSize() const;
    const Linux_SambaReadListForShareInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaReadListForShareInstance& anInstance);

  };

}

#endif
