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

#pragma once

// actual_client_location.h - [Generated by hdkcli_cpp]

// Non-generated client code.
#include "hdk_cli_cpp.h"

// Underlying schema module.
#include "actual_client_mod.h"


namespace HDK
{
    ///
    /// \fn InitializeClient
    ///      Initialize the HDK client library.  This should be called once per application instance.
    ///      Each call to InitializeClient should be matched by a call to UninitializeClient.
    ///      \retval true if initialization was successful, false if not.
    ///
    bool InitializeClient() throw();

    ///
    /// \fn UninitializeClient
    ///      Cleanup the HDK client library.  This should be called if true was returned from InitializeClient
    ///      When the caller is done using the HDK client library.
    ///
    void UninitializeClient() throw();


    namespace Cisco_A
    {
        ///
        /// \enum CiscoActionResult
        ///      <a>http://cisco.com/HNAPExt/A/CiscoActionResult</a>
        ///
        enum CiscoActionResult
        {
            CiscoActionResult_Unknown = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoActionResult__UNKNOWN__ /*<! Unknown value */,
            CiscoActionResult_OK = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoActionResult_OK /*!< OK */,
            CiscoActionResult_ERROR = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoActionResult_ERROR /*!< ERROR */
        }; // enum CiscoActionResult

        ///
        /// \enum CiscoEnum
        ///      <a>http://cisco.com/HNAPExt/A/CiscoEnum</a>
        ///
        enum CiscoEnum
        {
            CiscoEnum_Unknown = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoEnum__UNKNOWN__ /*<! Unknown value */,
            CiscoEnum_Value1 = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoEnum_Value1 /*!< Value1 */,
            CiscoEnum_Value2 = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoEnum_Value2 /*!< Value2 */,
            CiscoEnum_Value3 = ACTUAL_CLIENT_MOD_Enum_Cisco_A_CiscoEnum_Value3 /*!< Value3 */
        }; // enum CiscoEnum

    } // namespace Cisco_A

    namespace Cisco
    {
        ///
        /// \enum CiscoActionResult
        ///      <a>http://cisco.com/HNAPExt/CiscoActionResult</a>
        ///
        enum CiscoActionResult
        {
            CiscoActionResult_Unknown = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoActionResult__UNKNOWN__ /*<! Unknown value */,
            CiscoActionResult_OK = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoActionResult_OK /*!< OK */,
            CiscoActionResult_ERROR = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoActionResult_ERROR /*!< ERROR */
        }; // enum CiscoActionResult

        ///
        /// \enum CiscoEnum
        ///      <a>http://cisco.com/HNAPExt/CiscoEnum</a>
        ///
        enum CiscoEnum
        {
            CiscoEnum_Unknown = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoEnum__UNKNOWN__ /*<! Unknown value */,
            CiscoEnum_Value1 = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoEnum_Value1 /*!< Value1 */,
            CiscoEnum_Value2 = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoEnum_Value2 /*!< Value2 */,
            CiscoEnum_Value3 = ACTUAL_CLIENT_MOD_Enum_Cisco_CiscoEnum_Value3 /*!< Value3 */
        }; // enum CiscoEnum

    } // namespace Cisco

    namespace Cisco_A
    {
        ///
        /// \class CiscoEnumArray
        ///      Wrapper class for accessing arrays of CiscoEnum values.
        ///
        typedef HDK::EnumArray<enum CiscoEnum, ACTUAL_CLIENT_MOD_EnumType_Cisco_A_CiscoEnum, ACTUAL_CLIENT_MOD_Element_Cisco_A_string> CiscoEnumArray;
        typedef HDK::EnumArray<enum CiscoEnum, ACTUAL_CLIENT_MOD_EnumType_Cisco_A_CiscoEnum, ACTUAL_CLIENT_MOD_Element_Cisco_A_string>::EnumArrayIter CiscoEnumArrayIter;

