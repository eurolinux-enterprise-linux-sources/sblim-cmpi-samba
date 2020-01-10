// =======================================================================
// Linux_SambaShareProtocolForShareManualInstance.h
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
#ifndef Linux_SambaShareProtocolForShareManualInstance_h
#define Linux_SambaShareProtocolForShareManualInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaShareProtocolForShareInstanceName.h"


namespace genProvider {

  class Linux_SambaShareProtocolForShareManualInstance {
       
    private:
    void init();
    void init(const Linux_SambaShareProtocolForShareManualInstance& anInstance);
    void reset();
       
    Linux_SambaShareProtocolForShareInstanceName m_instanceName;
       
    struct isSetType{
      unsigned int instanceName:1;

    } isSet;
    
    public:
    Linux_SambaShareProtocolForShareManualInstance();
    Linux_SambaShareProtocolForShareManualInstance(
      const Linux_SambaShareProtocolForShareManualInstance& anInstance);
    Linux_SambaShareProtocolForShareManualInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaShareProtocolForShareManualInstance();
       
    Linux_SambaShareProtocolForShareManualInstance& operator=(
      const Linux_SambaShareProtocolForShareManualInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaShareProtocolForShareInstanceName& anInstanceName);        
    const Linux_SambaShareProtocolForShareInstanceName& getInstanceName() const;


  };
  
  struct Linux_SambaShareProtocolForShareManualInstanceEnumerationElement {

    Linux_SambaShareProtocolForShareManualInstance* m_elementP;
    Linux_SambaShareProtocolForShareManualInstanceEnumerationElement* m_nextP;

    Linux_SambaShareProtocolForShareManualInstanceEnumerationElement();
    ~Linux_SambaShareProtocolForShareManualInstanceEnumerationElement();  

  };
  

  class Linux_SambaShareProtocolForShareManualInstanceEnumeration {

    private:
    Linux_SambaShareProtocolForShareManualInstanceEnumerationElement* m_firstElementP;
    Linux_SambaShareProtocolForShareManualInstanceEnumerationElement* m_currentElementP;
    Linux_SambaShareProtocolForShareManualInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaShareProtocolForShareManualInstanceEnumeration();
    Linux_SambaShareProtocolForShareManualInstanceEnumeration(
      const Linux_SambaShareProtocolForShareManualInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaShareProtocolForShareManualInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaShareProtocolForShareManualInstance& getNext();
    int getSize() const;
    const Linux_SambaShareProtocolForShareManualInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaShareProtocolForShareManualInstance& anInstance);

  };

}

#endif
