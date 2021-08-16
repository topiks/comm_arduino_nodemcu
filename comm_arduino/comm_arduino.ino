#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(5,6);
String data;
int status_comm = 0;
int data1, data2, data3;

void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
s.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}

void loop() { // run over and over
data =String("suhu = 10, lempap = 20 cok");

//kirimdatajson();
//terimadata();
//Serial.println(status_comm);

switch(status_comm)
{
  case 0:
      kirimdatajson();
       if (Serial.available())
          status_comm = 1;
//        Serial.write(Serial.read());
  break;

  case 1:
//    Serial.write(Serial.read());

StaticJsonBuffer<1000> jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(Serial);
          if (root == JsonObject::invalid())
            return;
         
          Serial.println("JSON received and parsed");
          root.prettyPrintTo(Serial);
          Serial.print("Data 1 ");
          Serial.println("");
          data1=root["suhu1"];
          Serial.print(data1);
          Serial.print("   Data 2 ");
          data2=root["suhu2"];
          Serial.print(data2);
          Serial.println("");
          Serial.println("---------------------xxxxx--------------------");
          data3=root["end"];
          delay(100);
            if(data3 == 99)
            {
                status_comm = 0;   
            }
//    status_comm = 0;
  break;

  case 2:
  break;
}

}

void kirimdata()
{
  s.println(data);
  delay(1000);
}

void kirimdatajson()
{
StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["suhu1"] = 100;
  root["suhu2"] = 200;
  root["end"] = 99;
  
  root.printTo(s);
  delay(1000);
}



void terimadata()
{
  if (Serial.available()) {
  Serial.write(Serial.read());
}
}