        ///
        /// \class CiscoStructArray
        ///      Wrapper class for accessing arrays of CiscoStruct values.
        ///
        class CiscoStructStruct; // forward declaration
        typedef HDK::StructArray<CiscoStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_A_CiscoStruct> CiscoStructArray;
        typedef HDK::StructArray<CiscoStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_A_CiscoStruct>::StructArrayIter CiscoStructArrayIter;

        ///
        /// \class IntArray
        ///      Wrapper class for accessing arrays of int values.
        ///
        typedef HDK::IntArray<ACTUAL_CLIENT_MOD_Element_Cisco_A_int> IntArray;
        typedef HDK::IntArray<ACTUAL_CLIENT_MOD_Element_Cisco_A_int>::IntArrayIter IntArrayIter;

        ///
        /// \class StringArray
        ///      Wrapper class for accessing arrays of string values.
        ///
        typedef HDK::StringArray<ACTUAL_CLIENT_MOD_Element_Cisco_A_string> StringArray;
        typedef HDK::StringArray<ACTUAL_CLIENT_MOD_Element_Cisco_A_string>::StringArrayIter StringArrayIter;

    } // namespace Cisco_A

    namespace Cisco
    {
        ///
        /// \class CiscoCSVableStructArray
        ///      Wrapper class for accessing arrays of CiscoCSVableStruct values.
        ///
        class CiscoCSVableStructStruct; // forward declaration
        typedef HDK::StructArray<CiscoCSVableStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_CiscoCSVableStruct> CiscoCSVableStructArray;
        typedef HDK::StructArray<CiscoCSVableStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_CiscoCSVableStruct>::StructArrayIter CiscoCSVableStructArrayIter;

        ///
        /// \class CiscoEnumArray
        ///      Wrapper class for accessing arrays of CiscoEnum values.
        ///
        typedef HDK::EnumArray<enum CiscoEnum, ACTUAL_CLIENT_MOD_EnumType_Cisco_CiscoEnum, ACTUAL_CLIENT_MOD_Element_Cisco_string> CiscoEnumArray;
        typedef HDK::EnumArray<enum CiscoEnum, ACTUAL_CLIENT_MOD_EnumType_Cisco_CiscoEnum, ACTUAL_CLIENT_MOD_Element_Cisco_string>::EnumArrayIter CiscoEnumArrayIter;

        ///
        /// \class CiscoStructArray
        ///      Wrapper class for accessing arrays of CiscoStruct values.
        ///
        class CiscoStructStruct; // forward declaration
        typedef HDK::StructArray<CiscoStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_CiscoStruct> CiscoStructArray;
        typedef HDK::StructArray<CiscoStructStruct, ACTUAL_CLIENT_MOD_Element_Cisco_CiscoStruct>::StructArrayIter CiscoStructArrayIter;

        ///
        /// \class IntArray
        ///      Wrapper class for accessing arrays of int values.
        ///
        typedef HDK::IntArray<ACTUAL_CLIENT_MOD_Element_Cisco_int> IntArray;
        typedef HDK::IntArray<ACTUAL_CLIENT_MOD_Element_Cisco_int>::IntArrayIter IntArrayIter;

        ///
        /// \class StringArray
        ///      Wrapper class for accessing arrays of string values.
        ///
        typedef HDK::StringArray<ACTUAL_CLIENT_MOD_Element_Cisco_string> StringArray;
        typedef HDK::StringArray<ACTUAL_CLIENT_MOD_Element_Cisco_string>::StringArrayIter StringArrayIter;

    } // namespace Cisco

    namespace Cisco_A
    {
        ///
        /// \brief CiscoStruct
        ///      <a>http://cisco.com/HNAPExt/A/CiscoStruct</a>
        ///
        class CiscoStructStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoStructStruct() throw();

            CiscoStructStruct(HDK_XML_Struct* phdkstruct) throw();

            ///
            /// \brief Get the a value.
            ///
            HDK_XML_Int get_a() const throw();

            ///
            /// \brief Set the a value.
            ///
            void set_a(HDK_XML_Int value) throw();

            ///
            /// \brief Get the as value.
            ///
            IntArray get_as() const throw();

            ///
            /// \brief Set the as value.
            ///
            void set_as(const IntArray& value) throw();

