// ============================================================================
// Copyright © 2007, International Business Machines
//
// THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
// ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
// CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
//
// You can obtain a current copy of the Eclipse Public License from
// http://www.opensource.org/licenses/eclipse-1.0.php
//
// Authors:             Sam Kannan <samkannan (at) us.ibm.com>
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Include the required CMPI data types, function headers, and macros */
#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"

#define _CLASSNAME			"Linux_SambaElementConformsToProfile"
#define _SRCCLASSNAME 		"Linux_SambaRegisteredProfile"
#define _TARGETCLASSNAME 	"Linux_SambaService"
#define _SRCPROPERTYNAME 	"ConformantStandard"
#define _TARGETPROPERTYNAME "ManagedElement"
#define _TARGETCLASSNS 		"root/cimv2"
#define _SOURCECLASSNS 		"root/PG_InterOp"

typedef struct {
	CMPIObjectPath *src;
	CMPIObjectPath *target;
} _RESOURCEP;


// gettext support
#ifdef ENABLE_NLS
    #include <libintl.h>
    #include <locale.h>
    #define _(String) gettext(String)
    #define gettext_nohup(String) (String)
    #define N_(String) gettext_nohup(String)
#else
    #define _(String) String
    #define N_(String) String
    #define setlocale(a,b)
    #define bindtextdomain(a,b)
    #define textdomain(a)
#endif


CMPIStatus Linux_ElementConformsToProfile_GetInstance
	( const CMPIBroker *broker, const CMPIContext *context, const CMPIObjectPath *reference, const char **properties, CMPIInstance **instance);

CMPIStatus Linux_ElementConformsToProfile_GetInstanceFromResource( const CMPIBroker *broker, const CMPIContext *context, 
		const CMPIObjectPath *reference, const char ** properties, _RESOURCEP *resource, CMPIInstance **instance );

CMPIStatus Linux_ElementConformsToProfile_getResource 
	( const CMPIBroker *broker, const CMPIContext *context, const CMPIObjectPath *reference, _RESOURCEP *resource);

void Linux_ElementConformsToProfile_SetInstanceData(const CMPIBroker * broker, const CMPIInstance * instance, const _RESOURCEP *resource);

bool Linux_ElementConformsToProfile_Compare_CMPIData(const CMPIBroker *broker, const CMPIData *data1, const CMPIData *data2);

bool Linux_ElementConformsToProfile_EqualsObjectPath 
	( const CMPIBroker *broker, const CMPIObjectPath *op1, const CMPIObjectPath *op2);

bool Linux_ElementConformsToProfile_Validate(const CMPIBroker *broker, const CMPIObjectPath *op1, const CMPIObjectPath *op2, const CMPIObjectPath *resultOP,
		const char *role1, char * role2, const char *resultRole1, const char * resultRole2, const char *resultClass);
