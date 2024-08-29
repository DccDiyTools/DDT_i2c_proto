#include "DdtProtoDevice.h"
#include <Wire.h>
#ifdef DDT_MODE_CLIENT
#include "I2cTransport.h"

u_int8_t* buff=NULL;
u_int8_t buff_size=0;

void onClientReceive(int reg)
{
    SERIAL_OUT.printf("onReceive %u\n",reg);
    if (buff!=NULL || buff_size!= reg){
        free(buff);
        buff=NULL;
        buff=(byte*)malloc(reg*sizeof(u_int8_t));
        buff_size=reg;
    }

    u_int8_t read = Wire.readBytes(buff,reg);
    SERIAL_OUT.printf("  read %u\n  ->",read);
    for(int i=0;i<read;i++){
        SERIAL_OUT.printf(" %02x",buff[i]);
    }
    SERIAL_OUT.println("\n");
}

void onClientRequest(void){
    SERIAL_OUT.println("onRequest");
    byte rsize = buff[0] & I2C_SIZE_MASK;
    send_response_byte(9,false, false, rsize);
    SERIAL_OUT.println();
}

#endif


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
