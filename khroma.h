#ifndef KHROMA_H
#define KHROMA_H

#include <PolychrHAUM.h>

#ifdef BUILD_PC
#define A0 0
#define A1 1
#endif

#define PIN__BTN1          2
#define PIN__BTN2          3
#define PIN__POWER_BTN     4
#define PIN__POWER_CMD     5
#define PIN__POWER_STATUS  6
#define PIN__LEDSTRIP_DATA 10
#define PIN__POTAR_LIGHT   A0
#define PIN__POTAR_SPEED   A1
#define PIN__ALEA          A2

extern PolychrHAUM <150, PIN__LEDSTRIP_DATA> khroma;

#endif
