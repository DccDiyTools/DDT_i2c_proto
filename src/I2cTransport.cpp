
#include "DdtProto.h"
#include "I2cTransport.h"
#include "Wire.h"


uint8_t send_request(uint8_t dst,uint8_t proto,uint8_t cmd, u_int8_t rw, uint8_t size_params, u_int8_t*params, uint8_t size_response, uint8_t* response ){
    if (size_response > 63 || size_response<3) return I2C_INVALID_RSIZE;
    if(response == NULL) return I2C_INVALID_RESPONSE_BUFF;
    if(size_params>0 && params==NULL) return I2C_INVALID_RESPONSE_BUFF;
    

    byte hdr = size_response & I2C_SIZE_MASK;
    if(rw) hdr |= I2C_RW_MASK;
    if(proto>10) hdr |= I2C_EXT_MASK;

    byte crc =0;
    
    // It is a ping
    Wire.beginTransmission(dst);
    Wire.write(hdr);//hdr
    crc=hdr;
    if(proto>10){
        Wire.write(proto);
        crc+=proto;
    }
    Wire.write(cmd);
    crc+=cmd;
    for(uint t =0; t<size_params;t++){
        Wire.write(params[t]);
        crc+params[t];
    }
    crc ^= I2C_CRC_MASK;
    Wire.write(crc);


    if(Wire.endTransmission(false)!=0){
        SERIAL_OUT.println("Error1");
        return I2C_ERROR_REQUEST;
    }
    u_int8_t read = Wire.requestFrom(dst, size_response);
    if(read!=size_response){
        SERIAL_OUT.printf("read is %u %u\n",read,Wire.available());
        SERIAL_OUT.println("Error2");

        Wire.endTransmission(true);
        return I2C_ERROR_RESPONSE;
    }
    Wire.readBytes(response,size_response);
    Wire.endTransmission(true);

    //Check DATA.
    return I2C_TRANSPORT_OK;
}

uint8_t send_response_byte(uint8_t response,uint8_t of, uint8_t err, u_int8_t rSize){
    return send_response(1,&response,of,err,rSize);
}

uint8_t send_response(uint8_t size,uint8_t* response,uint8_t of, uint8_t err, u_int8_t rSize){
    int pad = rSize - 2 -size;

    byte crc = 0;
    byte hdr = size & I2C_SIZE_MASK;
    if (of) hdr|= I2C_OF_MASK;
    if (err) hdr|= I2C_ERR_MASK;

    crc = hdr;
    Wire.write(hdr);
    SERIAL_OUT.printf("  -> %02x",hdr);
    Wire.write(response,size);
    for(int i =0; i< size;i++){ 
        crc+=response[i];
        SERIAL_OUT.printf(" %02x",response[i]);
    }
    for (int i=0;i<pad;i++){
        Wire.write((uint8_t)pad);
        SERIAL_OUT.printf(" %02x",pad);
        crc+=pad;
    }
    crc ^= I2C_CRC_MASK;
    Wire.write(crc);
    SERIAL_OUT.printf(" %02x",crc);
    return I2C_OK;
}