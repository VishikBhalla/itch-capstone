#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Set WiFi credentials
//#define WIFI_SSID "red-board"
#define WIFI_SSID "itch"
#define WIFI_PASS "capstone"

bool robotEnabled = true;
ESP8266WebServer server(80);

void handleIncomingCommand();

void setup() {
  // Setup serial port
  Serial.begin(9600);
  Serial1.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_POST, handleIncomingCommand);
  server.begin();
}

void loop() {
  if(Serial1.available()) {
    
  }
  
  server.handleClient();
}

void handleIncomingCommand() {
  if (!server.hasArg("plain")) { //Check if body received
    server.send(400, "text/plain", "Body not received");
    return;
  }

  String incoming = server.arg("plain");
  StaticJsonDocument<128> doc;

  DeserializationError error = deserializeJson(doc, incoming);

  if (error) {
    server.send(400, "text/plain", error.c_str());
    return;
  }

  if (strcmp(doc["name"], "enable") == 0) {
    robotEnabled = true;
    server.send(200, "text/plain", "robot enabled");
    return;
  }
  if (strcmp(doc["name"], "disable") == 0) {
    robotEnabled = false;
    doc["name"] = "stop";
  } else if (!robotEnabled) {
    server.send(409, "text/plain", "robot currently disabled");
    return;
  }

  Serial.print("Sending doc over with name: ");
  Serial.println((String) doc["name"]);
//  serializeJson(doc, Serial);
  serializeJson(doc, Serial1);
}
