#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
 
String data;
void setup() {
Serial.begin(115200);
s.begin(115200);
delay(2000);
}
 
void loop() {
data =String("suhu = 10, lempap = 20");
s.println(data);
delay(1000);
}
