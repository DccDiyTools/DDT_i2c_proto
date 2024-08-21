#ifndef DDT_PROTO_MASTER
#define DDT_PROTO_MASTER
#include "DdtProto.h"
#ifdef DDT_MODE_CLIENT
#error "Master loaded in Client mode"
#endif
#include "DdtProtoDevice.h"

typedef struct s_i2c_dev t_i2c_dev;
typedef t_i2c_dev* p_i2c_dev;

struct s_i2c_dev{
    u_int8_t addr;
    u_int16_t caps;
    
   p_i2c_dev next;
} ;


p_i2c_dev scan_devices();
void printI2cDevice(p_i2c_dev dev);

#endif