// =======================================================================
// Linux_SambaInvalidUsersForShareManualInstance.h
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
#ifndef Linux_SambaInvalidUsersForShareManualInstance_h
#define Linux_SambaInvalidUsersForShareManualInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaInvalidUsersForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaInvalidUsersForShareManualInstance {
       
    private:
    void init();
    void init(const Linux_SambaInvalidUsersForShareManualInstance& anInstance);
    void reset();
       
    Linux_SambaInvalidUsersForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaInvalidUsersForShareManualInstance();
    Linux_SambaInvalidUsersForShareManualInstance(
      const Linux_SambaInvalidUsersForShareManualInstance& anInstance);
    Linux_SambaInvalidUsersForShareManualInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaInvalidUsersForShareManualInstance();
       
    Linux_SambaInvalidUsersForShareManualInstance& operator=(
      const Linux_SambaInvalidUsersForShareManualInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaInvalidUsersForShareInstanceName& anInstanceName);        
    const Linux_SambaInvalidUsersForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement {

    Linux_SambaInvalidUsersForShareManualInstance* m_elementP;
    Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement* m_nextP;

    Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement();
    ~Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement();  

  };
  

  class Linux_SambaInvalidUsersForShareManualInstanceEnumeration {

    private:
    Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement* m_firstElementP;
    Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement* m_currentElementP;
    Linux_SambaInvalidUsersForShareManualInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaInvalidUsersForShareManualInstanceEnumeration();
    Linux_SambaInvalidUsersForShareManualInstanceEnumeration(
      const Linux_SambaInvalidUsersForShareManualInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaInvalidUsersForShareManualInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaInvalidUsersForShareManualInstance& getNext();
    int getSize() const;
    const Linux_SambaInvalidUsersForShareManualInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaInvalidUsersForShareManualInstance& anInstance);

  };

}

#endif
