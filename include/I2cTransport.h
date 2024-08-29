#ifndef I2C_TRANSPORT
#define I2C_TRANSPORT

#include <Arduino.h>

#define I2C_TRANSPORT_OK 0
#define I2C_INVALID_RSIZE 1
#define I2C_INVALID_RESPONSE_BUFF 2
#define I2C_ERROR_REQUEST 3
#define I2C_ERROR_RESPONSE 4


#define I2C_SIZE_MASK 0x3F
#define I2C_RW_MASK 0x40
#define I2C_EXT_MASK 0x80
#define I2C_ERR_MASK 0x40
#define I2C_OF_MASK 0x80
#define I2C_CRC_MASK 0XAA


uint8_t send_request(uint8_t dst,uint8_t proto,uint8_t cmd, u_int8_t rw, uint8_t size_params, u_int8_t*params, uint8_t size_response, uint8_t* response );

uint8_t send_response(uint8_t size,uint8_t* response,uint8_t of, uint8_t err, u_int8_t rSize);
uint8_t send_response_byte(uint8_t response,uint8_t of, uint8_t err, u_int8_t rSize);

#endif