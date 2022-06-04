#include <Arduino.h>
#include "HX711.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
extern String HTML;

const int LOADCELL_DOUT_PIN = 23;
const int LOADCELL_SCK_PIN = 19;
float calibration_factor = -35130; 
float reading;




const char* ssid = "Lowi7DBD";
const char* password = "RDBTQ84TNCJ2AK";

String lecturaSensor();
AsyncWebServer server(80);

HX711 dispositivo;

String lecturaSensor() {
  if (dispositivo.is_ready()) {
    reading = dispositivo.get_units(5);
    Serial.print("Kilos:");
    Serial.println(String(reading));
    return String(reading);
  } else {
    return " ";
  }

}




void setup() {
  Serial.begin(115200);
  dispositivo.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  dispositivo.tare();
  dispositivo.set_scale(calibration_factor);

  
  
  
 // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
   // Connect to Wi-Fi
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
   // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
 

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/fuerza", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", lecturaSensor().c_str());
  });

  
  server.begin();

  }



void loop() {
  
  

}