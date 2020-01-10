// =======================================================================
// Linux_SambaUsersForServiceInstance.h
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
#ifndef Linux_SambaUsersForServiceInstance_h
#define Linux_SambaUsersForServiceInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaUsersForServiceInstanceName.h"


namespace genProvider {

  class Linux_SambaUsersForServiceInstance {
       
    private:
    void init();
    void init(const Linux_SambaUsersForServiceInstance& anInstance);
    void reset();
       
    Linux_SambaUsersForServiceInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaUsersForServiceInstance();
    Linux_SambaUsersForServiceInstance(
      const Linux_SambaUsersForServiceInstance& anInstance);
    Linux_SambaUsersForServiceInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaUsersForServiceInstance();
       
    Linux_SambaUsersForServiceInstance& operator=(
      const Linux_SambaUsersForServiceInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaUsersForServiceInstanceName& anInstanceName);        
    const Linux_SambaUsersForServiceInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaUsersForServiceInstanceEnumerationElement {

    Linux_SambaUsersForServiceInstance* m_elementP;
    Linux_SambaUsersForServiceInstanceEnumerationElement* m_nextP;

    Linux_SambaUsersForServiceInstanceEnumerationElement();
    ~Linux_SambaUsersForServiceInstanceEnumerationElement();  

  };
  

  class Linux_SambaUsersForServiceInstanceEnumeration {

    private:
    Linux_SambaUsersForServiceInstanceEnumerationElement* m_firstElementP;
    Linux_SambaUsersForServiceInstanceEnumerationElement* m_currentElementP;
    Linux_SambaUsersForServiceInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaUsersForServiceInstanceEnumeration();
    Linux_SambaUsersForServiceInstanceEnumeration(
      const Linux_SambaUsersForServiceInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaUsersForServiceInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaUsersForServiceInstance& getNext();
    int getSize() const;
    const Linux_SambaUsersForServiceInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaUsersForServiceInstance& anInstance);

  };

}

#endif
