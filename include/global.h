#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <iostream>

#include "Shared.h"

typedef long int64;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#pragma warning(disable:4996) // This function or variable may be unsafe
#pragma warning(disable:4244) // Conversion from T1 to T2, possible loss of data

#ifdef _DEBUG
 #define DATA_PATH "..\\..\\data"
 #define CONF_PATH "..\\..\\config"
#else
 #define DATA_PATH ".\\data"
 #define CONF_PATH "."
#endif

#endif
