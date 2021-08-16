#include <SoftwareSerial.h>
String str;
char dataterima[100];

void setup(){
Serial.begin(115200);
Serial1.begin(115200);
delay(2000);
}
void loop()
{
str =String("coming from ESP8266: ");

terimadata();
//kirimdata();

//delay(1000);
}

void kirimdata()
{
    Serial1.println(str);
    delay(1000);
}

void terimadata()
{
    if (Serial.available()) {
    Serial.write(Serial.read());

//    sprintf(dataterima, "%d", Serial.read());
        
//    if(strstr(Serial.read(), "cok"))
//    {
//        Serial.println("found");
//        }
    }
}
