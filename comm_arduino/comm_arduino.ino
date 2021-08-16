  
#include <SoftwareSerial.h>

SoftwareSerial s(5,6);
String data;

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

kirimdata();
//terimadata();
}

void kirimdata()
{
  s.println(data);
  delay(1000);
}


void terimadata()
{
  if (Serial.available()) {
  Serial.write(Serial.read());
}
}
