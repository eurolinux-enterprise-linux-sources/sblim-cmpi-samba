// =======================================================================
// Linux_SambaServiceConfigurationManualInstance.h
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
#ifndef Linux_SambaServiceConfigurationManualInstance_h
#define Linux_SambaServiceConfigurationManualInstance_h


#include "cmpidt.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiBooleanData.h"
#include "CmpiCharData.h"
#include "CmpiDateTime.h"

#include "Linux_SambaServiceConfigurationInstanceName.h"


namespace genProvider {

  class Linux_SambaServiceConfigurationManualInstance {
       
    private:
    void init();
    void init(const Linux_SambaServiceConfigurationManualInstance& anInstance);
    void reset();
       
    Linux_SambaServiceConfigurationInstanceName m_instanceName;
    const char* m_ConfigurationFile;
       
    struct isSetType{
      unsigned int instanceName:1;
      unsigned int ConfigurationFile:1;

    } isSet;
    
    public:
    Linux_SambaServiceConfigurationManualInstance();
    Linux_SambaServiceConfigurationManualInstance(
      const Linux_SambaServiceConfigurationManualInstance& anInstance);
    Linux_SambaServiceConfigurationManualInstance(
      const CmpiInstance& aCmpiInstance, 
      const char* anInstanceNamespaceP);
    ~Linux_SambaServiceConfigurationManualInstance();
       
    Linux_SambaServiceConfigurationManualInstance& operator=(
      const Linux_SambaServiceConfigurationManualInstance& anInstance);
       
    CmpiInstance getCmpiInstance(const char** aPropertiesPP = 0) const;
    unsigned int isInstanceNameSet() const;
    void setInstanceName(const Linux_SambaServiceConfigurationInstanceName& anInstanceName);        
    const Linux_SambaServiceConfigurationInstanceName& getInstanceName() const;

    unsigned int isConfigurationFileSet() const;
    void setConfigurationFile(const char* aValue, int aCopyFlag = 1);
    const char* getConfigurationFile() const;


  };
  
  struct Linux_SambaServiceConfigurationManualInstanceEnumerationElement {

    Linux_SambaServiceConfigurationManualInstance* m_elementP;
    Linux_SambaServiceConfigurationManualInstanceEnumerationElement* m_nextP;

    Linux_SambaServiceConfigurationManualInstanceEnumerationElement();
    ~Linux_SambaServiceConfigurationManualInstanceEnumerationElement();  

  };
  

  class Linux_SambaServiceConfigurationManualInstanceEnumeration {

    private:
    Linux_SambaServiceConfigurationManualInstanceEnumerationElement* m_firstElementP;
    Linux_SambaServiceConfigurationManualInstanceEnumerationElement* m_currentElementP;
    Linux_SambaServiceConfigurationManualInstanceEnumerationElement* m_endElementP;

    public:
    Linux_SambaServiceConfigurationManualInstanceEnumeration();
    Linux_SambaServiceConfigurationManualInstanceEnumeration(
      const Linux_SambaServiceConfigurationManualInstanceEnumeration& anInstanceEnumeration);
    ~Linux_SambaServiceConfigurationManualInstanceEnumeration();

    void reset();
    bool hasNext() const;
    const Linux_SambaServiceConfigurationManualInstance& getNext();
    int getSize() const;
    const Linux_SambaServiceConfigurationManualInstance& getElement(int anIndex) const;  	  
    void addElement(const Linux_SambaServiceConfigurationManualInstance& anInstance);

  };

}

#endif
