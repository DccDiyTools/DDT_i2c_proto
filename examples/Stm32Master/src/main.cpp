#include <Arduino.h>
#include <DdtProtoMaster.h>

#ifndef SERIAL_OUT
#define SERIAL_OUT SerialUSB
#endif

#ifndef LED
#define LED PC13
#endif

u_int32_t next_High;
u_int32_t next_Low;
u_int32_t next_Scan;

void setup()
{
    SERIAL_OUT.begin(115200);
    pinMode(LED, OUTPUT);
    initDdtProtoDevice();
    next_High=millis() -1;
    next_Low=next_High+1000;
    next_Scan=next_High;
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
    
    if(cMillis>next_Scan){
        uint8_t found= scan_devices();
        SERIAL_OUT.printf("Found: %u devices\n",found);
        cMillis = millis();
        next_Scan=cMillis+5000;
        while (next_High<cMillis)next_High+=2000;
        while (next_Low<cMillis)next_Low+=2000;
    }

}