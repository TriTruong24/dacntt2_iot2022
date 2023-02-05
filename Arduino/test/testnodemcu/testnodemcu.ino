#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "https://fire-warning-2022-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "0CE7jZk6kELpEr6uuFFqfaX8o7Lxv2By4vXQ7jzf"
#define WIFI_SSID "FPT Telecom"
#define WIFI_PASSWORD "He!!01234"
#define LED 2

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("https://fire-warning-2022-default-rtdb.firebaseio.com/LEDStatus",1);
}

void loop() {
  if(Firebase.getInt("https://fire-warning-2022-default-rtdb.firebaseio.com/LEDStatus"))
  {
    digitalWrite(LED,HIGH);
  }
    else
    {
      digitalWrite(LED,LOW);
    }
delay(1000);
}

