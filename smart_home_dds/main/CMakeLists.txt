# Phase A (bench test) needs only these sources + the IDF driver/wifi/nvs components.
#
# For Phase B (XRCE client), after you have generated smart_home.{h,c} with
# microxrceddsgen and vendored the client under ../components/, ADD them here:
#
#   set(SRCS "smart_home_client.c" "wifi_sta.c" "smart_home.c")
#   ... PRIV_REQUIRES ... microxrcedds_client
#
idf_component_register(
    SRCS
        "smart_home_client.c"
        "wifi_sta.c"
        "smart_home.c"        # generated: microxrceddsgen smart_home.idl
    INCLUDE_DIRS "."
    REQUIRES
        driver        # LEDC / GPIO
        esp_wifi
        nvs_flash
        esp_event
        esp_netif
        eprosima      # Micro-XRCE-DDS-Client + Micro-CDR (components/eprosima)
)
