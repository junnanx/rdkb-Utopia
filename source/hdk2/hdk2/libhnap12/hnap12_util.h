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

/*
 * hnap12_util.h
 *
 * Various utility functions that may be used by other hdk modules.
 *
 */

#ifndef __HNAP12_UTIL_H__
#define __HNAP12_UTIL_H__

#include "hdk_xml.h"


/*
 * IPAdress Helpers
 */

/* Validate that pIP is not 0.0.0.0 and is not the broadcast address for pSubnet */
int HNAP12_UTL_IPAddress_IsValid(HDK_XML_IPAddress* pIP, HDK_XML_IPAddress* pSubnet);

/*
 * Validates that the entire range of IPs between pIPFirst and
 * pIPLast are within the subnet computed from the pDevIp and pSubnet.
 */
int HNAP12_UTL_IPAddress_IsValidRange(HDK_XML_IPAddress* pIP, HDK_XML_IPAddress* pSubnet,
                                      HDK_XML_IPAddress* pIPFirst, HDK_XML_IPAddress* pIPLast);

/*
 * Validates that a subnet mask is in the correct form, ie. all
 * 1's followed by all 0's (in binary form)
 */
int HNAP12_UTL_IPAddress_IsValidSubnet(HDK_XML_IPAddress* pSubnet);

/*
 * Validates that pIPAddress falls within the subnet computed
 * from pIP and pSubnet.
 */
int HNAP12_UTL_IPAddress_IsWithinSubnet(HDK_XML_IPAddress* pIP, HDK_XML_IPAddress* pSubnet,
                                        HDK_XML_IPAddress* pIPAddress);


/*
 * Password/SSID/character Helpers
 */

/* Validate admin passwords */
int HNAP12_UTL_AdminPassword_IsValid(char* pszPassword);

/* Validate passwords */
int HNAP12_UTL_Password_IsValid(char* pszPassword);

/* Validate SSIDs */
int HNAP12_UTL_SSID_IsValid(char* pszSSID);

/* Validate printable ASCII characters */
int HNAP12_UTL_Ascii_IsValid(char* pszStr);

/* Validate HEX characters */
int HNAP12_UTL_Hex_IsValid(char* pszStr);


/*
 * WEP/WPA Helpers
 */

/* Validate WPA/WPA2 keys */
int HNAP12_UTL_WPAKey_IsValid(char* pszKey, int fAllowHex);

/* Validate WEP-64/128 keys */
int HNAP12_UTL_WEPKey_IsValid(char* pszKey);

#endif /* __HNAP12_UTIL_H__ */
