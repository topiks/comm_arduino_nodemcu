#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "socmaggot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zwPZeHZ6Bk0FkdDYLNwnfOi4v1NgZc9IW5wTiU7P"
#define WIFI_SSID "BME Enjoyy"
#define WIFI_PASSWORD "viktorie59"

FirebaseData firebaseData;

String str;
char dataterima[100];

int status_comm = 0;
int suhu1, suhu2, kelembapan1, kelembapan2;
int data1, data2, data3;

// firebase testing
int val = 99;

// controlling
bool fan;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  // connect wifi
  Serial.println("Serial communication started\n\n");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  delay(2000);
}
void loop()
{

  // write to database
//  Firebase.setInt(firebaseData, "/data", val) ;
//  val++;
//  delay(1000);

readfromdb();
communicate();
}

void pushtodb()
{
    Firebase.setInt(firebaseData, "/data", val);
}

void readfromdb()
{
    if (Firebase.getBool(firebaseData, "/kandang1/fan")) {                         
    if (firebaseData.dataType() == "boolean") {                         
      fan = firebaseData.boolData();
//      Serial.println(fan);
//      delay(500);
    }
  }
else {
    Serial.println(firebaseData.errorReason());
  }
}

void communicate()
{
    val++;
  Serial.print("suhu1 ");
  Serial.print(suhu1);
  Serial.print(" | suhu2 ");
  Serial.print(suhu2);
  Serial.print(" | kelembapan1 ");
  Serial.print(kelembapan1);
  Serial.print(" | kelembapan2 ");
  Serial.print(kelembapan2);
  Serial.print(" | fan ");
  Serial.print(fan);
  Serial.print(" | status comm ");
  Serial.println(status_comm);
  switch (status_comm)
  {
    case 0:
      {
        DynamicJsonBuffer jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(Serial);

        if (root == JsonObject::invalid())
          return;

        suhu1 = root["suhu1"];
        suhu2 = root["suhu2"];
        kelembapan1 = root["lembap1"];
        kelembapan2 = root["lembap2"];
        data3 = root["end"];
//        status_comm = 1;
 
        
//        delay(100);
//        if (data3 == 99)
//        {
          status_comm = 1;
//        }
//Serial.print("ini data fan pertama");
//      Serial.println(fan);
      }
      
//      status_comm = 1;
      break;

    case 1:
//       Serial.print("ini data fan ");
//      Serial.println(fan);
      kirimdatajson();
delay(2000);
//  if (Serial.available())
      status_comm = 0;
      break;

  }
}


void kirimdatajson()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["larva"] = 1;
  root["sampah"] = 3;
    root["fan"] = fan;
  root["end"] = 99;
  root.printTo(Serial1);
  
}

void kirimdata()
{
  Serial1.println(str);
  delay(1000);
}

void terimadata()
{

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Serial);
  if (root == JsonObject::invalid())
    return;

  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.print("Data 1 ");
  Serial.println("");
  data1 = root["suhu1"];
  Serial.print(data1);
  Serial.print("   Data 2 ");
  data2 = root["suhu2"];
  Serial.print(data2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  data3 = root["end"];
}
