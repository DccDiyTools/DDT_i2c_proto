#include <Arduino.h>

#ifndef SERIAL_OUT
#define SERIAL_OUT SerialUSB
#endif

#ifndef LED
#define LED PC13
#endif

void setup()
{
    SERIAL_OUT.begin(115200);
    pinMode(LED, OUTPUT);

}

void loop(){
    SERIAL_OUT.println("Serial Monitor HIGH");
    digitalWrite(LED,HIGH);
    delay(1000);    
    SERIAL_OUT.println("Serial Monitor LOW");
    digitalWrite(LED,LOW);
    delay(1000);    
}