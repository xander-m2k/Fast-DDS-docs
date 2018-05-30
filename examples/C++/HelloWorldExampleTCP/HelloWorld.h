// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file HelloWorld.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _HelloWorld_H_
#define _HelloWorld_H_

// TODO Poner en el contexto.

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif
#else
#include <unistd.h>
#define eProsima_user_DllExport
#endif

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(HelloWorld_SOURCE)
#define HelloWorld_DllAPI __declspec( dllexport )
#else
#define HelloWorld_DllAPI __declspec( dllimport )
#endif // HelloWorld_SOURCE
#else
#define HelloWorld_DllAPI
#endif
#else
#define HelloWorld_DllAPI
#endif // _WIN32

namespace eprosima
{
    namespace fastcdr
    {
        class Cdr;
    }
}

/*!
 * @brief This class represents the structure HelloWorld defined by the user in the IDL file.
 * @ingroup HELLOWORLD
 */
class HelloWorld
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport HelloWorld();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~HelloWorld();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object HelloWorld that will be copied.
     */
    eProsima_user_DllExport HelloWorld(const HelloWorld &x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object HelloWorld that will be copied.
     */
    eProsima_user_DllExport HelloWorld(HelloWorld &&x);

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object HelloWorld that will be copied.
     */
    eProsima_user_DllExport HelloWorld& operator=(const HelloWorld &x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object HelloWorld that will be copied.
     */
    eProsima_user_DllExport HelloWorld& operator=(HelloWorld &&x);

    /*!
     * @brief This function sets a value in member index
     * @param _index New value for member index
     */
    inline eProsima_user_DllExport void index(uint32_t _index)
    {
        m_index = _index;
    }

    /*!
     * @brief This function returns the value of member index
     * @return Value of member index
     */
    inline eProsima_user_DllExport uint32_t index() const
    {
        return m_index;
    }

    /*!
     * @brief This function returns a reference to member index
     * @return Reference to member index
     */
    inline eProsima_user_DllExport uint32_t& index()
    {
        return m_index;
    }
    /*!
     * @brief This function copies the value in member message
     * @param _message New value to be copied in member message
     */
    inline eProsima_user_DllExport void message(const std::string &_message)
    {
        m_message = _message;
    }

    /*!
     * @brief This function moves the value in member message
     * @param _message New value to be moved in member message
     */
    inline eProsima_user_DllExport void message(std::string &&_message)
    {
        m_message = std::move(_message);
    }

    /*!
     * @brief This function returns a constant reference to member message
     * @return Constant reference to member message
     */
    inline eProsima_user_DllExport const std::string& message() const
    {
        return m_message;
    }

    /*!
     * @brief This function returns a reference to member message
     * @return Reference to member message
     */
    inline eProsima_user_DllExport std::string& message()
    {
        return m_message;
    }

    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(const HelloWorld& data, size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(eprosima::fastcdr::Cdr &cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(eprosima::fastcdr::Cdr &cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(eprosima::fastcdr::Cdr &cdr) const;

    inline static void ProcessMemUsage(double& vm_usage, double& resident_set)
    {
#if defined(_WIN32)
        //TODO: Memory management
        vm_usage = 0;
        resident_set = 0;
#else
        using std::ios_base;
        using std::ifstream;
        using std::string;

        vm_usage     = 0.0;
        resident_set = 0.0;

        // 'file' stat seems to give the most reliable results
        //
        ifstream stat_stream("/proc/self/stat",ios_base::in);

        // dummy vars for leading entries in stat that we don't care about
        //
        string pid, comm, state, ppid, pgrp, session, tty_nr;
        string tpgid, flags, minflt, cminflt, majflt, cmajflt;
        string utime, stime, cutime, cstime, priority, nice;
        string O, itrealvalue, starttime;

        // the two fields we want
        //
        unsigned long vsize;
        long rss;

        stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                    >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                    >> utime >> stime >> cutime >> cstime >> priority >> nice
                    >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

        stat_stream.close();

        long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
        vm_usage     = vsize / 1024.0;
        resident_set = rss * page_size_kb;
#endif
    }

private:
    uint32_t m_index;
    std::string m_message;
};

#endif // _HelloWorld_H_