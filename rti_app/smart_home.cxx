

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from smart_home.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>
#include <atomic>

#ifndef NDDS_STANDALONE_TYPE
#include "rti/topic/cdr/Serialization.hpp"
#include "smart_homePlugin.hpp"
#else
#include "rti/topic/cdr/SerializationHelpers.hpp"
#endif

#include "smart_home.hpp"

#include <rti/util/ostream_operators.hpp>

namespace smart_home {

    // ---- LedCommand:

    LedCommand::LedCommand() :
        id (0) ,
        brightness (0)  {

    }

    LedCommand::LedCommand (uint16_t id_,uint16_t brightness_) {
        id = id_;
        brightness = brightness_;
    }

    bool operator == (const LedCommand& a, const LedCommand& b) {

        if (a.id != b.id) {
            return false;
        }
        if (a.brightness != b.brightness) {
            return false;
        }

        return true;
    }

    bool operator != (const LedCommand& a, const LedCommand& b) {
        return !operator ==(a, b);
    }

    void swap(LedCommand& a, LedCommand& b) noexcept
    {
        using std::swap;

        swap(a.id, b.id);
        swap(a.brightness, b.brightness);

    }  
    std::ostream& operator << (std::ostream& o,const LedCommand& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "id: " << sample.id<<", ";
        o << "brightness: " << sample.brightness;
        o <<"]";
        return o;
    }

    // ---- ServoCommand:

    ServoCommand::ServoCommand() :
        angle (0)  {

    }

    ServoCommand::ServoCommand (uint16_t angle_) {
        angle = angle_;
    }

    bool operator == (const ServoCommand& a, const ServoCommand& b) {

        if (a.angle != b.angle) {
            return false;
        }

        return true;
    }

    bool operator != (const ServoCommand& a, const ServoCommand& b) {
        return !operator ==(a, b);
    }

    void swap(ServoCommand& a, ServoCommand& b) noexcept
    {
        using std::swap;

        swap(a.angle, b.angle);

    }  
    std::ostream& operator << (std::ostream& o,const ServoCommand& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "angle: " << sample.angle;
        o <<"]";
        return o;
    }

    // ---- DeviceState:

    DeviceState::DeviceState() :
        led1 (0) ,
        led2 (0) ,
        servo_angle (0)  {

    }

    DeviceState::DeviceState (uint16_t led1_,uint16_t led2_,uint16_t servo_angle_) {
        led1 = led1_;
        led2 = led2_;
        servo_angle = servo_angle_;
    }

    bool operator == (const DeviceState& a, const DeviceState& b) {

        if (a.led1 != b.led1) {
            return false;
        }
        if (a.led2 != b.led2) {
            return false;
        }
        if (a.servo_angle != b.servo_angle) {
            return false;
        }

        return true;
    }

    bool operator != (const DeviceState& a, const DeviceState& b) {
        return !operator ==(a, b);
    }

    void swap(DeviceState& a, DeviceState& b) noexcept
    {
        using std::swap;

        swap(a.led1, b.led1);
        swap(a.led2, b.led2);
        swap(a.servo_angle, b.servo_angle);

    }  
    std::ostream& operator << (std::ostream& o,const DeviceState& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "led1: " << sample.led1<<", ";
        o << "led2: " << sample.led2<<", ";
        o << "servo_angle: " << sample.servo_angle;
        o <<"]";
        return o;
    }

} // namespace smart_home  

#ifdef NDDS_STANDALONE_TYPE
namespace rti {
    namespace topic {
    }
}

