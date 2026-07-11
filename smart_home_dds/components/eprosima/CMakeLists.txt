# ESP-IDF component wrapping eProsima Micro-XRCE-DDS-Client (v3.0.1) + Micro-CDR (v2.0.2).
# Profiles enabled via the hand-authored config.h files:
#   - UDP transport, POSIX_NOPOLL platform (lwIP BSD sockets, recvfrom + SO_RCVTIMEO)
# IMPORTANT: only ONE platform variant per transport is listed; the others
# (posix poll, windows, freertos_plus_tcp, rtems) define the SAME symbols and
# must NOT be compiled or you get duplicate-symbol link errors.

set(CLIENT Micro-XRCE-DDS-Client/src/c)
set(CDR    Micro-CDR/src/c)

set(SRCS
    # ---- Micro-CDR ----
    ${CDR}/common.c
    ${CDR}/types/array.c
    ${CDR}/types/basic.c
    ${CDR}/types/sequence.c
    ${CDR}/types/string.c

    # ---- Client core ----
    ${CLIENT}/core/log/log.c
    ${CLIENT}/core/serialization/xrce_header.c
    ${CLIENT}/core/serialization/xrce_subheader.c
    ${CLIENT}/core/serialization/xrce_types.c
    ${CLIENT}/core/session/common_create_entities.c
    ${CLIENT}/core/session/create_entities_bin.c
    ${CLIENT}/core/session/create_entities_ref.c
    ${CLIENT}/core/session/create_entities_xml.c
    ${CLIENT}/core/session/object_id.c
    ${CLIENT}/core/session/read_access.c
    ${CLIENT}/core/session/session_info.c
    ${CLIENT}/core/session/session.c
    ${CLIENT}/core/session/submessage.c
    ${CLIENT}/core/session/write_access.c
    ${CLIENT}/core/session/stream/input_best_effort_stream.c
    ${CLIENT}/core/session/stream/input_reliable_stream.c
    ${CLIENT}/core/session/stream/output_best_effort_stream.c
    ${CLIENT}/core/session/stream/output_reliable_stream.c
    ${CLIENT}/core/session/stream/seq_num.c
    ${CLIENT}/core/session/stream/stream_id.c
    ${CLIENT}/core/session/stream/stream_storage.c

    # ---- Client util ----
    ${CLIENT}/util/time.c

    # ---- Client UDP transport (NOPOLL variant ONLY) ----
    ${CLIENT}/profile/transport/ip/ip_posix.c
    ${CLIENT}/profile/transport/ip/udp/udp_transport.c
    ${CLIENT}/profile/transport/ip/udp/udp_transport_posix_nopoll.c
)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS
        "Micro-XRCE-DDS-Client/include"
        "Micro-CDR/include"
    REQUIRES
        lwip          # sockets, getaddrinfo, arpa/inet.h
)

# The client/microcdr sources use relative "" includes for their internal
# headers, which resolve from each .c file's own directory — no extra include
# dirs needed. Silence third-party warnings so they don't drown the build.
target_compile_options(${COMPONENT_LIB} PRIVATE -w)
