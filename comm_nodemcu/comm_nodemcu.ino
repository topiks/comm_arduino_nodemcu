#include <SoftwareSerial.h>
#include <ArduinoJson.h>

String str;
char dataterima[100];

int status_comm = 0;
int data1, data2, data3;

void setup(){
Serial.begin(115200);
Serial1.begin(115200);
delay(2000);
}
void loop()
{
str =String("coming from ESP8266: ");
//Serial.println(status_comm);

switch(status_comm)
{
    case 0:
    {
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
                status_comm = 1;   
            }
    }
    break;   

    case 1:
//        Serial1.println(str);
       kirimdatajson();
        delay(1000);
        status_comm = 0;
    break;

    case 2:
    break;

    
}


//kirimdata();

//delay(1000);
}

void kirimdatajson()
{
    StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["suhu1"] = 100;
  root["suhu2"] = 200;
  root["end"] = 99;
  
  root.printTo(Serial1);
  delay(1000);
}

void kirimdata()
{
    Serial1.println(str);
    delay(1000);
}

void terimadata()
{
//    if (Serial.available()) {
//    Serial.write(Serial.read());
//    }

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
}
