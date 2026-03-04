#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef REMAKE_328
#include <Arduino.h>
#include <time.h>
#include <SystemPins.hpp>
#elif defined(NATIVE)
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdint>
using namespace std;
#endif

struct Time {uint8_t DAY = 00;uint8_t MONTH = 00;uint8_t YEAR = 00;uint8_t HOUR = 00;uint8_t MINUTES = 00;uint8_t SECONDS = 00;};
namespace System {
    typedef Time DateTime;
    int GetFreeMemory();
    void InitLogs();
    void InitSysPins();
    bool IsCharging();
    int GetChargPercent();
    Time GetTime();
    void Log(const char* msg);
};

#endif