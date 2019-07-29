#define sensor1 35
#define sensor2 32
#define sensor3 27
#define sensor4 19
#define sensor5 18
#define sensor6 4

/* Firebase Credential*/
#include "FirebaseESP32.h"
#define FIREBASE_HOST "fiil with your Firebase Host" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "fill with your Firebase Auth"
FirebaseData firebaseData;

/* Wifi Initial Configurator*/
#include <WiFi.h>
#define WIFI_SSID "JaringanPentest"
#define WIFI_PASSWORD "123pastibisa"

/* Firebase Address */
String lokasiPath = "/location";
String spotPath = "/spot";
/* Value Status */
String valueSpot[] = {"Tersedia", "Terisi"};

/* Time Area */
unsigned long tm = 0;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (millis() > tm + 200) {
    //    RunSensor(spotInt);
    tm = millis();

    if (digitalRead(sensor1))
      RunSensor("Tersedia", 1);
    else
      RunSensor("Terisi", 1);

    if (digitalRead(sensor2))
      RunSensor("Tersedia", 2);
    else
      RunSensor("Terisi", 2);

    if (digitalRead(sensor3))
      RunSensor("Tersedia", 3);
    else
      RunSensor("Terisi", 3);

    if (digitalRead(sensor4))
      RunSensor("Tersedia", 4);
    else
      RunSensor("Terisi", 4);

    if (digitalRead(sensor5))
      RunSensor("Tersedia", 5);
    else
      RunSensor("Terisi", 5);

    if (digitalRead(sensor6))
      RunSensor("Tersedia", 6);
    else
      RunSensor("Terisi", 6);
  }
}

void RunSensor(String value, int name) {
  String pathSpot = lokasiPath;
  pathSpot       += spotPath;
  pathSpot       += String(name);

  String statusPath = pathSpot + "/status";
  boolean seenStatusValue = Firebase.setString(firebaseData
                            , statusPath
                            , value);
  if (seenStatusValue)
    Serial.println("[Terkirim] : " + statusPath + " : " + value);

  String namePath = pathSpot + "/name";
  String nameValue = "spot" + String(name);
  boolean seenNameValue = Firebase.setString(firebaseData
                          , namePath
                          , nameValue);
  if (seenNameValue)
    Serial.println("[Terkirim] : " + namePath + " : " + nameValue);
}
