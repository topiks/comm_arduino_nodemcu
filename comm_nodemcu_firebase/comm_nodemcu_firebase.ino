
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

void setup() {

  Serial.begin(115200);                                   // Select the same baud rate if you want to see the datas on Serial Monitor

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
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
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() { 

// Write

if (Firebase.setInt(firebaseData, "/data", val)) {    // On successful Write operation, function returns 1  
               val++;
               delay(1000);
     }

else {        
    Serial.println(firebaseData.errorReason());
  }


// Read
if (Firebase.getInt(firebaseData, "/kandang1/suhu")) {                           // On successful Read operation, function returns 1  
    if (firebaseData.dataType() == "int") {                            // print read data if it is integer
      val = firebaseData.intData();
      Serial.println(val);
      Serial.println("\n Change value at firebase console to see changes here."); 
      delay(10000);
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
 
}
