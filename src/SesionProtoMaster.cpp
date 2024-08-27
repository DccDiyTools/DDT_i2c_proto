#include "DdtProto.h"
#ifdef DDT_MODE_MASTER
#include "DdtProtoMaster.h"
#include "Wire.h"
#include "SesionProtoMaster.h"

uint8_t send_get_id(p_i2c_dev dev){

}

uint8_t send_get_caps(p_i2c_dev dev){return 0;}
uint8_t send_get_caps_proto(p_i2c_dev dev,uint8_t proto_id){return 0;}
uint8_t send_set_addr(p_i2c_dev dev,uint8_t new_addr){return 0;}
uint8_t send_get_addr(p_i2c_dev dev){
    
    // It is a ping
    Wire.beginTransmission(dev->addr);
    Wire.write(CMD_Get_Addr_R);

    if(Wire.endTransmission(false)!=0){
        SERIAL_OUT.println("Error1");
        return SESION_PROTO_I2C_ERROR;
    }
    u_int8_t read = Wire.requestFrom(dev->addr, 1);
    if(read!=1){
        SERIAL_OUT.printf("read is %u %u\n",read,Wire.available());
        SERIAL_OUT.println("Error2");

        Wire.endTransmission(true);
        return SESION_PROTO_I2C_ERROR;
    }
    byte addr = Wire.read();
    Wire.endTransmission(true);
    if (addr != dev->addr){
        SERIAL_OUT.printf("ADDR MissMatch %02x was %02x\n",dev->addr,addr);
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