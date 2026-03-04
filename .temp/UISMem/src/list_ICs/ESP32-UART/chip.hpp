#ifndef UISMEM_ESP32_UART_H
#define UISMEM_ESP32_UART_H

/*

 + ESP32-UART-SOFTRAM
 + (Used for testing only)

 - MAX MEMORY = 20000Bytes RAM
 - "Bus" Address = 16bit

*/
#include <stdint.h>
#include <SoftwareSerial.h>
#include <util/delay.h>

extern SoftwareSerial uart_chip;

#define ALLOCATEMEM 0x30
#define SETDATABYTE 0x20
#define SETDATASERIAL 0x21
#define GETDATABYTE 0x10
#define GETDATASERIAL 0x11

#define DELAY_MS_BFR_DATA 3

class Memory {
public:
    static void Init();
    static uint16_t AllocateMemory(size_t size);
    static void SaveDataByByte(uint8_t data,uint16_t addrs);
    static uint8_t GetDataFrmAddress(uint16_t address);

    static void SaveDataBySerialByte(uint8_t* data,size_t bytes,uint16_t addrs);
    static uint8_t* GetSerialDataFrmAddress(size_t bytes,uint16_t addrs);
};

#endif