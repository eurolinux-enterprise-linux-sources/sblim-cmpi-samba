// =======================================================================
// Linux_SambaPrinterPrintingOptionsInstance.cpp
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
#include "Linux_SambaPrinterPrintingOptionsInstance.h"
#include "CmpiData.h"
#include "CmpiString.h"
#include "CmpiArray.h"
#include <string>

namespace genProvider {

  //****************************************************************************
  //Linux_SambaPrinterPrintingOptionsInstance
  //----------------------------------------------------------------------------
  //empty constructor
  Linux_SambaPrinterPrintingOptionsInstance::Linux_SambaPrinterPrintingOptionsInstance() {   	
   	init();  	   	
  }
  
  //----------------------------------------------------------------------------
  //copy constructor	
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstance::Linux_SambaPrinterPrintingOptionsInstance(
    const Linux_SambaPrinterPrintingOptionsInstance& anInstance) {   	
   	init(anInstance);  	   	
  }
  
  //----------------------------------------------------------------------------
  //constructor using CmpiInstance
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstance::Linux_SambaPrinterPrintingOptionsInstance(
    const CmpiInstance& aCmpiInstance,
    const char* anInstanceNamespaceP) {

    CmpiData cmpiData;

    init(); 
    
    CmpiObjectPath cop = aCmpiInstance.getObjectPath();
    cop.setNameSpace(anInstanceNamespaceP);
    setInstanceName(Linux_SambaPrinterPrintingOptionsInstanceName(cop));

    cmpiData = aCmpiInstance.getProperty("Caption");
    if ( ! cmpiData.isNullValue()){
      CmpiString Caption = cmpiData;
      setCaption(Caption.charPtr());
    }

    cmpiData = aCmpiInstance.getProperty("CupsOptions");
    if ( ! cmpiData.isNullValue()){
      CmpiString CupsOptions = cmpiData;
      setCupsOptions(CupsOptions.charPtr());
    }

    cmpiData = aCmpiInstance.getProperty("DefaultDevMode");
    if ( ! cmpiData.isNullValue()){
      CMPIBoolean DefaultDevMode = cmpiData;
      setDefaultDevMode(DefaultDevMode);
    }

    cmpiData = aCmpiInstance.getProperty("Description");
    if ( ! cmpiData.isNullValue()){
      CmpiString Description = cmpiData;
      setDescription(Description.charPtr());
    }

    cmpiData = aCmpiInstance.getProperty("ElementName");
    if ( ! cmpiData.isNullValue()){
      CmpiString ElementName = cmpiData;
      setElementName(ElementName.charPtr());
    }

    cmpiData = aCmpiInstance.getProperty("MaxPrintjobs");
    if ( ! cmpiData.isNullValue()){
      CMPIUint64 MaxPrintjobs = cmpiData;
      setMaxPrintjobs(MaxPrintjobs);
    }

    cmpiData = aCmpiInstance.getProperty("MaxReportedPrintjobs");
    if ( ! cmpiData.isNullValue()){
      CMPIUint64 MaxReportedPrintjobs = cmpiData;
      setMaxReportedPrintjobs(MaxReportedPrintjobs);
    }

    cmpiData = aCmpiInstance.getProperty("PrintCommand");
    if ( ! cmpiData.isNullValue()){
      CmpiString PrintCommand = cmpiData;
      setPrintCommand(PrintCommand.charPtr());
    }

    cmpiData = aCmpiInstance.getProperty("UseClientDriver");
    if ( ! cmpiData.isNullValue()){
      CMPIBoolean UseClientDriver = cmpiData;
      setUseClientDriver(UseClientDriver);
    }

    
  }
  
