#ifndef DDT_PROTO_DEVICE
#define DDT_PROTO_DEVICE
#include <Arduino.h>

#ifdef DDT_MODE_MASTER
#ifdef DDT_MODE_CLIENT
#error "Define only one Mode -D DTT_MODE_MASTER or -D DDT_MODE_CLIENT"
#endif
#endif

#ifndef DDT_MODE_MASTER
#ifndef DDT_MODE_CLIENT
#error "Define one Mode -D DTT_MODE_MASTER or -D DDT_MODE_CLIENT"
#endif
#endif


u_int8_t initDdtProtoDevice();

u_int8_t scan_devices();

#endif