#ifndef DDT_PROTO
#define DDT_PROTO
#include <Arduino.h>

#define DDT_VERSION "0.0.1"

#if __has_include("DdtProtoConfig.h")
//this allows vscode to parse config
#include "DdtProtoConfig.h"
#endif

#include "ConfigCheck.h"
#include "DtdProtoProtocols.h"
#include "DtdProtoPanels.h"

extern "C" char* sbrk(int incr);
// free RAM (actually, free stack
inline uint32_t FreeBytes() {
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));
}

#endif