#else
// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        template<>
        struct native_type_code< ::smart_home::LedCommand > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member LedCommand_g_tc_members[2]=
                {

                    {
                        (char *)"id",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"brightness",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode LedCommand_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"smart_home::LedCommand", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        LedCommand_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for LedCommand*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &LedCommand_g_tc;
                }

                LedCommand_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                LedCommand_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                LedCommand_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;

                /* Initialize the values for member annotations. */
                LedCommand_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
                LedCommand_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                LedCommand_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                LedCommand_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                LedCommand_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                LedCommand_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                LedCommand_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

                LedCommand_g_tc._data._sampleAccessInfo = sample_access_info();
                LedCommand_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &LedCommand_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::smart_home::LedCommand *sample;

                static RTIXCdrMemberAccessInfo LedCommand_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo LedCommand_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &LedCommand_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::smart_home::LedCommand);
                if (sample == NULL) {
                    return NULL;
                }

                LedCommand_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->id - (char *)sample);

                LedCommand_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->brightness - (char *)sample);

                LedCommand_g_sampleAccessInfo.memberAccessInfos =
                LedCommand_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::smart_home::LedCommand);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        LedCommand_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        LedCommand_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                LedCommand_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                LedCommand_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::smart_home::LedCommand >;

                LedCommand_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &LedCommand_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin LedCommand_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &LedCommand_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::smart_home::LedCommand >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::smart_home::LedCommand >::get())));
        }

        template<>
        struct native_type_code< ::smart_home::ServoCommand > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member ServoCommand_g_tc_members[1]=
                {

                    {
                        (char *)"angle",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ServoCommand_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"smart_home::ServoCommand", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        1, /* Number of members */
                        ServoCommand_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ServoCommand*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &ServoCommand_g_tc;
                }

                ServoCommand_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ServoCommand_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;

                /* Initialize the values for member annotations. */
                ServoCommand_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                ServoCommand_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
                ServoCommand_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                ServoCommand_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                ServoCommand_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                ServoCommand_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

                ServoCommand_g_tc._data._sampleAccessInfo = sample_access_info();
                ServoCommand_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &ServoCommand_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::smart_home::ServoCommand *sample;

                static RTIXCdrMemberAccessInfo ServoCommand_g_memberAccessInfos[1] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ServoCommand_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &ServoCommand_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::smart_home::ServoCommand);
                if (sample == NULL) {
                    return NULL;
                }

                ServoCommand_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->angle - (char *)sample);

                ServoCommand_g_sampleAccessInfo.memberAccessInfos =
                ServoCommand_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::smart_home::ServoCommand);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        ServoCommand_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        ServoCommand_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ServoCommand_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ServoCommand_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::smart_home::ServoCommand >;

                ServoCommand_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &ServoCommand_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ServoCommand_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ServoCommand_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::smart_home::ServoCommand >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::smart_home::ServoCommand >::get())));
        }

        template<>
        struct native_type_code< ::smart_home::DeviceState > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member DeviceState_g_tc_members[3]=
                {

                    {
                        (char *)"led1",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"led2",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"servo_angle",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode DeviceState_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"smart_home::DeviceState", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        3, /* Number of members */
                        DeviceState_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for DeviceState*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &DeviceState_g_tc;
                }

                DeviceState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                DeviceState_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DeviceState_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DeviceState_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;

                /* Initialize the values for member annotations. */
                DeviceState_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[0]._annotations._defaultValue._u.ushort_value = 0;
                DeviceState_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[0]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DeviceState_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[0]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DeviceState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                DeviceState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DeviceState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DeviceState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                DeviceState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DeviceState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DeviceState_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

                DeviceState_g_tc._data._sampleAccessInfo = sample_access_info();
                DeviceState_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &DeviceState_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::smart_home::DeviceState *sample;

                static RTIXCdrMemberAccessInfo DeviceState_g_memberAccessInfos[3] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo DeviceState_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &DeviceState_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::smart_home::DeviceState);
                if (sample == NULL) {
                    return NULL;
                }

                DeviceState_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->led1 - (char *)sample);

                DeviceState_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->led2 - (char *)sample);

                DeviceState_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->servo_angle - (char *)sample);

                DeviceState_g_sampleAccessInfo.memberAccessInfos =
                DeviceState_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::smart_home::DeviceState);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        DeviceState_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        DeviceState_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                DeviceState_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                DeviceState_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::smart_home::DeviceState >;

                DeviceState_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &DeviceState_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin DeviceState_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &DeviceState_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::smart_home::DeviceState >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::smart_home::DeviceState >::get())));
        }
    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ::smart_home::LedCommand >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::smart_home::LedCommandPlugin_new,
                ::smart_home::LedCommandPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::smart_home::LedCommand >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::smart_home::LedCommand& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = LedCommandPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = LedCommandPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::smart_home::LedCommand >::from_cdr_buffer(::smart_home::LedCommand& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = LedCommandPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::smart_home::LedCommand from cdr buffer");
        }

        void topic_type_support< ::smart_home::LedCommand >::reset_sample(::smart_home::LedCommand& sample) 
        {
            sample.id = 0;
            sample.brightness = 0;
        }

        void topic_type_support< ::smart_home::LedCommand >::allocate_sample(::smart_home::LedCommand& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
        void topic_type_support< ::smart_home::ServoCommand >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::smart_home::ServoCommandPlugin_new,
                ::smart_home::ServoCommandPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::smart_home::ServoCommand >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::smart_home::ServoCommand& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ServoCommandPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ServoCommandPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::smart_home::ServoCommand >::from_cdr_buffer(::smart_home::ServoCommand& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ServoCommandPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::smart_home::ServoCommand from cdr buffer");
        }

        void topic_type_support< ::smart_home::ServoCommand >::reset_sample(::smart_home::ServoCommand& sample) 
        {
            sample.angle = 0;
        }

        void topic_type_support< ::smart_home::ServoCommand >::allocate_sample(::smart_home::ServoCommand& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
        void topic_type_support< ::smart_home::DeviceState >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::smart_home::DeviceStatePlugin_new,
                ::smart_home::DeviceStatePlugin_delete);
        }

        std::vector<char>& topic_type_support< ::smart_home::DeviceState >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::smart_home::DeviceState& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = DeviceStatePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = DeviceStatePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::smart_home::DeviceState >::from_cdr_buffer(::smart_home::DeviceState& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = DeviceStatePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::smart_home::DeviceState from cdr buffer");
        }

        void topic_type_support< ::smart_home::DeviceState >::reset_sample(::smart_home::DeviceState& sample) 
        {
            sample.led1 = 0;
            sample.led2 = 0;
            sample.servo_angle = 0;
        }

        void topic_type_support< ::smart_home::DeviceState >::allocate_sample(::smart_home::DeviceState& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
    }
}  

#endif // NDDS_STANDALONE_TYPE
