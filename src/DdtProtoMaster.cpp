#include "DdtProto.h"
#include "DdtProtoMaster.h"
#include "Wire.h"
#ifdef DDT_MODE_MASTER

p_i2c_dev scan_devices()
{
    byte error, address;
    int nDevices;
    p_i2c_dev ret = NULL;
    p_i2c_dev last =NULL;

    SERIAL_OUT.println("Scanning...");

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
            SERIAL_OUT.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            SERIAL_OUT.print(address, HEX);
            SERIAL_OUT.println("  !");
            if(ret == NULL){
                ret = (p_i2c_dev)malloc(sizeof(t_i2c_dev));
                last = ret;
            }else{
                last->next=(p_i2c_dev)malloc(sizeof(t_i2c_dev));
                last = last->next;
            }
            last->addr=address;
            last->caps=PANEL_I2C_UNKNOWN<<10;
            last->next=NULL;
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

    return ret;
}

void printI2cDevice(p_i2c_dev dev){
    SERIAL_OUT.printf("Device data:\n  addres:0x%02x\n",dev->addr);
    u_int8_t panel= (dev->caps & MASK_CAPS_PANEL) >> 10;
    SERIAL_OUT.printf("  panel: 0x%02x -> ",panel);
    switch (panel)
    {
    case PANEL_I2C_UNKNOWN:
        SERIAL_OUT.println("I2C Device");
        break;
    case PANEL_DRIVER_DESK_TFT:
        SERIAL_OUT.println("Driver Desk TFT");
        break;
    default:
        SERIAL_OUT.println("UNKNOWN");
        break;
    }
}

#endif