            ///
            /// \brief Get the b value.
            ///
            const char* get_b() const throw();

            ///
            /// \brief Set the b value.
            ///
            void set_b(const char* value) throw();

            ///
            /// \brief Get the bs value.
            ///
            StringArray get_bs() const throw();

            ///
            /// \brief Set the bs value.
            ///
            void set_bs(const StringArray& value) throw();

            ///
            /// \brief Get the c value.
            ///
            enum CiscoEnum get_c() const throw();

            ///
            /// \brief Set the c value.
            ///
            void set_c(enum CiscoEnum value) throw();

            ///
            /// \brief Get the cs value.
            ///
            CiscoEnumArray get_cs() const throw();

            ///
            /// \brief Set the cs value.
            ///
            void set_cs(const CiscoEnumArray& value) throw();

        }; // class CiscoStructStruct : public Struct

    } // namespace Cisco_A

    namespace Cisco
    {
        ///
        /// \brief CiscoCSVableStruct
        ///      <a>http://cisco.com/HNAPExt/CiscoCSVableStruct</a>
        ///
        class CiscoCSVableStructStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoCSVableStructStruct() throw();

            CiscoCSVableStructStruct(HDK_XML_Struct* phdkstruct) throw();

            ///
            /// \brief Get the a value.
            ///
            HDK_XML_Int get_a() const throw();

            ///
            /// \brief Set the a value.
            ///
            void set_a(HDK_XML_Int value) throw();

            ///
            /// \brief Get the b value.
            ///
            const char* get_b() const throw();

            ///
            /// \brief Set the b value.
            ///
            void set_b(const char* value) throw();

            ///
            /// \brief Get the c value.
            ///
            time_t get_c() const throw();

            ///
            /// \brief Set the c value.
            ///
            void set_c(time_t value) throw();

        }; // class CiscoCSVableStructStruct : public Struct

        ///
        /// \brief CiscoStruct
        ///      <a>http://cisco.com/HNAPExt/CiscoStruct</a>
        ///
        class CiscoStructStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoStructStruct() throw();

            CiscoStructStruct(HDK_XML_Struct* phdkstruct) throw();

            ///
            /// \brief Get the a value.
            ///
            HDK_XML_Int get_a() const throw();

            ///
            /// \brief Set the a value.
            ///
            void set_a(HDK_XML_Int value) throw();

            ///
            /// \brief Get the as value.
            ///
            IntArray get_as() const throw();

            ///
            /// \brief Set the as value.
            ///
            void set_as(const IntArray& value) throw();

            ///
            /// \brief Get the b value.
            ///
            const char* get_b() const throw();

            ///
            /// \brief Set the b value.
            ///
            void set_b(const char* value) throw();

            ///
            /// \brief Get the bs value.
            ///
            StringArray get_bs() const throw();

            ///
            /// \brief Set the bs value.
            ///
            void set_bs(const StringArray& value) throw();

            ///
            /// \brief Get the c value.
            ///
            enum CiscoEnum get_c() const throw();

            ///
            /// \brief Set the c value.
            ///
            void set_c(enum CiscoEnum value) throw();

            ///
            /// \brief Get the cs value.
            ///
            CiscoEnumArray get_cs() const throw();

            ///
            /// \brief Set the cs value.
            ///
            void set_cs(const CiscoEnumArray& value) throw();

        }; // class CiscoStructStruct : public Struct

        ///
        /// \brief CiscoAction
        ///      <a>http://cisco.com/HNAPExt/CiscoAction</a>
        ///
        class CiscoActionStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionStruct() throw();

            ///
            /// \brief Get the a value.
            ///
            CiscoStructStruct get_a() const throw();

            ///
            /// \brief Set the a value.
            ///
            void set_a(const CiscoStructStruct& value) throw();

            ///
            /// \brief Get the csvInts value.
            ///
            IntArray get_csvInts() const throw();

            ///
            /// \brief Set the csvInts value.
            ///
            void set_csvInts(const IntArray& value) throw();

            ///
            /// \brief Get the csvStruct value.
            ///
            CiscoCSVableStructStruct get_csvStruct() const throw();

            ///
            /// \brief Set the csvStruct value.
            ///
            void set_csvStruct(const CiscoCSVableStructStruct& value) throw();

            ///
            /// \brief Get the csvStructs value.
            ///
            CiscoCSVableStructArray get_csvStructs() const throw();

            ///
            /// \brief Set the csvStructs value.
            ///
            void set_csvStructs(const CiscoCSVableStructArray& value) throw();

        }; // class CiscoActionStruct : public Struct

        ///
        /// \brief CiscoActionResponse
        ///      <a>http://cisco.com/HNAPExt/CiscoActionResponse</a>
        ///
        class CiscoActionResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionResponseStruct() throw();

            ///
            /// \brief Get the CiscoActionResult value.
            ///
            enum CiscoActionResult get_CiscoActionResult() const throw();

            ///
            /// \brief Get the b value.
            ///
            CiscoStructArray get_b() const throw();

        }; // class CiscoActionResponseStruct : public Struct

    } // namespace Cisco

    namespace Cisco_A
    {
        ///
        /// \brief CiscoAction
        ///      <a>http://cisco.com/HNAPExt/A/CiscoAction</a>
        ///
        class CiscoActionStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionStruct() throw();

            ///
            /// \brief Get the a value.
            ///
            CiscoStructStruct get_a() const throw();

            ///
            /// \brief Set the a value.
            ///
            void set_a(const CiscoStructStruct& value) throw();

        }; // class CiscoActionStruct : public Struct

        ///
        /// \brief CiscoActionResponse
        ///      <a>http://cisco.com/HNAPExt/A/CiscoActionResponse</a>
        ///
        class CiscoActionResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionResponseStruct() throw();

            ///
            /// \brief Get the CiscoActionResult value.
            ///
            enum CiscoActionResult get_CiscoActionResult() const throw();

            ///
            /// \brief Get the b value.
            ///
            CiscoStructArray get_b() const throw();

        }; // class CiscoActionResponseStruct : public Struct

    } // namespace Cisco_A

    namespace Cisco
    {
        ///
        /// \brief SOAP method URI for action CiscoAction
        ///
#define Cisco_CiscoAction_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_MOD_Module(), ACTUAL_CLIENT_MOD_MethodEnum_Cisco_CiscoAction)->pszSOAPAction)

        ///
        /// \brief Call the CiscoAction method on a given device.
        ///     <a>http://cisco.com/HNAPExt/CiscoAction</a>
        ///     This method uses HTTP method POST and location 'Other'
        ///
        ///     Possible result values:
        ///          - #CiscoActionResult_OK
        ///          - #CiscoActionResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the CiscoAction HNAP method.
        ///     \arg output The output argument data from the CiscoAction HNAP method.
        ///     \arg[optional] result The HNAP result of the CiscoAction HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError CiscoAction
        (
            HDK::ITarget* pTarget,
            const CiscoActionStruct & input,
            CiscoActionResponseStruct & output,
            enum CiscoActionResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco

    namespace Cisco_A
    {
        ///
        /// \brief SOAP method URI for action CiscoAction
        ///
#define Cisco_A_CiscoAction_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_MOD_Module(), ACTUAL_CLIENT_MOD_MethodEnum_Cisco_A_CiscoAction)->pszSOAPAction)

        ///
        /// \brief Call the CiscoAction method on a given device.
        ///     <a>http://cisco.com/HNAPExt/A/CiscoAction</a>
        ///     This method uses HTTP method POST and location 'Other'
        ///
        ///     Possible result values:
        ///          - #CiscoActionResult_OK
        ///          - #CiscoActionResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the CiscoAction HNAP method.
        ///     \arg output The output argument data from the CiscoAction HNAP method.
        ///     \arg[optional] result The HNAP result of the CiscoAction HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError CiscoAction
        (
            HDK::ITarget* pTarget,
            const CiscoActionStruct & input,
            CiscoActionResponseStruct & output,
            enum CiscoActionResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco_A
} // namespace HDK
