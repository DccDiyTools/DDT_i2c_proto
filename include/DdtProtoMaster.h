#ifndef DDT_PROTO_MASTER
#define DDT_PROTO_MASTER
#include "DdtProto.h"
#ifdef DDT_MODE_CLIENT
#error "Master loaded in Client mode"
#endif
#include "DdtProtoDevice.h"

#endif