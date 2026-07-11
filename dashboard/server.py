#!/usr/bin/env python3
"""
Smart-Home DDS dashboard — local web control panel.

Bridges the browser to the DDS domain by reusing the already-built host tools:
  - commands  -> runs led_publisher / servo_publisher (publish to led_cmd/servo_cmd)
  - telemetry -> runs state_subscriber, parses device_state, exposes it at /state

Prereqs: the XRCE Agent must be running (Docker or native) and the ESP32 connected.
Usage:   python3 server.py           (then open http://localhost:8080)
Env:     AGENT_IP (default 127.0.0.1), AGENT_PORT (default 8888), PORT (default 8080)
"""
import http.server, socketserver, subprocess, threading, json, os, re, time, urllib.parse, collections

HERE       = os.path.dirname(os.path.abspath(__file__))
TOOLS      = os.path.join(HERE, "..", "smart_home_dds", "host_tools")
AGENT_IP   = os.environ.get("AGENT_IP", "127.0.0.1")
AGENT_PORT = os.environ.get("AGENT_PORT", "8888")
WEB_PORT   = int(os.environ.get("PORT", "8080"))

# latest device-reported state + freshness timestamp
state = {"led1": 0, "led2": 0, "servo": 90, "ts": 0.0}
_lock = threading.Lock()

# rolling activity log (both directions): sent commands + received state changes
LOG = collections.deque(maxlen=150)
def add_log(direction, text):   # direction: "send" | "recv"
    LOG.append({"t": time.strftime("%H:%M:%S"), "dir": direction, "text": text})

def tool(name):
    return os.path.join(TOOLS, name)

def publish_led(led_id, value):
    add_log("send", f"LED{led_id} → {value}")
    # repeat=2 for reliable delivery (a single sample can occasionally be missed)
    subprocess.run([tool("led_publisher"), AGENT_IP, AGENT_PORT, str(led_id), str(value), "2"],
                   timeout=8, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def publish_servo(angle):
    add_log("send", f"Servo → {angle}°")
    subprocess.run([tool("servo_publisher"), AGENT_IP, AGENT_PORT, str(angle), "2"],
                   timeout=8, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def state_reader():
    """Continuously run state_subscriber and parse its device_state lines."""
    pat = re.compile(r"LED1=(\d+)\s+LED2=(\d+)\s+servo=(\d+)")
    while True:
        try:
            p = subprocess.Popen([tool("state_subscriber"), AGENT_IP, AGENT_PORT],
                                 stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)
            for line in p.stdout:
                m = pat.search(line)
                if m:
                    l1, l2, sv = map(int, m.groups())
                    with _lock:
                        changed = (l1, l2, sv) != (state["led1"], state["led2"], state["servo"])
                        state["led1"], state["led2"], state["servo"] = l1, l2, sv
                        state["ts"] = time.time()
                    if changed:      # only log when the device's reported state actually changes
                        add_log("recv", f"device: LED1={l1} LED2={l2} servo={sv}°")
            p.wait()
        except Exception:
            pass
        time.sleep(1.0)   # restart if the subscriber exits

class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, *a):  # quiet
        pass

    def _send(self, code, body, ctype="application/json"):
        b = body.encode() if isinstance(body, str) else body
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(b)))
        self.end_headers()
        self.wfile.write(b)

    def do_GET(self):
        u = urllib.parse.urlparse(self.path)
        if u.path in ("/", "/index.html"):
            with open(os.path.join(HERE, "index.html"), "rb") as f:
                self._send(200, f.read(), "text/html; charset=utf-8")
        elif u.path == "/state":
            with _lock:
                fresh = (time.time() - state["ts"]) < 4.0 if state["ts"] else False
                self._send(200, json.dumps({**{k: state[k] for k in ("led1","led2","servo")},
                                            "connected": fresh}))
        elif u.path == "/log":
            self._send(200, json.dumps(list(LOG)[-60:]))   # most recent 60 entries
        else:
            self._send(404, "{}")

    def do_POST(self):
        u = urllib.parse.urlparse(self.path)
        q = urllib.parse.parse_qs(u.query)
        try:
            if u.path == "/led":
                led_id = int(q.get("id", ["1"])[0]); v = max(0, min(255, int(q.get("v", ["0"])[0])))
                publish_led(led_id, v); self._send(200, json.dumps({"ok": True}))
            elif u.path == "/servo":
                a = max(0, min(180, int(q.get("angle", ["90"])[0])))
                publish_servo(a); self._send(200, json.dumps({"ok": True}))
            else:
                self._send(404, "{}")
        except subprocess.TimeoutExpired:
            self._send(504, json.dumps({"ok": False, "err": "agent/device not reachable"}))
        except Exception as e:
            self._send(500, json.dumps({"ok": False, "err": str(e)}))

class ThreadingServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
    daemon_threads = True

if __name__ == "__main__":
    for t in ("led_publisher", "servo_publisher", "state_subscriber"):
        if not os.path.exists(tool(t)):
            print(f"!! missing host tool: {tool(t)}\n   build them: bash ../smart_home_dds/host_tools/build.sh")
    threading.Thread(target=state_reader, daemon=True).start()
    print(f"Smart-Home dashboard: http://localhost:{WEB_PORT}")
    print(f"  agent = {AGENT_IP}:{AGENT_PORT}   (must be running, board connected)")
    ThreadingServer(("", WEB_PORT), Handler).serve_forever()
