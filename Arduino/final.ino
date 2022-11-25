//#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "MQ135.h"

#define PIN_MQ135 A0

//prosess sensor temperture
const int DHTPIN = D1;
const int DHTTYPE = DHT11;

DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135_sensor = MQ135(PIN_MQ135);

//#define FIREBASE_HOST "https://myhome-5f49a.firebaseio.com/"
//#define FIREBASE_AUTH "TanLdZr49UWZ56BodrgGq3W2sNiDCVYQOMJcZYNG"
#define WIFI_SSID "VIETTEL-TBL"
#define WIFI_PASSWORD "khongcomatkhau123"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
int flame_sensor = D2;
int flying_Fish = A0;
int flame_detected = HIGH;                     

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
//
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
//  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
//  Firebase.setwriteSizeLimit(firebaseData, "tiny");

}

//void loop()
//{
//   //==========FLAME_SENSOR==========
//  flame_detected = digitalRead(flame_sensor);
//  Firebase.setInt(firebaseData,"/HOUSE_STATUS/FLAME_DETECTED", flame_detected); //set value
//  Serial.printf("\t FLAME Status: %d\n",flame_detected);
//  //-------endflame--------
//
//  //=======DHT11_TEMP-HUM_SENSOR========
//  float h = dht.readHumidity(); //read Humidity
//  float t = dht.readTemperature(); //read Temperature
//  Firebase.setDouble(firebaseData,"/HOUSE_STATUS/temp", t);         //set value
//  Firebase.setDouble(firebaseData,"/HOUSE_STATUS/hum", h);            //set value
//  Serial.printf("Temperature: %.2f\n",t);
//  Serial.printf("Humidity: %.2f\n",h);
//  delay(500);
//   
//  //==========FLYING_FISH==========
//  float PPM = mq135_sensor.getCorrectedPPM(t,h);
//  Serial.printf("\t GAS value: %.2f\n",PPM);
//  Firebase.setDouble(firebaseData,"/HOUSE_STATUS/PPM", PPM);
//
//  //-------endflying_fish--------
//  int fireStatus= -1;
//
//  if(flame_detected==0)
//    fireStatus = 3;
//  else if(t>60)
//    fireStatus = 3;
//  else if(PPM>=30)
//    fireStatus = 3;
//  else if(PPM>=20&&PPM<30)
//    fireStatus = 2;
//  else if(t>=50&&t<=60)
//    fireStatus = 2;
//  else if(t>=40)
//    fireStatus = 1;
//  else
//    fireStatus = 0;
//Firebase.setInt(firebaseData, "/HOUSE_STATUS/WARNING",fireStatus);
//   
//}
