#include <Arduino.h>
#include <DdtProtoMaster.h>
#include <SesionProtoMaster.h>

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
    delay(2000);//wait 2 seconds to allow clients init
    SERIAL_OUT.println("Ddt I2C Protocol Master " DDT_VERSION  " (" __DATE__ ")");
    

    SERIAL_OUT.print("Free bytes: ");
    SERIAL_OUT.println(FreeBytes());
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
        p_i2c_dev found= scan_devices();
        SERIAL_OUT.print("Free bytes: ");
        SERIAL_OUT.println(FreeBytes());
        u_int8_t n_Devices=0;
        while (found != NULL){
            p_i2c_dev curr= found;
            found = found->next;
            n_Devices++;

            if(send_get_addr(curr)==SESION_PROTO_OK){
                SERIAL_OUT.println("   ***Compatible");
            }

            printI2cDevice(curr);
            SERIAL_OUT.println();
            free(curr);
        }


        SERIAL_OUT.printf("Found: %u devices\n",n_Devices);
        SERIAL_OUT.print("Free bytes: ");
        SERIAL_OUT.println(FreeBytes());

        cMillis = millis();
        next_Scan=cMillis+5000;
        while (next_High<cMillis)next_High+=2000;
        while (next_Low<cMillis)next_Low+=2000;
    }

}