  //----------------------------------------------------------------------------
  //Destructor
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstance::
   ~Linux_SambaPrinterPrintingOptionsInstance(){
   	reset();  	  
  }
  
  
  //----------------------------------------------------------------------------
  //copy operator
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstance&
  Linux_SambaPrinterPrintingOptionsInstance::operator=(
    const Linux_SambaPrinterPrintingOptionsInstance& anInstance) {   	
   	
   	init(anInstance);
   	return *this;
  
  }
  
  
  //----------------------------------------------------------------------------
  //converts to CmpiInstance
  //----------------------------------------------------------------------------
  CmpiInstance
  Linux_SambaPrinterPrintingOptionsInstance::getCmpiInstance(
    const char** aPropertiesPP) const {
   	
   	CmpiObjectPath objectPath=getInstanceName().getObjectPath();      
    CmpiInstance cmpiInstance(objectPath);    
    getInstanceName().fillKeys(cmpiInstance);
    
    if (aPropertiesPP) {
	    cmpiInstance.setPropertyFilter(aPropertiesPP,0);
    }

  	if (isSet.Caption) {
  	  
  	  cmpiInstance.setProperty(
  	    "Caption",
  	    CmpiData(m_Caption));
  	}

  	if (isSet.CupsOptions) {
  	  
  	  cmpiInstance.setProperty(
  	    "CupsOptions",
  	    CmpiData(m_CupsOptions));
  	}

  	if (isSet.DefaultDevMode) {
  	  
  	  cmpiInstance.setProperty(
  	    "DefaultDevMode",
  	    CmpiBooleanData(m_DefaultDevMode));
  	}

  	if (isSet.Description) {
  	  
  	  cmpiInstance.setProperty(
  	    "Description",
  	    CmpiData(m_Description));
  	}

  	if (isSet.ElementName) {
  	  
  	  cmpiInstance.setProperty(
  	    "ElementName",
  	    CmpiData(m_ElementName));
  	}

  	if (isSet.MaxPrintjobs) {
  	  
  	  cmpiInstance.setProperty(
  	    "MaxPrintjobs",
  	    CmpiData(m_MaxPrintjobs));
  	}

  	if (isSet.MaxReportedPrintjobs) {
  	  
  	  cmpiInstance.setProperty(
  	    "MaxReportedPrintjobs",
  	    CmpiData(m_MaxReportedPrintjobs));
  	}

  	if (isSet.PrintCommand) {
  	  
  	  cmpiInstance.setProperty(
  	    "PrintCommand",
  	    CmpiData(m_PrintCommand));
  	}

  	if (isSet.UseClientDriver) {
  	  
  	  cmpiInstance.setProperty(
  	    "UseClientDriver",
  	    CmpiBooleanData(m_UseClientDriver));
  	}

  	
  	return cmpiInstance;
  	
  }
  
  //----------------------------------------------------------------------------
  // InstanceName related methods
  //----------------------------------------------------------------------------
  unsigned int 
  Linux_SambaPrinterPrintingOptionsInstance::isInstanceNameSet() const {
  	return isSet.instanceName;
  }
  
  //----------------------------------------------------------------------------
  const Linux_SambaPrinterPrintingOptionsInstanceName&
  Linux_SambaPrinterPrintingOptionsInstance::getInstanceName() const {

    if( ! isSet.instanceName) {
   	  throw CmpiErrorFormater::getErrorException(
        CmpiErrorFormater::NOT_SET,
        "InstanceName (CIM Key Attributes)",
        "Linux_SambaPrinterPrintingOptions");
   	}
  		
   	return m_instanceName;
  
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setInstanceName(
    const Linux_SambaPrinterPrintingOptionsInstanceName& val) {

    m_instanceName = val;
    isSet.instanceName = 1;

  }
       
  //----------------------------------------------------------------------------
  // Caption related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isCaptionSet() const {
    return isSet.Caption;
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setCaption(
    const char* aValueP,
    int aCopyFlag) {
    
    if (isSet.Caption) {
      delete [] m_Caption;
    }
    
    if (aCopyFlag && aValueP) {
      char* valueP = new char[strlen(aValueP) + 1];
      strcpy(valueP,aValueP);
      m_Caption = valueP;
    } else {
      m_Caption = aValueP;
    }
    
    isSet.Caption = 1;

  }       

  //----------------------------------------------------------------------------
  const char*
  Linux_SambaPrinterPrintingOptionsInstance::getCaption() const {
    
    if ( ! isSet.Caption) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "Caption",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_Caption;

  }
       
  //----------------------------------------------------------------------------
  // CupsOptions related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isCupsOptionsSet() const {
    return isSet.CupsOptions;
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setCupsOptions(
    const char* aValueP,
    int aCopyFlag) {
    
    if (isSet.CupsOptions) {
      delete [] m_CupsOptions;
    }
    
    if (aCopyFlag && aValueP) {
      char* valueP = new char[strlen(aValueP) + 1];
      strcpy(valueP,aValueP);
      m_CupsOptions = valueP;
    } else {
      m_CupsOptions = aValueP;
    }
    
    isSet.CupsOptions = 1;

  }       

  //----------------------------------------------------------------------------
  const char*
  Linux_SambaPrinterPrintingOptionsInstance::getCupsOptions() const {
    
    if ( ! isSet.CupsOptions) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "CupsOptions",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_CupsOptions;

  }
       
  //----------------------------------------------------------------------------
  // DefaultDevMode related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isDefaultDevModeSet() const {
    return isSet.DefaultDevMode;
  }

