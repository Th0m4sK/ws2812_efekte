#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_NeoPixel.h>
#include <secret.h>
#include <ws2812_obj.h>

const char* ssid = STASSID;
const char* password = STAPSK;
const char* hostname = STAHOST;


#define LED_PIN D4
#define Sensor1 D7
#define Sensor2 D6
#define Sensor3 D5
#define Sensor4 D1
#define Gate1 D3
#define Gate2 D0
#define LED_COUNT 7 //34 //16


ws2812_obj LED_Test1( 1,6);
ws2812_obj LED_Test2(4,6);
ws2812_obj LED_Tor_Links(0,4);
ws2812_obj LED_Tor_Rechts(4,9);
ws2812_obj LED_Cam1_OnOff(10,17);
ws2812_obj LED_Cam2_OnOff(18,25);
ws2812_obj LED_Key(26,33);
struct LED_STATUS
{
  
};

uint32_t LED_Backup[LED_COUNT];
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// setup() function -- runs once at startup --------------------------------





void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Start");

   WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setHostname(hostname);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.clear();
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255);


  pinMode(Sensor1,INPUT);
  pinMode(Sensor2,INPUT);
  pinMode(Sensor3,INPUT);
  pinMode(Sensor4,INPUT);
  LED_Test1.setStatus(strip,LED_Backup,SETCOLOR,0x00,0x00,0);
  LED_Test2.setStatus(strip,LED_Backup,SETCOLOR,0x00,0x00,0);
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
 ArduinoOTA.handle();

if (!digitalRead(Sensor1)){
 
 Serial.println("Sensor1 HIGH");
}

if (!digitalRead(Sensor2)){
 
 Serial.println("Sensor2 HIGH");
}
if (!digitalRead(Sensor3)){
 
 Serial.println("Sensor3 HIGH");
}
if (!digitalRead(Sensor4)){
 
 Serial.println("Sensor4 HIGH");
}
LED_Test1.setStatus(strip,LED_Backup,COLORSWITCH,strip.Color(0,0,50),strip.Color(50,00,0),500);


 

  //LED_Test.colorWipe(strip,strip.Color(0,255,0),backward ,500);
 strip.show();
 
}


