/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

#ifndef __UNITTEST_UTIL_H__
#define __UNITTEST_UTIL_H__

#include "hdk_xml.h"

/* Convert HDK types to string - NOT thread-safe! */
extern const char* DateTimeToString(time_t t, int fUTC);
extern const char* IPAddressToString(const HDK_XML_IPAddress* pIP);
extern const char* MACAddressToString(const HDK_XML_MACAddress* pMAC);
extern const char* UUIDToString(const HDK_XML_UUID* pUUID);
extern const char* ParseErrorToString(HDK_XML_ParseError parseError);
extern const char* BuiltinTypeToString(HDK_XML_BuiltinType type);

/* Helper function for parse/serialize/validate tests */
extern void ParseTestHelper(HDK_XML_Struct* pStruct, const HDK_XML_SchemaNode* pSchemaNodes,
                            const HDK_XML_EnumType* pEnumTypes, unsigned int ixSchemaNode,
                            int options, unsigned int cbMaxAlloc, ... /* XML chunks */);

/* ParseTestHelper options */
typedef enum _ParseTestHelper_Options
{
    ParseTestHelper_NoSerialize = 0x01,
    ParseTestHelper_NoValidate = 0x02,
    ParseTestHelper_ErrorOutput = 0x04,
    ParseTestHelper_Parse_NoXML = 0x8,
    ParseTestHelper_Parse_Member = 0x10,
    ParseTestHelper_Parse_CSV = 0x20,
    ParseTestHelper_Serialize_NoNewlines = 0x40,
    ParseTestHelper_Serialize_NoXML = 0x80,
    ParseTestHelper_Serialize_CSV = 0x100
} ParseTestHelper_Options;

/* ParseTestHelper XML chunks terminator */
#define ParseTestHelperEnd (const char*)0

#endif /* __UNITTEST_UTIL_H__ */
