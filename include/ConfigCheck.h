/*
This file runs a check on the configuration
*/

#include "DdtProto.h"
#ifndef DDT_I2C_PROTO_CONFIG
#warning "DDT_I2C_PROTO_CONFIG not definded, please add '-include ./include/DdtProtoConfig.h' to build_flags or ensure all required defines are set"
#endif

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