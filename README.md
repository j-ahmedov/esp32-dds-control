# Smart-Home Node over DDS — ESP32-S3

An ESP32-S3 drives **two dimmable LEDs and a servo**, controlled and monitored over a real
**DDS** dataspace. The device runs **eProsima Micro XRCE-DDS**; a bridge agent puts it on
DDS **domain 0**, where both a local web dashboard **and RTI Connext** (a different DDS
vendor) can command it and read its telemetry — all from one shared IDL contract.

> Full technical report (architecture, code, circuit diagrams, engineering notes):
> **[`docs/ESP32-DDS-SmartHome-Report.pdf`](docs/ESP32-DDS-SmartHome-Report.pdf)**

---

## What it does
- **LED1 / LED2** — PWM brightness 0–255 (LEDC)
- **Servo** — angle 0–180° (MCPWM)
- **Commands** flow: controller → agent → ESP32 → hardware
- **Telemetry** flows back: ESP32 publishes `device_state` → controller displays live values
- **Cross-vendor**: RTI Connext interoperates with the eProsima device, unchanged

## Architecture
```
 Controller (Mac)                         ESP32-S3 device
 ┌──────────────────┐   RTPS, domain 0   ┌──────────────────┐
 │ Web dashboard     │◄──────────────────►│                  │
 │  (eProsima tools) │                    │ Micro XRCE-DDS   │─► LED1 (GPIO11)
 │  — or —           │   Micro XRCE-DDS   │ client (firmware)│─► LED2 (GPIO12)
 │ RTI Connext       │◄── Agent (native)◄─┤                  │─► Servo (GPIO9)
 └──────────────────┘      Wi-Fi/UDP:8888 └──────────────────┘
```
The **Agent** is eProsima's Micro-XRCE-DDS Agent (Fast DDS backend), run **natively** on
the Mac. It bridges the tiny device onto the DDS network so any DDS participant can talk to it.

## Repository layout
```
smart_home_dds/     ESP-IDF firmware (idf.py) + host_tools/ + vendored eProsima client
rti_app/            RTI Connext C++11 publisher/subscriber (cross-vendor demo)
dashboard/          Web control panel: run.sh + server.py + index.html
docs/               Full PDF report
smart_home.idl      (in each project) the shared type contract — single source of truth
```

## Hardware / wiring
| Signal | Pin | Wiring |
|--------|-----|--------|
| LED1 | GPIO 11 | pin → 220 Ω → LED long leg; short leg → GND |
| LED2 | GPIO 12 | pin → 220 Ω → LED long leg; short leg → GND |
| Servo signal | GPIO 9 | → servo orange wire |
| Servo power | 5 V | servo red → **external 5 V** (a servo won't run on 3.3 V) |
| Common ground | GND | servo brown + LED cathodes + ext-5 V GND all tied to ESP32 GND |

> ⚠️ The servo's power ground **must** be shared with the ESP32 ground. Wire components
> directly to the pins — loose breadboard contacts were the #1 source of "not working".

## Prerequisites (one-time)
- **ESP-IDF v5.4** — activate with `source ~/esp/idf_env.sh`
- **Native Micro-XRCE-DDS Agent** — built at `~/esp/Micro-XRCE-DDS-Agent/build/MicroXRCEAgent`
  (run natively, not in Docker — Docker's UDP forwarding to the LAN is unreliable on macOS)
- **Host tools libs** at `~/esp/eprosima-host` (for the dashboard/CLI publishers)
- **RTI Connext 7.7.0** — only for the RTI demo
- Full setup steps: see Appendix A of the PDF report.

## Run it (everyday — web dashboard)
```bash
cd ~/Documents/PlatformIO/Projects/esp32_dds_control
bash dashboard/run.sh          # starts the native agent + opens the browser
```
Then **press `RST`** on the board and open **http://localhost:8080**.
Move a slider/button → the LED/servo responds → the live panel and Activity Log show the
device reporting its state back. Green dot = device online.

### If Wi-Fi or the Mac's IP changed (reflash)
The device needs the Mac's current IP baked in. Check and update, then reflash:
```bash
ipconfig getifaddr en0     # the Mac's IP — must equal AGENT_IP in the firmware
# edit WIFI_SSID / WIFI_PASS / AGENT_IP in smart_home_dds/main/smart_home_client.c
source ~/esp/idf_env.sh
cd smart_home_dds && idf.py build && idf.py -p /dev/cu.usbmodem1101 flash
# press RST
```

## Cross-vendor demo (RTI Connext)
```bash
# native agent must be running (dashboard's run.sh starts it); press RST on the board
export NDDSHOME=/Applications/rti_connext_dds-7.7.0
export PATH=$NDDSHOME/bin:$PATH
export DYLD_LIBRARY_PATH=$NDDSHOME/lib/arm64Darwin23clang16.0
cd rti_app
rtiddsspy -domainId 0 -transport 1     # RTI discovers the device's topics
./rti_publisher led 1 200              # RTI commands the LED
./rti_publisher servo 90               # ...and the servo
./rti_subscriber                       # RTI reads device_state back
```

## Troubleshooting
| Symptom | Fix |
|---------|-----|
| Dashboard dot **red / offline** | Agent running? Then **press `RST`** (board reconnects). Then check Wi-Fi/`AGENT_IP`. |
| Board won't connect after network change | Update `WIFI_*` / `AGENT_IP`, rebuild + flash, `RST`. |
| A part doesn't respond but telemetry shows the value | It's **wiring**, not code — re-seat directly to the pin. |
| Servo won't move | Needs solid **5 V** + shared ground; won't run on 3.3 V. |
| RTI: `shared memory` errors | Use `rtiddsspy -domainId 0 -transport 1`; the RTI apps already force UDPv4. |

## Technology
ESP32-S3 · ESP-IDF v5.4 · eProsima Micro XRCE-DDS (client v3.0.1 + Micro-CDR) ·
Micro-XRCE-DDS Agent (Fast DDS) · RTI Connext 7.7.0 · one shared OMG IDL contract.
