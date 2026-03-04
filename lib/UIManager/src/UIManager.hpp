#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#ifdef REMAKE_328
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;
#endif

#ifdef NATIVE
#include "ChLCD_SDL2.hpp"
extern LCDCHAR_SDL2 lcd;
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <iostream>
#endif

#include <Utils.hpp>
#include <Controller.hpp>
//#include <UISMem.hpp>

#ifdef UISMEM_H
    extern UISMem_byte::_3D Memory;
    extern UISMem_byte::_2D MemoryScreen;
#else
extern uint8_t Memory[4][20][8];
extern uint8_t MemoryScreen[8][8];
#endif
extern int id_to_recover;


namespace UIManager {
    //UIManager();
    void init();
    #ifdef NATIVE
    void SDL2init(SDL_Renderer* renderer);
    #endif
    void FullRefresh();
    void Refresh(const int &posX,const int &posY);
    void DrawPixel(int posX,int posY,int pixelX,int pixelY);
    void ErasePixel(int posX,int posY,int pixelX,int pixelY);
    void PrintText(int posX,int posY,const char* text);
    void DrawCharacter(int posX,int posY,uint8_t (&char_)[8]);
    #ifdef REMAKE_328
    void DrawICO_P(int posX,int posY,const uint8_t progmem [2][3][8] PROGMEM);
    #elif defined(NATIVE)
    void DrawICO(int posX,int posY,const uint8_t progmem [2][3][8]);
    #endif
    void ClearScreen();
    void ResetScreen();

    void ShowDialog(const char title[8],const char* text);
};


#endif