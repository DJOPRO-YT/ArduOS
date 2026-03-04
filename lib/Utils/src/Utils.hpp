#ifndef UTILS_H
#define UTILS_H

//#include <Arduino.h>
#ifdef REMAKE_328
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#elif defined(NATIVE)
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <SDL2/SDL.h>
#endif

//typedef uint8_t byte;

bool IfByteArraysAreSame(const uint8_t(&arrayA)[8], const uint8_t(&arrayB)[8]);
bool IsValueFalseArrayByte(const uint8_t(&ar)[8]);
bool IfByteArraysAreSamePointers(const uint8_t** arrayA, const uint8_t** arrayB);
int findDuplicateRow(uint8_t arr[][8], int rowCount);
int findDuplicateRowPointer(uint8_t** arr, int rowCount);
int XChar_to_Pixel(int char_count_X);
int YChar_to_Pixel(int char_count_Y);
void Sleep_for(uint16_t ms);
const char* TimeFormater(uint8_t h,uint8_t m=0,uint8_t s=0);
void foo(const uint8_t* arr, size_t len, uint8_t(&out)[8]);
int add_ifdec(float value);
#ifdef NATIVE
long map(long x, long in_min, long in_max, long out_min, long out_max);
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
#endif

#endif