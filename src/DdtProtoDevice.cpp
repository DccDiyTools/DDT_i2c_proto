#include "DdtProtoDevice.h"
#include <Wire.h>

void onClientReceive(int reg)
{
    SERIAL_OUT.println("onReceive");
    while (Wire.available() > 0)
    {
        u_int8_t data;
        data = Wire.read(); // Not best option
        SERIAL_OUT.print(data);
        int w = Wire.write(data + 1); // Test Made.
    }
}

void onClientRequest(void){
    SERIAL_OUT.println("onRequest");
    while (Wire.available() > 0)
    {
        u_int8_t data;
        data = Wire.read(); // Not best option
        SERIAL_OUT.print(data);
        int w = Wire.write(data + 1); // Test Made.
    }
}

u_int8_t initDdtProtoDevice()
{
#ifdef DDT_MODE_MASTER
#pragma message "DDT_MODE_MASTER"
    SERIAL_OUT.println("Begin Master");
    Wire.begin();
#endif
#ifdef DDT_MODE_CLIENT
#pragma message "DDT_MODE_CLIENT"
    SERIAL_OUT.println("Begin Client");
    Wire.begin(9);
    Wire.onReceive(onClientReceive);
    Wire.onRequest(onClientRequest);
#endif
    return 0;
}
