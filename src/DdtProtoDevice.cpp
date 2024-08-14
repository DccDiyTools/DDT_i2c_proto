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

u_int8_t scan_devices()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");

    return nDevices;
}