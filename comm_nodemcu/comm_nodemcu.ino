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
int val = 0;

// controlling
bool fan1;
bool fan2;

bool larva1;
bool larva2;

bool sampah1;
bool sampah2;

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
pushtodb();
readfromdb();
communicate();
}

void pushtodb()
{
    Firebase.setInt(firebaseData, "/data", val);
    Firebase.setInt(firebaseData, "/kandang1/suhu", suhu1);
    Firebase.setInt(firebaseData, "/kandang2/suhu", suhu2);
    Firebase.setInt(firebaseData, "/kandang1/kelembapan", kelembapan1);
    Firebase.setInt(firebaseData, "/kandang2/kelembapan", kelembapan2);
    val++;
}

void readfromdb()
{
    // fan
    if (Firebase.getBool(firebaseData, "/kandang1/fan")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          fan1 = firebaseData.boolData();
        }
    }

    if (Firebase.getBool(firebaseData, "/kandang2/fan")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          fan2 = firebaseData.boolData();
        }
    }

    // larva
    if (Firebase.getBool(firebaseData, "/kandang1/larva")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          larva1 = firebaseData.boolData();
        }
    }

    if (Firebase.getBool(firebaseData, "/kandang2/larva")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          larva2 = firebaseData.boolData();
        }
    }

    // sampah
    if (Firebase.getBool(firebaseData, "/kandang1/sampah")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          sampah1 = firebaseData.boolData();
        }
    }

    if (Firebase.getBool(firebaseData, "/kandang2/sampah")) {                         
        if (firebaseData.dataType() == "boolean") {                         
          sampah2 = firebaseData.boolData();
        }
    }
else {
    Serial.println(firebaseData.errorReason());
  }
}

void communicate()
{
  Serial.print("suhu1 ");
  Serial.print(suhu1);
  Serial.print(" | suhu2 ");
  Serial.print(suhu2);
  Serial.print(" | kelembapan1 ");
  Serial.print(kelembapan1);
  Serial.print(" | kelembapan2 ");
  Serial.print(kelembapan2);
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
        status_comm = 1;
      }
      break;

    case 1:
      kirimdatajson();
      delay(2000);
      status_comm = 0;
      break;
  }
}


void kirimdatajson()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  if(larva1 == 1 && larva2 ==1)
    root["larva"] = 3;
  else if(larva1 == 1 && larva2 ==0)
    root["larva"] = 1;
  else if(larva1 == 0 && larva2 ==1)
    root["larva"] = 2;
  else
    root["larva"] = 0;

  if(sampah1 == 1 && sampah2 ==1)
    root["sampah"] = 3;
  else if(sampah1 == 1 && sampah2 ==0)
    root["sampah"] = 1;
  else if(sampah1 == 0 && sampah2 ==1)
    root["sampah"] = 2;
  else
    root["sampah"] = 0;

  if(fan1 == 1 && fan2 ==1)
    root["fan"] = 3;
  else if(fan1 == 1 && fan2 ==0)
    root["fan"] = 1;
  else if(fan1 == 0 && fan2 ==1)
    root["fan"] = 2;
  else
    root["fan"] = 0;
  
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
