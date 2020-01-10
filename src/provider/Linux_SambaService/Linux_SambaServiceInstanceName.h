// =======================================================================
// Linux_SambaServiceInstanceName.h
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
#ifndef Linux_SambaServiceInstanceName_h
#define Linux_SambaServiceInstanceName_h

#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"
#include "ArrayConverter.h"
#include "CmpiErrorFormater.h"


namespace genProvider {

  class Linux_SambaServiceInstanceName {
       
    private:
    void init();
    void init(const Linux_SambaServiceInstanceName& anInstanceName);
    void reset();
       
    const char* m_CIMClassNameP;
    const char* m_nameSpaceP;
    
    const char* m_CreationClassName;
    const char* m_Name;
    const char* m_SystemCreationClassName;
    const char* m_SystemName;
       
    struct isSetType{
      unsigned int m_nameSpaceP:1;
      unsigned int CreationClassName:1;
      unsigned int Name:1;
      unsigned int SystemCreationClassName:1;
      unsigned int SystemName:1;

    } isSet;
  
    public:
    Linux_SambaServiceInstanceName();
  	
    Linux_SambaServiceInstanceName(const Linux_SambaServiceInstanceName& anInstanceName);
  	   
    Linux_SambaServiceInstanceName(const CmpiObjectPath& path);
  	 
    ~Linux_SambaServiceInstanceName();
       
    Linux_SambaServiceInstanceName& operator=(const Linux_SambaServiceInstanceName& anInstanceName);
       
    CmpiObjectPath getObjectPath() const;
       
    void fillKeys(CmpiInstance& cmpiInstance) const;
       
    unsigned int isNameSpaceSet() const;
    void setNamespace(const char* aNameSpaceP, int aCopyFlag = 1);
    const char* getNamespace() const;
    
    unsigned int isCreationClassNameSet() const;
    void setCreationClassName(const char* aValue, int aCopyFlag = 1);
    const char* getCreationClassName() const;

    unsigned int isNameSet() const;
    void setName(const char* aValue, int aCopyFlag = 1);
    const char* getName() const;

    unsigned int isSystemCreationClassNameSet() const;
    void setSystemCreationClassName(const char* aValue, int aCopyFlag = 1);
    const char* getSystemCreationClassName() const;

    unsigned int isSystemNameSet() const;
    void setSystemName(const char* aValue, int aCopyFlag = 1);
    const char* getSystemName() const;


  };
  
  //****************************************************************************
  struct Linux_SambaServiceInstanceNameEnumerationElement {
  	Linux_SambaServiceInstanceName* m_elementP;
  	Linux_SambaServiceInstanceNameEnumerationElement* m_nextP;
  	
  	Linux_SambaServiceInstanceNameEnumerationElement();
  	~Linux_SambaServiceInstanceNameEnumerationElement();  	
  };
  
  //****************************************************************************
  class Linux_SambaServiceInstanceNameEnumeration {
  
  	private:
    Linux_SambaServiceInstanceNameEnumerationElement* m_firstElementP;
  	Linux_SambaServiceInstanceNameEnumerationElement* m_currentElementP;
  	Linux_SambaServiceInstanceNameEnumerationElement* m_endElementP;
  	
  	public:
    Linux_SambaServiceInstanceNameEnumeration();
  	  
    Linux_SambaServiceInstanceNameEnumeration(const CmpiArray& arr);
  	  
    Linux_SambaServiceInstanceNameEnumeration(const Linux_SambaServiceInstanceNameEnumeration& anInstanceNameEnumeration);
  	   
    ~Linux_SambaServiceInstanceNameEnumeration();
  	  
    void reset();
  	  
    bool hasNext() const;
  	  
    const Linux_SambaServiceInstanceName& getNext();
  	  
    int getSize() const;
  	  
    const Linux_SambaServiceInstanceName& getElement(int anIndex) const;  	  
  	  
    //no copy of the element is done
    void addElement(const Linux_SambaServiceInstanceName& anInstanceName);
  	  
    operator CmpiArray() const;

  };

}
#endif

