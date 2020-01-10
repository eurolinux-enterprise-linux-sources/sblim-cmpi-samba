// =======================================================================
// Linux_SambaUserInstanceName.h
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
#ifndef Linux_SambaUserInstanceName_h
#define Linux_SambaUserInstanceName_h

#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"
#include "ArrayConverter.h"
#include "CmpiErrorFormater.h"


namespace genProvider {

  class Linux_SambaUserInstanceName {
       
    private:
    void init();
    void init(const Linux_SambaUserInstanceName& anInstanceName);
    void reset();
       
    const char* m_CIMClassNameP;
    const char* m_nameSpaceP;
    
    const char* m_SambaUserName;
       
    struct isSetType{
      unsigned int m_nameSpaceP:1;
      unsigned int SambaUserName:1;

    } isSet;
  
    public:
    Linux_SambaUserInstanceName();
  	
    Linux_SambaUserInstanceName(const Linux_SambaUserInstanceName& anInstanceName);
  	   
    Linux_SambaUserInstanceName(const CmpiObjectPath& path);
  	 
    ~Linux_SambaUserInstanceName();
       
    Linux_SambaUserInstanceName& operator=(const Linux_SambaUserInstanceName& anInstanceName);
       
    CmpiObjectPath getObjectPath() const;
       
    void fillKeys(CmpiInstance& cmpiInstance) const;
       
    unsigned int isNameSpaceSet() const;
    void setNamespace(const char* aNameSpaceP, int aCopyFlag = 1);
    const char* getNamespace() const;
    
    unsigned int isSambaUserNameSet() const;
    void setSambaUserName(const char* aValue, int aCopyFlag = 1);
    const char* getSambaUserName() const;


  };
  
  //****************************************************************************
  struct Linux_SambaUserInstanceNameEnumerationElement {
  	Linux_SambaUserInstanceName* m_elementP;
  	Linux_SambaUserInstanceNameEnumerationElement* m_nextP;
  	
  	Linux_SambaUserInstanceNameEnumerationElement();
  	~Linux_SambaUserInstanceNameEnumerationElement();  	
  };
  
  //****************************************************************************
  class Linux_SambaUserInstanceNameEnumeration {
  
  	private:
    Linux_SambaUserInstanceNameEnumerationElement* m_firstElementP;
  	Linux_SambaUserInstanceNameEnumerationElement* m_currentElementP;
  	Linux_SambaUserInstanceNameEnumerationElement* m_endElementP;
  	
  	public:
    Linux_SambaUserInstanceNameEnumeration();
  	  
    Linux_SambaUserInstanceNameEnumeration(const CmpiArray& arr);
  	  
    Linux_SambaUserInstanceNameEnumeration(const Linux_SambaUserInstanceNameEnumeration& anInstanceNameEnumeration);
  	   
    ~Linux_SambaUserInstanceNameEnumeration();
  	  
    void reset();
  	  
    bool hasNext() const;
  	  
    const Linux_SambaUserInstanceName& getNext();
  	  
    int getSize() const;
  	  
    const Linux_SambaUserInstanceName& getElement(int anIndex) const;  	  
  	  
    //no copy of the element is done
    void addElement(const Linux_SambaUserInstanceName& anInstanceName);
  	  
    operator CmpiArray() const;

  };

}
#endif

