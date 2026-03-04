#ifdef REMAKE_328

#ifndef MODULES_H
#define MODULES_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <UIManager.hpp>
#include <Controller.hpp>

#include <SystemPins.hpp>
#define CS CS_MODULE
#define TX TX_MODULE
#define RX RX_MODULE

#define SPI_MODE_COM 1
#define UART_MODE_COM 0

struct InfoModule {
    char name[15]; //20 character MAX
    int Type; // [0]: Cartige | [1]: ROM Memory
    int com_type = UART_MODE_COM;
    char ID[10]; // Ex: ABG58D6S4R
    bool connected = false;
};

extern InfoModule info;
extern SoftwareSerial uart;

class Module {
public:
    Module();
    static void Init();
    static bool Connect();
    static void Launch();
    static bool IsConnected();
    static InfoModule GetModuleInfos();
    static const char* GetDriverData();

    /*
    
      ---- Mode 0 ----
       Start() -> Listen to commands from cartridge

      ---- Mode 1 ----
       Start() -> Coming soon

    */
};

#endif
#endif