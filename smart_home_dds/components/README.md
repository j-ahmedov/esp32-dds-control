# components/ — vendored libraries (Phase B only)

Phase A (bench test) needs nothing here.

For Phase B, put the eProsima client here so ESP-IDF picks it up as a component:

## Option 1 — official client (more control)
Clone Micro-XRCE-DDS-Client (v3.x) and Micro-CDR into this folder, each with an
ESP-IDF `CMakeLists.txt` exposing `microxrcedds_client` / `microcdr`. Configure
the UDP transport for ESP-IDF (lwIP sockets).

```
git clone -b v3.0.1 https://github.com/eProsima/Micro-XRCE-DDS-Client.git
git clone https://github.com/eProsima/Micro-CDR.git
```

## Option 2 — community starter (faster bring-up)
```
git clone https://github.com/raveious/esp-xrce-dds-client.git
```
Already wired as an ESP-IDF component; start here if the official integration fights you.

## Then
1. Generate type support from the IDL (one dir up):
   `microxrceddsgen ../smart_home.idl` → copy `smart_home.{h,c}` into `../main/`.
2. Flip `SMART_HOME_BENCH_TEST` to `0` in `main/smart_home_client.c`.
3. Add `smart_home.c` + the client to `main/CMakeLists.txt` (see comments there).
4. **DIFF** the `uxr_*` calls against the client's
   `examples/SubscribeHelloWorldClient/main.c` — API names drift across versions.
