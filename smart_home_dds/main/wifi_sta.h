#pragma once

// Blocks until the station has an IP (or aborts after retries).
// Signature matches the `extern` declaration the firmware relies on.
void wifi_init_sta(const char *ssid, const char *pass);
