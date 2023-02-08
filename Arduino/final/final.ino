#include <Arduino.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>


#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
//MQ135 mq135_sensor = MQ135(PIN_MQ135);

#define FIREBASE_HOST "https://fire-warning-9e33c-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "UGn2I5JwvyDKusF8HbEvKm328qZbcKzdmEcoZxTs"
#define WIFI_SSID "ITZONE"
#define WIFI_PASSWORD "12345678"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
int flame_sensor = 4;
int smoke_sensor = A0;
//int flame_sensor_read = HIGH;
int temp_smoke_sensor;
int flame_sensor_read;                     

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(flame_sensor,INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin();
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
  //==========FLAME_SENSOR==========
  flame_sensor_read = digitalRead(flame_sensor);
  Firebase.setInt(firebaseData,"/FLAME_STATUS", flame_sensor_read); //set value
  Serial.printf("FLAME Status: %d\n",flame_sensor_read);
  

  //=======DHT11_TEMP-HUM_SENSOR========
  float h = dht.readHumidity(); //read Humidity
  float t = dht.readTemperature(); //read Temperature
   if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  Firebase.setDouble(firebaseData,"/Temperature", t);         //set value
  Firebase.setDouble(firebaseData,"/Humidity", h);            //set value
  Serial.printf("Temperature: %.2f\n",t);
  Serial.printf("Humidity: %.2f\n",h);
  delay(500);
 
  temp_smoke_sensor = analogRead(smoke_sensor);
  Serial.printf("GAS value: %d\n",temp_smoke_sensor);
  Firebase.setDouble(firebaseData,"/GAS", temp_smoke_sensor);

  int fireStatus= -1;

  if(flame_sensor_read==0)
      fireStatus = 3;
    else if(temp_smoke_sensor>=65)
      fireStatus = 2;
    else if(t>=28)
      fireStatus = 1;
    else
      fireStatus = 0;
  Firebase.setInt(firebaseData, "/WARNING",fireStatus);
   
}
