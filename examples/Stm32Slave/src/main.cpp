#include <Arduino.h>
#include <DdtProtoClient.h>

#ifndef SERIAL_OUT
#define SERIAL_OUT SerialUSB
#endif

#ifndef LED
#define LED PC13
#endif

u_int32_t next_High;
u_int32_t next_Low;

void setup()
{
    SERIAL_OUT.begin(115200);
    delay(1000);
    pinMode(LED, OUTPUT);

    SERIAL_OUT.println("Stm32Slave Example Init");
    initDdtProtoDevice();
    pinMode(PB6, INPUT_PULLUP);
    pinMode(PB7, INPUT_PULLUP);

    next_High=millis() -1;
    next_Low=next_High+1000;
    
}

void loop(){
    u_int32_t cMillis = millis();
    if(cMillis>next_High){
        SERIAL_OUT.println("Serial Monitor HIGH");
        digitalWrite(LED,HIGH);
        while (next_High<cMillis)next_High+=2000;

    }
    if(cMillis>next_Low){
        SERIAL_OUT.println("Serial Monitor LOW");
        digitalWrite(LED,LOW);
        while (next_Low<cMillis)next_Low+=2000;
    }
    
}