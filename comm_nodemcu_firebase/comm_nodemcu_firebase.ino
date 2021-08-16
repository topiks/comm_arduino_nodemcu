#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
                          
#define FIREBASE_HOST "socmaggot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zwPZeHZ6Bk0FkdDYLNwnfOi4v1NgZc9IW5wTiU7P"
#define WIFI_SSID "BME Enjoyy"
#define WIFI_PASSWORD "viktorie59"
 
// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;
int databaru;
bool fan;

void setup() {

  Serial.begin(115200);                                  
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
  delay(1000);
}

void loop() { 

// Write

Firebase.setInt(firebaseData, "/data", val) ;
val++;

//if (Firebase.getInt(firebaseData, "/data")) {                         
//    if (firebaseData.dataType() == "int") {                          
//      databaru = firebaseData.intData();
//      Serial.println(databaru);
//      delay(500);
//    }
//  }

if (Firebase.getBool(firebaseData, "/kandang1/fan")) {                         
    if (firebaseData.dataType() == "boolean") {                         
      fan = firebaseData.boolData();
      Serial.println(fan);
      delay(500);
    }
  }
else {
    Serial.println(firebaseData.errorReason());
  }
}
