#include "System.hpp"

int System::GetFreeMemory()
{
    #ifdef REMAKE_328
    extern unsigned int __bss_end;
    extern unsigned int __heap_start;
    extern void *__brkval;

    int free_memory;
    if ((int)__brkval == 0)
        free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
        free_memory = ((int)&free_memory) - ((int)__brkval);

    return free_memory;
    #endif
    return 0;
}

void System::InitLogs()
{
    #ifdef REMAKE_328
    Serial.begin(115200);
    #endif
}

void System::Log(const char* msg)
{
    #ifdef REMAKE_328
    Serial.println(msg);
    #elif defined(NATIVE)
    printf(msg);
    #endif
}

void System::InitSysPins()
{
    #ifdef REMAKE_328
    pinMode(CHARGE_CHECK,INPUT);
    #endif
}

bool System::IsCharging()
{
    #ifdef REMAKE_328
    return digitalRead(CHARGE_CHECK);
    #endif
    return true;
}

Time System::GetTime()
{
    Time hhitemp;

    #ifdef NATIVE
    time_t time__;
    time(&time__);
    struct tm datetime__ = *localtime(&time__);
    hhitemp.DAY = datetime__.tm_mday;
    hhitemp.HOUR = datetime__.tm_hour;
    hhitemp.MINUTES = datetime__.tm_min;
    hhitemp.MONTH = datetime__.tm_mon;
    hhitemp.SECONDS = datetime__.tm_sec;
    hhitemp.YEAR = datetime__.tm_year;
    #elif defined(REMAKE_328)

    float time = millis();
    hhitemp.SECONDS = time/1000;
    hhitemp.MINUTES = hhitemp.SECONDS/60;
    hhitemp.HOUR = hhitemp.MINUTES/60;
    hhitemp.DAY = hhitemp.HOUR/24;
    hhitemp.MONTH = hhitemp.DAY/30;
    hhitemp.YEAR = hhitemp.MONTH/12;

    #endif
    
    return hhitemp;
}

int System::GetChargPercent()
{
    #ifdef REMAKE_328

    int raw = analogRead(BATTERY_VOLUME);
    //raw = constrain(raw, 900, 1023);
    return map(raw, 0, 1023, 0, 100);

    #endif
    return 100;
}