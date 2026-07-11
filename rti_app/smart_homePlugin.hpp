

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from smart_home.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef smart_homePlugin_701303453_h
#define smart_homePlugin_701303453_h

#include "smart_home.hpp"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
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

    #define LedCommandPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define LedCommandPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define LedCommandPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define LedCommandPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define LedCommandPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern LedCommand*
    LedCommandPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern LedCommand*
    LedCommandPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern LedCommand*
    LedCommandPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    LedCommandPluginSupport_copy_data(
        LedCommand *out,
        const LedCommand *in);

    NDDSUSERDllExport extern void
    LedCommandPluginSupport_destroy_data_w_params(
        LedCommand *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    LedCommandPluginSupport_destroy_data_ex(
        LedCommand *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    LedCommandPluginSupport_destroy_data(
        LedCommand *sample);

    NDDSUSERDllExport extern void
    LedCommandPluginSupport_print_data(
        const LedCommand *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    LedCommandPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    LedCommandPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    LedCommandPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    LedCommandPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    LedCommandPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        LedCommand *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    LedCommandPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        LedCommand *out,
        const LedCommand *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    LedCommandPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const LedCommand *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    LedCommandPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        LedCommand **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    LedCommandPlugin_deserialize_from_cdr_buffer(
        LedCommand *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    LedCommandPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    LedCommandPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    LedCommandPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    LedCommandPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    LedCommandPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        LedCommand ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    LedCommandPlugin_new(void);

    NDDSUSERDllExport extern void
    LedCommandPlugin_delete(struct PRESTypePlugin *);

    #define ServoCommandPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define ServoCommandPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define ServoCommandPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define ServoCommandPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define ServoCommandPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    ServoCommandPluginSupport_copy_data(
        ServoCommand *out,
        const ServoCommand *in);

    NDDSUSERDllExport extern void
    ServoCommandPluginSupport_destroy_data_w_params(
        ServoCommand *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    ServoCommandPluginSupport_destroy_data_ex(
        ServoCommand *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    ServoCommandPluginSupport_destroy_data(
        ServoCommand *sample);

    NDDSUSERDllExport extern void
    ServoCommandPluginSupport_print_data(
        const ServoCommand *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    ServoCommandPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    ServoCommandPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    ServoCommandPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    ServoCommandPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    ServoCommandPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand *out,
        const ServoCommand *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ServoCommand *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_deserialize_from_cdr_buffer(
        ServoCommand *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    ServoCommandPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    ServoCommandPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    ServoCommandPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    ServoCommandPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    ServoCommandPlugin_new(void);

    NDDSUSERDllExport extern void
    ServoCommandPlugin_delete(struct PRESTypePlugin *);

    #define DeviceStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define DeviceStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define DeviceStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define DeviceStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define DeviceStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern DeviceState*
    DeviceStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern DeviceState*
    DeviceStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DeviceState*
    DeviceStatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    DeviceStatePluginSupport_copy_data(
        DeviceState *out,
        const DeviceState *in);

    NDDSUSERDllExport extern void
    DeviceStatePluginSupport_destroy_data_w_params(
        DeviceState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    DeviceStatePluginSupport_destroy_data_ex(
        DeviceState *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    DeviceStatePluginSupport_destroy_data(
        DeviceState *sample);

    NDDSUSERDllExport extern void
    DeviceStatePluginSupport_print_data(
        const DeviceState *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    DeviceStatePlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    DeviceStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    DeviceStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    DeviceStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    DeviceStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        DeviceState *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    DeviceStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DeviceState *out,
        const DeviceState *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    DeviceStatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DeviceState *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    DeviceStatePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        DeviceState **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DeviceStatePlugin_deserialize_from_cdr_buffer(
        DeviceState *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    DeviceStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    DeviceStatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    DeviceStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    DeviceStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    DeviceStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DeviceState ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    DeviceStatePlugin_new(void);

    NDDSUSERDllExport extern void
    DeviceStatePlugin_delete(struct PRESTypePlugin *);

} /* namespace smart_home  */

#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* smart_homePlugin_701303453_h */
