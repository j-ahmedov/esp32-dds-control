

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from smart_home.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef smart_home_701303453_hpp
#define smart_home_701303453_hpp

#include <iosfwd>

#if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
#undef RTIUSERDllExport
#define RTIUSERDllExport __attribute__((visibility("default")))
#endif

#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/External.hpp"
#include "rti/core/LongDouble.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/core/array.hpp"
#include "rti/topic/TopicTraits.hpp"

#include "omg/types/string_view.hpp"

#include "omg/types/sequence.hpp"
#include "omg/types/optional.hpp"

#ifndef NDDS_STANDALONE_TYPE
#include "cdr/cdr_typeCode.h"
#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#endif

#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __attribute__((visibility("default")))
#endif

namespace smart_home {

    struct NDDSUSERDllExport LedCommand {
        uint16_t id {};
        uint16_t brightness {};

        LedCommand();

        LedCommand(uint16_t id_,uint16_t brightness_);

    };

    NDDSUSERDllExport bool operator == (const LedCommand& a, const LedCommand& b);
    NDDSUSERDllExport bool operator != (const LedCommand& a, const LedCommand& b);
    NDDSUSERDllExport void swap(LedCommand& a, LedCommand& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const LedCommand& sample);

    struct NDDSUSERDllExport ServoCommand {
        uint16_t angle {};

        ServoCommand();

        explicit ServoCommand(uint16_t angle_);

    };

    NDDSUSERDllExport bool operator == (const ServoCommand& a, const ServoCommand& b);
    NDDSUSERDllExport bool operator != (const ServoCommand& a, const ServoCommand& b);
    NDDSUSERDllExport void swap(ServoCommand& a, ServoCommand& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ServoCommand& sample);

    struct NDDSUSERDllExport DeviceState {
        uint16_t led1 {};
        uint16_t led2 {};
        uint16_t servo_angle {};

        DeviceState();

        DeviceState(uint16_t led1_,uint16_t led2_,uint16_t servo_angle_);

    };

    NDDSUSERDllExport bool operator == (const DeviceState& a, const DeviceState& b);
    NDDSUSERDllExport bool operator != (const DeviceState& a, const DeviceState& b);
    NDDSUSERDllExport void swap(DeviceState& a, DeviceState& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const DeviceState& sample);

} // namespace smart_home  

#ifdef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace topic {
    }
}
#else

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< ::smart_home::LedCommand > {
            NDDSUSERDllExport static std::string value() {
                return "smart_home::LedCommand";
            }
        };

        template<>
        struct is_topic_type< ::smart_home::LedCommand > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::smart_home::LedCommand > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::smart_home::LedCommand& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::smart_home::LedCommand& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::smart_home::LedCommand& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::smart_home::LedCommand& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::smart_home::ServoCommand > {
            NDDSUSERDllExport static std::string value() {
                return "smart_home::ServoCommand";
            }
        };

        template<>
        struct is_topic_type< ::smart_home::ServoCommand > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::smart_home::ServoCommand > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::smart_home::ServoCommand& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::smart_home::ServoCommand& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::smart_home::ServoCommand& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::smart_home::ServoCommand& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::smart_home::DeviceState > {
            NDDSUSERDllExport static std::string value() {
                return "smart_home::DeviceState";
            }
        };

        template<>
        struct is_topic_type< ::smart_home::DeviceState > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::smart_home::DeviceState > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::smart_home::DeviceState& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::smart_home::DeviceState& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::smart_home::DeviceState& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::smart_home::DeviceState& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
    }
}

namespace rti { 
    namespace topic {

        template<>
        struct dynamic_type< ::smart_home::LedCommand > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::smart_home::LedCommand > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::smart_home::ServoCommand > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::smart_home::ServoCommand > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::smart_home::DeviceState > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::smart_home::DeviceState > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

    }
}

#endif // NDDS_STANDALONE_TYPE
#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // smart_home_701303453_hpp
