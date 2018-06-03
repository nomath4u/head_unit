#include <SoftwareSerial.h>
SoftwareSerial rn_serial(D7,D6);
void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200);
  rn_serial.begin(115200);
  while(!Serial){;}
  Serial.println("Ready to go Serial");
}

void loop() {
  if(Serial.available() > 0){
    //Serial.println("Printing something");
    rn_serial.write(Serial.read());
  }
  if(rn_serial.available() > 0){
    //Serial.println("Receiving something");
    Serial.write(rn_serial.read());
  }
}
