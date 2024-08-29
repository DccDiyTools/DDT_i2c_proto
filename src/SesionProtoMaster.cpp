#include "DdtProto.h"
#ifdef DDT_MODE_MASTER
#include "DdtProtoMaster.h"
#include "SesionProtoMaster.h"
#include "I2cTransport.h"

uint8_t send_get_id(p_i2c_dev dev){return 0;}

uint8_t send_get_caps(p_i2c_dev dev){return 0;}
uint8_t send_get_caps_proto(p_i2c_dev dev,uint8_t proto_id){return 0;}
uint8_t send_set_addr(p_i2c_dev dev,uint8_t new_addr){return 0;}
uint8_t send_get_addr(p_i2c_dev dev){
    
    u_int8_t resp[3];

    u_int8_t ret = send_request(dev->addr, 0,CMD_Get_Addr_R, false,0,NULL,3,resp);

    if (resp[1] != dev->addr){
        SERIAL_OUT.printf("ADDR MissMatch %02x was %02x\n",dev->addr,resp[1]);
        return SESION_PROTO_ERROR;
    }

    return SESION_PROTO_OK;
} 
uint8_t send_reset(p_i2c_dev dev){return 0;}
uint8_t send_e_stop(p_i2c_dev dev){return 0;}
uint8_t send_stod(p_i2c_dev dev){return 0;} //Dev can be null so it is a general
uint8_t send_send_int(p_i2c_dev dev){return 0;}
uint8_t send_ack_int(p_i2c_dev dev){return 0;}
uint8_t send_read_event(p_i2c_dev dev){return 0;} //TODO: ¿Return? ¿CB from other protocols?
uint8_t send_init(p_i2c_dev dev){return 0;} //Dev can be null so it is a general
uint8_t send_get_status(p_i2c_dev dev){return 0;}//TODO: ¿Return? ¿CB from other protocols?

#endif