#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(5,6);
String data;
int status_comm = 0;
int data1, data2, data3;
int larva, sampah, fan;

void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
s.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}

void loop() { // run over and over
 

communicate();
}

void communicate()
{
   Serial.print("larva ");
   Serial.print(larva);
   Serial.print(" | sampah ");
   Serial.print(sampah);
   Serial.print(" | fan ");
   Serial.print(fan);
   Serial.print(" | status comm ");
   Serial.println(status_comm);
  switch(status_comm)
{
  case 0:
      kirimdatajson();
      delay(2000);
      status_comm = 1;
  break;

  case 1:
  {
    DynamicJsonBuffer jsonBuffer;
  
          JsonObject& root = jsonBuffer.parseObject(Serial);
          if (root == JsonObject::invalid())
            return;
         
          larva = root["larva"];
          sampah = root["sampah"];
          fan = root["fan"];
          data3=root["end"];
          status_comm = 0;   
  }
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
DynamicJsonBuffer jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["suhu1"] = 10;
  root["suhu2"] = 8;
  root["lembap1"] = 10;
  root["lembap2"] = 8;
  root["end"] = 99;
  
  root.printTo(s);
  
}

void terimadata()
{
  if (Serial.available()) {
  Serial.write(Serial.read());
}
}
