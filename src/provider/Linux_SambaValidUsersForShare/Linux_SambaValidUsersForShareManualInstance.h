// =======================================================================
// Linux_SambaValidUsersForShareManualInstance.h
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
#ifndef Linux_SambaValidUsersForShareManualInstance_h
#define Linux_SambaValidUsersForShareManualInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaValidUsersForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaValidUsersForShareManualInstance {
       
    private:
    void init();
    void init(const Linux_SambaValidUsersForShareManualInstance& anInstance);
    void reset();
       
    Linux_SambaValidUsersForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaValidUsersForShareManualInstance();
    Linux_SambaValidUsersForShareManualInstance(
      const Linux_SambaValidUsersForShareManualInstance& anInstance);
    Linux_SambaValidUsersForShareManualInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaValidUsersForShareManualInstance();
       
    Linux_SambaValidUsersForShareManualInstance& operator=(
      const Linux_SambaValidUsersForShareManualInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaValidUsersForShareInstanceName& anInstanceName);        
    const Linux_SambaValidUsersForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaValidUsersForShareManualInstanceEnumerationElement {

    Linux_SambaValidUsersForShareManualInstance* m_elementP;
    Linux_SambaValidUsersForShareManualInstanceEnumerationElement* m_nextP;

    Linux_SambaValidUsersForShareManualInstanceEnumerationElement();
    ~Linux_SambaValidUsersForShareManualInstanceEnumerationElement();  

  };
  

  class Linux_SambaValidUsersForShareManualInstanceEnumeration {

    private:
    Linux_SambaValidUsersForShareManualInstanceEnumerationElement* m_firstElementP;
    Linux_SambaValidUsersForShareManualInstanceEnumerationElement* m_currentElementP;
    Linux_SambaValidUsersForShareManualInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaValidUsersForShareManualInstanceEnumeration();
    Linux_SambaValidUsersForShareManualInstanceEnumeration(
      const Linux_SambaValidUsersForShareManualInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaValidUsersForShareManualInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaValidUsersForShareManualInstance& getNext();
    int getSize() const;
    const Linux_SambaValidUsersForShareManualInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaValidUsersForShareManualInstance& anInstance);

  };

}

#endif
