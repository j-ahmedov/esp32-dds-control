// Hand-authored from config.h.in for the ESP-IDF build (no CMake configure step).
// Profiles: UDP transport only, POSIX_NOPOLL platform (lwIP BSD sockets, no poll()).
// Keep in sync with components/eprosima/CMakeLists.txt source selection.

#ifndef _UXR_CLIENT_CONFIG_H_
#define _UXR_CLIENT_CONFIG_H_

#define UXR_CLIENT_VERSION_MAJOR 3
#define UXR_CLIENT_VERSION_MINOR 0
#define UXR_CLIENT_VERSION_MICRO 1
#define UXR_CLIENT_VERSION_STR "3.0.1"

/* #undef UCLIENT_PROFILE_DISCOVERY */

#define UCLIENT_PROFILE_UDP
/* #undef UCLIENT_PROFILE_TCP */
/* #undef UCLIENT_PROFILE_CAN */
/* #undef UCLIENT_PROFILE_SERIAL */
/* #undef UCLIENT_PROFILE_CUSTOM_TRANSPORT */
/* #undef UCLIENT_PROFILE_MULTITHREAD */
/* #undef UCLIENT_PROFILE_SHARED_MEMORY */
/* #undef UCLIENT_PROFILE_STREAM_FRAMING */

/* #undef UCLIENT_PLATFORM_POSIX */
#define UCLIENT_PLATFORM_POSIX_NOPOLL
/* #undef UCLIENT_PLATFORM_WINDOWS */
/* #undef UCLIENT_PLATFORM_FREERTOS_PLUS_TCP */
/* #undef UCLIENT_PLATFORM_RTEMS_BSD_NET */
/* #undef UCLIENT_PLATFORM_ZEPHYR */

#define UXR_CONFIG_MAX_OUTPUT_BEST_EFFORT_STREAMS     1
#define UXR_CONFIG_MAX_OUTPUT_RELIABLE_STREAMS        1
#define UXR_CONFIG_MAX_INPUT_BEST_EFFORT_STREAMS      1
#define UXR_CONFIG_MAX_INPUT_RELIABLE_STREAMS         1

#define UXR_CONFIG_MAX_SESSION_CONNECTION_ATTEMPTS    10
#define UXR_CONFIG_MIN_SESSION_CONNECTION_INTERVAL    1000
#define UXR_CONFIG_MIN_HEARTBEAT_TIME_INTERVAL        100

#ifdef UCLIENT_PROFILE_UDP
#define UXR_CONFIG_UDP_TRANSPORT_MTU                  512
#endif

/* #undef UCLIENT_TWEAK_XRCE_WRITE_LIMIT */

/* #undef UCLIENT_HARD_LIVELINESS_CHECK */

// Version checks (mirrors the .in guard)
#if UXR_CLIENT_VERSION_MAJOR >= 4
#error config.h must be regenerated for client >= 4.x
#endif

#endif // _UXR_CLIENT_CONFIG_H_
