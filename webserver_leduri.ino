#include <WiFi.h>
#include <WebServer.h>
// Date Wi-Fi - pune aici SSID-ul și parola rețelei tale
const char* ssid     = "Maita";
const char* password = "parooola";
// Pini pentru LED-uri
const int LED1_PIN = 22;   // GPIO2
const int LED2_PIN = 23;   // GPIO4
// Server web pe portul 80
WebServer server(80);
// Pagina HTML simplă pentru test (opțional)
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>m     
<html>
<head>
  <meta charset="utf-8">
  <title>Control LED-uri ESP32</title>
</head>
<body>
  <h1>Control LED-uri ESP32</h1>
  <p>LED1:
    <a href="/led1/on"><button>ON</button></a>
    <a href="/led1/off"><button>OFF</button></a>
  </p>
  <p>LED2:
    <a href="/led2/on"><button>ON</button></a>
    <a href="/led2/off"><button>OFF</button></a>
  </p>
</body>
</html>
)rawliteral";
// Funcții handler
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}
void handleLED1On() {
  digitalWrite(LED1_PIN, HIGH);
  server.send(200, "text/plain", "LED1 ON");
}
void handleLED1Off() {
  digitalWrite(LED1_PIN, LOW);
  server.send(200, "text/plain", "LED1 OFF");
}
void handleLED2On() {
  digitalWrite(LED2_PIN, HIGH);
  server.send(200, "text/plain", "LED2 ON");
}
void handleLED2Off() {
  digitalWrite(LED2_PIN, LOW);
  server.send(200, "text/plain", "LED2 OFF");
}
void handleNotFound() {
  String message = "Not found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\n";
  server.send(404, "text/plain", message);
}
void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  // Conectare la Wi-Fi
  Serial.print("Conectare la ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectat");
  Serial.print("IP ESP32: ");
  Serial.println(WiFi.localIP());
  // Setare rute
  server.on("/", handleRoot);
  server.on("/led1/on", handleLED1On);
  server.on("/led1/off", handleLED1Off);
  server.on("/led2/on", handleLED2On);
  server.on("/led2/off", handleLED2Off);
  server.onNotFound(handleNotFound);
  // Pornire server
  server.begin();
  Serial.println("Server web pornit");
}
void loop() {
  server.handleClient();
}