# smart_home_dds — native ESP-IDF project

DDS firmware for the ESP32-S3, built with **`idf.py` (NOT PlatformIO)**. This lives
alongside the Arduino baseline (`../src/main.cpp`), which stays as the working fallback.

See `../some_code/DDS_BRINGUP_PLAN.md` for the full phased plan and interop checklist.

## Phase A — bench test (no network, default)
`SMART_HOME_BENCH_TEST` is `1` in `main/smart_home_client.c`, so the firmware just
exercises the hardware. No XRCE library or generated types are required.

```
. $IDF_PATH/export.sh
idf.py set-target esp32s3
idf.py build flash monitor      # S3 native USB usually /dev/cu.usbmodem*
```
**Expect:** LED1 (GPIO 11) fades up as LED2 (GPIO 12) fades down, then the servo
(GPIO 13) sweeps 0→180→0, looping forever.

## Phase B — XRCE client  (DONE: builds clean)
Already wired and compiling:
- eProsima client v3.0.1 + Micro-CDR v2.0.2 vendored at `components/eprosima/`
  (UDP + POSIX_NOPOLL, hand-authored config.h — see `components/README.md`).
- `main/smart_home.{h,c}` generated from the IDL.
- `SMART_HOME_BENCH_TEST` is `0`; `main/CMakeLists.txt` requires `eprosima`.

**Before flashing:** set real `WIFI_SSID`/`WIFI_PASS` and `AGENT_IP` (your Mac's LAN IP)
at the top of `main/smart_home_client.c`.

**Bring-up:**
1. Start the agent on the Mac:
   ```
   docker run -it --rm --net=host eprosima/micro-xrce-dds-agent:latest udp4 -p 8888 -v6
   ```
2. Flash + monitor:
   ```
   source ~/esp/idf_env.sh
   idf.py -p /dev/cu.usbmodem* flash monitor
   ```
3. **Expect:** firmware logs `entities created, listening...`; agent (`-v6`) logs
   `client connected` and the participant/topic/subscriber/datareader creations.

To regenerate types after editing the IDL:
`~/esp/Micro-XRCE-DDS-Gen/scripts/microxrceddsgen -replace -d main smart_home.idl`

> Build assumes 2 MB flash (app partition 25% free). If it grows, bump
> `CONFIG_ESPTOOLPY_FLASHSIZE` (the DevKitC-1 likely has 8 MB).

## Layout
```
smart_home_dds/
├── CMakeLists.txt            project
├── sdkconfig.defaults        target + stack + baud
├── smart_home.idl            type contract (shared with RTI)
├── components/               (Phase B) vendored eProsima client
└── main/
    ├── CMakeLists.txt
    ├── smart_home_client.c   firmware (bench switch at top)
    ├── wifi_sta.c            wifi_init_sta() implementation
    └── wifi_sta.h
```