  //----------------------------------------------------------------------------
  void Linux_SambaPrinterPrintingOptionsInstance::setDefaultDevMode(
    const CMPIBoolean aValue) {
  
    m_DefaultDevMode = aValue;
    isSet.DefaultDevMode = 1;
  
  }       

  //----------------------------------------------------------------------------
  const CMPIBoolean
  Linux_SambaPrinterPrintingOptionsInstance::getDefaultDevMode() const {
    
    if ( ! isSet.DefaultDevMode) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "DefaultDevMode",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_DefaultDevMode;

  }
       
  //----------------------------------------------------------------------------
  // Description related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isDescriptionSet() const {
    return isSet.Description;
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setDescription(
    const char* aValueP,
    int aCopyFlag) {
    
    if (isSet.Description) {
      delete [] m_Description;
    }
    
    if (aCopyFlag && aValueP) {
      char* valueP = new char[strlen(aValueP) + 1];
      strcpy(valueP,aValueP);
      m_Description = valueP;
    } else {
      m_Description = aValueP;
    }
    
    isSet.Description = 1;

  }       

  //----------------------------------------------------------------------------
  const char*
  Linux_SambaPrinterPrintingOptionsInstance::getDescription() const {
    
    if ( ! isSet.Description) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "Description",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_Description;

  }
       
  //----------------------------------------------------------------------------
  // ElementName related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isElementNameSet() const {
    return isSet.ElementName;
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setElementName(
    const char* aValueP,
    int aCopyFlag) {
    
    if (isSet.ElementName) {
      delete [] m_ElementName;
    }
    
    if (aCopyFlag && aValueP) {
      char* valueP = new char[strlen(aValueP) + 1];
      strcpy(valueP,aValueP);
      m_ElementName = valueP;
    } else {
      m_ElementName = aValueP;
    }
    
    isSet.ElementName = 1;

  }       

  //----------------------------------------------------------------------------
  const char*
  Linux_SambaPrinterPrintingOptionsInstance::getElementName() const {
    
    if ( ! isSet.ElementName) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "ElementName",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_ElementName;

  }
       
