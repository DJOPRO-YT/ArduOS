#include "chip.hpp"

SoftwareSerial uart_chip(7, 8);
/*

- KAWTHIR 5MISSI
- JA3FIR SAMMY

*Reclamation contre plaquare
*Faux couleur machine
*Couba plaquare

* 93 251 579

** Dispo cette semaine selement

*/
void Memory::Init()
{
    uart_chip.begin(115200);
}

uint16_t Memory::AllocateMemory(size_t size)
{
    uart_chip.write(ALLOCATEMEM);//uart_chip.println(ALLOCATEMEM);

    _delay_ms(DELAY_MS_BFR_DATA);
    uart_chip.println(size);
    if (uart_chip.available()) 
    {
        uint8_t buff[1];
        char addrs = uart_chip.readBytes(buff,1); // example : 0x01 = 00000001 = [0000][0001]
        return (uint16_t)buff[0];
    }
    return '\0';
}

void Memory::SaveDataByByte(uint8_t data,uint16_t addrs) 
{
    uart_chip.write(SETDATABYTE);//uart_chip.println(SETDATABYTE);

    _delay_ms(DELAY_MS_BFR_DATA);
    uart_chip.println(addrs);
    uart_chip.println(data);
}

uint8_t Memory::GetDataFrmAddress(uint16_t address)
{
    uart_chip.write(GETDATABYTE);//uart_chip.println(GETDATABYTE);

    _delay_ms(DELAY_MS_BFR_DATA);
    uart_chip.println(address);

    if (uart_chip.available()) 
    {
        uint8_t buff[1];
        char addrs = uart_chip.readBytes(buff,1);
        return buff[0];
    }
    return '\0';
}

void Memory::SaveDataBySerialByte(uint8_t* data,size_t bytes,uint16_t addrs)
{
    uart_chip.write(SETDATASERIAL);//uart_chip.println(SETDATASERIAL);

    _delay_ms(DELAY_MS_BFR_DATA);
    uart_chip.println(addrs);
    String data_r;
    for (size_t i = 0; i < bytes; i++)
    {
        data_r += data[i];
    }
    uart_chip.write(data, bytes);//uart_chip.println(data_r);
}

uint8_t* Memory::GetSerialDataFrmAddress(size_t bytes,uint16_t addrs)
{
    uart_chip.write(GETDATASERIAL);//uart_chip.println(GETDATASERIAL);

    _delay_ms(DELAY_MS_BFR_DATA);
    uart_chip.println(addrs);
    uart_chip.println(bytes);

    while (1) {
    if (uart_chip.available()) 
    {
        uint8_t buff[bytes];
        char data_ = uart_chip.readBytes(buff,bytes);
        return buff;

    }
    _delay_us(100);
    }
}