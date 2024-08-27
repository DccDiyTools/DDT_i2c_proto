#ifndef DDT_SESION_PROTO_MASTER
#define DDT_SESION_PROTO_MASTER
#include "DdtProto.h"
#include "DdtProtoMaster.h"

uint8_t send_get_id(p_i2c_dev dev);
uint8_t send_get_caps(p_i2c_dev dev);
uint8_t send_get_caps_proto(p_i2c_dev dev,uint8_t proto_id);
uint8_t send_set_addr(p_i2c_dev dev,uint8_t new_addr);
uint8_t send_get_addr(p_i2c_dev dev); // It is a ping
uint8_t send_reset(p_i2c_dev dev);
uint8_t send_e_stop(p_i2c_dev dev);
uint8_t send_stod(p_i2c_dev dev); //Dev can be null so it is a general
uint8_t send_send_int(p_i2c_dev dev);
uint8_t send_ack_int(p_i2c_dev dev);
uint8_t send_read_event(p_i2c_dev dev); //TODO: ¿Return? ¿CB from other protocols?
uint8_t send_init(p_i2c_dev dev); //Dev can be null so it is a general
uint8_t send_get_status(p_i2c_dev dev);//TODO: ¿Return? ¿CB from other protocols?


#define SESION_PROTO_OK 0
#define SESION_PROTO_ERROR 1
#define SESION_PROTO_I2C_ERROR 2

#endif