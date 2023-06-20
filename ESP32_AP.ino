#include <WiFi.h>
#include <esp_wifi.h>


// CONSTS
const char *ssid = "your-ap-name";
const char *password = "your-ap-password";
const uint8_t mac[] = { 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6 }; // your BSSID
const IPAddress host = IPAddress(192, 168, 1, 1); // your gateway

// HTTP SERVER
// delete if you not use, and LOOP FUNCTION both.
WiFiServer server(80);

// INIT FUNCTION
void setup() {
  WiFi.mode(WIFI_AP);
  // Modify MAC
  esp_err_t err = esp_wifi_set_mac(WIFI_IF_AP, &mac[0]);
  // Enable Wi-Fi AP
  WiFi.softAP(ssid, password, 1, 0, 1);
  WiFi.softAPConfig(host, host, IPAddress(255, 255, 255, 0));
  // Start HTTP Server
  server.begin();
}

// LOOP FUNCTION
void loop() {
  WiFiClient client = server.available();
  if (client && client.connected()) {
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    // the content of the HTTP response follows the header:
    client.print("MAC ADDRESS: ");
    client.println(WiFi.softAPmacAddress());

    // The HTTP response ends with another blank line:
    client.println();

    client.stop();
  }
}