  //----------------------------------------------------------------------------
  // MaxPrintjobs related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isMaxPrintjobsSet() const {
    return isSet.MaxPrintjobs;
  }

  //----------------------------------------------------------------------------
  void Linux_SambaPrinterPrintingOptionsInstance::setMaxPrintjobs(
    const CMPIUint64 aValue) {
  
    m_MaxPrintjobs = aValue;
    isSet.MaxPrintjobs = 1;
  
  }       

  //----------------------------------------------------------------------------
  const CMPIUint64
  Linux_SambaPrinterPrintingOptionsInstance::getMaxPrintjobs() const {
    
    if ( ! isSet.MaxPrintjobs) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "MaxPrintjobs",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_MaxPrintjobs;

  }
       
  //----------------------------------------------------------------------------
  // MaxReportedPrintjobs related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isMaxReportedPrintjobsSet() const {
    return isSet.MaxReportedPrintjobs;
  }

  //----------------------------------------------------------------------------
  void Linux_SambaPrinterPrintingOptionsInstance::setMaxReportedPrintjobs(
    const CMPIUint64 aValue) {
  
    m_MaxReportedPrintjobs = aValue;
    isSet.MaxReportedPrintjobs = 1;
  
  }       

  //----------------------------------------------------------------------------
  const CMPIUint64
  Linux_SambaPrinterPrintingOptionsInstance::getMaxReportedPrintjobs() const {
    
    if ( ! isSet.MaxReportedPrintjobs) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "MaxReportedPrintjobs",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_MaxReportedPrintjobs;

  }
       
  //----------------------------------------------------------------------------
  // PrintCommand related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isPrintCommandSet() const {
    return isSet.PrintCommand;
  }

  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::setPrintCommand(
    const char* aValueP,
    int aCopyFlag) {
    
    if (isSet.PrintCommand) {
      delete [] m_PrintCommand;
    }
    
    if (aCopyFlag && aValueP) {
      char* valueP = new char[strlen(aValueP) + 1];
      strcpy(valueP,aValueP);
      m_PrintCommand = valueP;
    } else {
      m_PrintCommand = aValueP;
    }
    
    isSet.PrintCommand = 1;

  }       

  //----------------------------------------------------------------------------
  const char*
  Linux_SambaPrinterPrintingOptionsInstance::getPrintCommand() const {
    
    if ( ! isSet.PrintCommand) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "PrintCommand",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_PrintCommand;

  }
       
  //----------------------------------------------------------------------------
  // UseClientDriver related methods
  //----------------------------------------------------------------------------
  unsigned int
  Linux_SambaPrinterPrintingOptionsInstance::isUseClientDriverSet() const {
    return isSet.UseClientDriver;
  }

  //----------------------------------------------------------------------------
  void Linux_SambaPrinterPrintingOptionsInstance::setUseClientDriver(
    const CMPIBoolean aValue) {
  
    m_UseClientDriver = aValue;
    isSet.UseClientDriver = 1;
  
  }       

  //----------------------------------------------------------------------------
  const CMPIBoolean
  Linux_SambaPrinterPrintingOptionsInstance::getUseClientDriver() const {
    
    if ( ! isSet.UseClientDriver) {
   	  throw CmpiErrorFormater::getErrorException(
   	    CmpiErrorFormater::NOT_SET,
        "UseClientDriver",
        "Linux_SambaPrinterPrintingOptions");
   	}


    return m_UseClientDriver;

  }

  
  //----------------------------------------------------------------------------
  //set isSet attributes to FALSE
  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::init() {
   	isSet.instanceName = 0;
    isSet.Caption = 0;
    isSet.CupsOptions = 0;
    isSet.DefaultDevMode = 0;
    isSet.Description = 0;
    isSet.ElementName = 0;
    isSet.MaxPrintjobs = 0;
    isSet.MaxReportedPrintjobs = 0;
    isSet.PrintCommand = 0;
    isSet.UseClientDriver = 0;
  	
  }
  
  //----------------------------------------------------------------------------
  //copies another instance properties in this
  //----------------------------------------------------------------------------
  void 
  Linux_SambaPrinterPrintingOptionsInstance::init(
    const Linux_SambaPrinterPrintingOptionsInstance& anOriginal) {   	

   	init();
   	   	
    if(anOriginal.isInstanceNameSet()) {
      setInstanceName(anOriginal.getInstanceName());
    }
       	
    if (anOriginal.isCaptionSet()) {
      const char* CaptionOriginal = anOriginal.getCaption();
      setCaption(CaptionOriginal,1);
    }
   	
    if (anOriginal.isCupsOptionsSet()) {
      const char* CupsOptionsOriginal = anOriginal.getCupsOptions();
      setCupsOptions(CupsOptionsOriginal,1);
    }
   	
    if (anOriginal.isDefaultDevModeSet()) {
      const CMPIBoolean DefaultDevModeOriginal = anOriginal.getDefaultDevMode();
      setDefaultDevMode(DefaultDevModeOriginal);
    }
   	
    if (anOriginal.isDescriptionSet()) {
      const char* DescriptionOriginal = anOriginal.getDescription();
      setDescription(DescriptionOriginal,1);
    }
   	
    if (anOriginal.isElementNameSet()) {
      const char* ElementNameOriginal = anOriginal.getElementName();
      setElementName(ElementNameOriginal,1);
    }
   	
    if (anOriginal.isMaxPrintjobsSet()) {
      const CMPIUint64 MaxPrintjobsOriginal = anOriginal.getMaxPrintjobs();
      setMaxPrintjobs(MaxPrintjobsOriginal);
    }
   	
    if (anOriginal.isMaxReportedPrintjobsSet()) {
      const CMPIUint64 MaxReportedPrintjobsOriginal = anOriginal.getMaxReportedPrintjobs();
      setMaxReportedPrintjobs(MaxReportedPrintjobsOriginal);
    }
   	
    if (anOriginal.isPrintCommandSet()) {
      const char* PrintCommandOriginal = anOriginal.getPrintCommand();
      setPrintCommand(PrintCommandOriginal,1);
    }
   	
    if (anOriginal.isUseClientDriverSet()) {
      const CMPIBoolean UseClientDriverOriginal = anOriginal.getUseClientDriver();
      setUseClientDriver(UseClientDriverOriginal);
    }
    
  }
  
  //----------------------------------------------------------------------------
  //reset the instance data
  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstance::reset() {
   	
  	if (isSet.Caption) {
  	  delete(m_Caption);
  	}

  	if (isSet.CupsOptions) {
  	  delete(m_CupsOptions);
  	}

  	if (isSet.Description) {
  	  delete(m_Description);
  	}

  	if (isSet.ElementName) {
  	  delete(m_ElementName);
  	}

  	if (isSet.PrintCommand) {
  	  delete(m_PrintCommand);
  	}

  }
  
  //----------------------------------------------------------------------------
  //Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement	
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement::Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement() {
   	
  	m_elementP = 0;
  	m_nextP = 0;
  	  
  }
  
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement::~Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement() {
   	
  	if (m_elementP) {
  	  delete(m_elementP);
  	}
  	
  	if (m_nextP) {
  	  delete(m_nextP);
  	}
  	  
  }

  //----------------------------------------------------------------------------
  //Linux_SambaPrinterPrintingOptionsInstanceNameEnumeration
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::Linux_SambaPrinterPrintingOptionsInstanceEnumeration() {
   	
    m_firstElementP = 0;
    m_currentElementP = 0;
    m_endElementP = 0;
  
  }
  
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::Linux_SambaPrinterPrintingOptionsInstanceEnumeration(
    const Linux_SambaPrinterPrintingOptionsInstanceEnumeration& anInstanceEnumeration) {
   	
    m_firstElementP = 0;
    m_currentElementP = 0;
    m_endElementP = 0;
  	 
    int size = anInstanceEnumeration.getSize();
    for (int x=0; x < size;++x) {
      addElement(anInstanceEnumeration.getElement(x));
    }           

  }
  
  //----------------------------------------------------------------------------
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::~Linux_SambaPrinterPrintingOptionsInstanceEnumeration() {
   	
  	if (m_firstElementP) {
  	  delete(m_firstElementP);
  	}
  	  	
  }
  
  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::reset() {
  	
  	m_currentElementP = m_firstElementP;
  	
  }
  	  
  //----------------------------------------------------------------------------
  bool
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::hasNext() const {
  	
  	return (m_currentElementP != 0);
  
  }
  
  //----------------------------------------------------------------------------
  int
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::getSize() const {
  	
    int size = 0;
    Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement* followingP = m_firstElementP;
  	
  	while (followingP) {
      followingP = followingP->m_nextP;
      ++size;
    }
  	
    return size;
    
  }
  
  //----------------------------------------------------------------------------
  const Linux_SambaPrinterPrintingOptionsInstance&  
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::getElement(int anIndex) const {
   
    Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement* followingP = m_firstElementP;
   
    int x = 0;
    while (followingP && (x < anIndex)) {
      followingP = followingP->m_nextP;
      ++x;
    }
    
    return *(followingP->m_elementP);

  }
  
  //----------------------------------------------------------------------------
  const Linux_SambaPrinterPrintingOptionsInstance&
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::getNext() {
   	
    Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement* currentElementP =
  	  m_currentElementP;

    m_currentElementP = m_currentElementP->m_nextP;
  	 
    return *(currentElementP->m_elementP);

  }
  	  
  //----------------------------------------------------------------------------
  void
  Linux_SambaPrinterPrintingOptionsInstanceEnumeration::addElement(
    const Linux_SambaPrinterPrintingOptionsInstance& anInstance) {
   	
  	if (m_firstElementP == 0) {
  	  m_firstElementP = new Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement();
  	  m_firstElementP->m_elementP = new Linux_SambaPrinterPrintingOptionsInstance(anInstance);
  	  m_endElementP = m_firstElementP;
  	  m_currentElementP = m_firstElementP;
  	} else {
  	  m_endElementP->m_nextP = new Linux_SambaPrinterPrintingOptionsInstanceEnumerationElement();
  	  m_endElementP = m_endElementP->m_nextP;
  	  m_endElementP->m_elementP = new Linux_SambaPrinterPrintingOptionsInstance(anInstance);
  	}

  }
  
}
