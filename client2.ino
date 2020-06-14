#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WLAN_SSID       "*****"  //replace with your wifi SSID
#define WLAN_PASS       "*****"  //replace with your wifi password
#define AIO_SERVER      "*****" //IP address of RPi
#define AIO_SERVERPORT  1883    // use 8883 for SSL
#define AIO_USERNAME    ""       //donot make any changes
#define AIO_KEY         ""       //donot make any changes

WiFiClient client;



Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish Soilmoisture = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/MOISTURESENSOR");

uint32_t delayMS;
void MQTT_connect();
void setup() {
  Serial.begin(115200);

  delay(10);
  pinMode(A0,INPUT);
  Serial.println(F("Adafruit MQTT demo"));
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  
}

uint32_t x = 0;

void loop() {
   MQTT_connect();
    delay(10);
 MOISTURESENSOR = analogRead(A0);
 delay(10);
   if (!  Soilmoisture.publish(MOISTURESENSOR)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}
 
void MQTT_connect()
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
     
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
