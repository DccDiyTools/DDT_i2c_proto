#ifndef DDT_PROTO_CLIENT
#define DDT_PROTO_CLIENT

#include <DdtProto.h>


#ifdef DDT_MODE_MASTER
#error "Client loaded in Master mode"
#endif

#include "DdtProtoDevice.h"

#endif