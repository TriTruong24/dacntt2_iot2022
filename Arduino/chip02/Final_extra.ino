
#include <stdio.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "https://fire-warning-9e33c-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "UGn2I5JwvyDKusF8HbEvKm328qZbcKzdmEcoZxTs"
#define WIFI_SSID "P301"
#define WIFI_PASSWORD "P301@789"


//Define FirebaseESP8266 data object
FirebaseData firebaseData;
int ledGreen = 2;
int ledBlue = 4;
int ledPurpule = 5;  
int flame_detected;                     
              
void setup()
{

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledPurpule, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledPurpule, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 500 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
}

void loop()
{
  
  int fireStatus = -1,temperature,ppm,flame_detected;
  if(Firebase.getInt(firebaseData, "/WARNING"))
      fireStatus = firebaseData.intData();
  if(Firebase.getInt(firebaseData, "/Temperature"))
      temperature = firebaseData.intData();
  if(Firebase.getInt(firebaseData, "/GAS"))
      ppm = firebaseData.intData();
  if(Firebase.getInt(firebaseData, "/FLAME_STATUS"))
      flame_detected = firebaseData.intData();
    Serial.printf("value fireStatus: %d\n",fireStatus);
    Serial.printf("value temperature: %d\n",temperature);
    Serial.printf("value ppm: %d\n",ppm);
    Serial.printf("value flame_detected: %d\n",flame_detected);

//if(flame_detected==0)
//    fireStatus = 3;
//  else if(temperature>30)
//    fireStatus = 2;
//  else if(ppm>=50)
//    fireStatus = 1;
//    else 
//      fireStatus = 0;
switch (fireStatus){
    case 0:
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledBlue, LOW);
          digitalWrite(ledPurpule, LOW);
          Serial.print("Case 0");
          break;
  
      case 1:
          digitalWrite(ledGreen, HIGH);
          digitalWrite(ledBlue, LOW);
          digitalWrite(ledPurpule, LOW);
          Serial.print("Case 1");
          break;
      case 2:
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledBlue, HIGH);
          digitalWrite(ledPurpule, LOW);
          Serial.print("Case 2");
          break;
      case 3:
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledBlue, LOW);
          digitalWrite(ledPurpule, HIGH);
          Serial.print("Case 3\n");
          break;
  }      
}
