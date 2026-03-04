#ifndef UISMEM_H
#define UISMEM_H

#include <Arduino.h>

#include "list_ICs/ESP32-UART/chip.hpp"

class UISMem {
public:
    static void Init();
};

class UISMem_byte {
public:

    class _1D {
    private:
        uint16_t addrs;
    public:
        _1D(size_t s) {addrs = Memory::AllocateMemory(s);}

        class Element {
        private:
            uint16_t addr;
        public:
            Element(uint16_t a) : addr(a) {}
            Element& operator=(uint8_t var)
            {
                Memory::SaveDataByByte(var,addr);
                return *this;
            }
            operator uint8_t() {
                return Memory::GetDataFrmAddress(addr);
            }
        };

        Element operator[](size_t index)
        {
            return Element(addrs + index);
        }
    };

    class _2D {
    private:
        uint16_t addrs;
        size_t sizes[2];
    public:
        _2D(size_t sizeA,size_t sizeB) {addrs = Memory::AllocateMemory(sizeA*sizeB);sizes[0] = sizeA;sizes[1] = sizeB;};

        class Element {
        private:
            uint16_t addr;
        public:
            Element(uint16_t a) : addr(a) {}
            Element& operator=(uint16_t var)
            {
                Memory::SaveDataByByte(var,addr);
                return *this;
            }
            operator uint8_t() {
                return Memory::GetDataFrmAddress(addr);
            }
        };

        class Row {
        private:
            uint16_t addr;
            size_t* sizes_2;
        public:
            Row(uint16_t a,size_t* s) : addr(a) , sizes_2(s){}
            Element operator[](size_t index) 
            {
                return Element(addr + index);
            }
            operator uint8_t*() {
                return Memory::GetSerialDataFrmAddress(sizes_2[1],addr);
            }
        };

        Row operator[](size_t index)
        {
            return Row(addrs + (sizes[1] * index),sizes);
        }
        operator uint8_t**() {
            uint8_t** temp;
            for (size_t i = 0;i < sizes[0];i++)
            {
                temp[i]= Memory::GetSerialDataFrmAddress(sizes[1],addrs);
            }
            return temp;
        }
    };

    class _3D {
    private:
        uint16_t addrs;
        size_t sizes[3];
    public:
        _3D(size_t sizeA,size_t sizeB,size_t sizeC) {addrs = Memory::AllocateMemory(sizeA*sizeB*sizeC);sizes[0] = sizeA;sizes[1] = sizeB;sizes[2] = sizeC;};

        class Element {
        private:
            uint16_t addr;
        public:
            Element(uint16_t a) : addr(a) {}
            Element& operator=(uint8_t var)
            {
                Memory::SaveDataByByte(var,addr);
                return *this;
            }
            operator uint8_t() {
                return Memory::GetDataFrmAddress(addr);
            }
        };

        class RowB {
        private:
            uint16_t addr;
            size_t* sizes_2;
        public:
            RowB(uint16_t a,size_t* s) : addr(a),sizes_2(s) {}
            Element operator[](size_t index) 
            {
                return Element(addr + index);
            }
            operator uint8_t*() 
            {
                return Memory::GetSerialDataFrmAddress(sizes_2[2],addr);
            }
        };

        class RowA {
        private:
            uint16_t addr;
            size_t* sizes_2;
        public:
            RowA(uint16_t a,size_t* s) : addr(a),sizes_2(s) {}
            RowB operator[](size_t index) 
            {
                return RowB(addr + (sizes_2[2] * index),sizes_2);
            }
            operator uint8_t**() {
                uint8_t** temp;
                for (size_t i = 0; i < sizes_2[1]; i++)
                {
                    temp[i] = Memory::GetSerialDataFrmAddress(sizes_2[2],addr);
                }
                return temp;
            }
        };

        RowA operator[](size_t index)
        {
            return RowA(addrs + ((sizes[1] * index) * sizes[2]),sizes);
        }
    };

    
};
#endif