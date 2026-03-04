#include "Utils.hpp"

//template <size_t N>
bool IfByteArraysAreSame(const uint8_t (&arrayA)[8], const uint8_t (&arrayB)[8])
{
    for (size_t i = 0; i < 8; ++i) {
        if (arrayA[i] != arrayB[i]){
            return false;
        }
    }
    return true;
}

bool IfByteArraysAreSamePointers(const uint8_t** arrayA, const uint8_t** arrayB)
{
    for (size_t i = 0; i < 8; ++i) {
        if (arrayA[i] != arrayB[i]){
            return false;
        }
    }
    return true;
}

bool IsValueFalseArrayByte(const uint8_t (&ar)[8])
{
    for (int i = 0; i < 8; ++i) {
        if (ar[i] != 0){
            return false;
        }
    }
    return true;
}

int findDuplicateRow(uint8_t arr[][8], int rowCount) {
  for (int i = 0; i < rowCount; i++) {
    for (int j = i + 1; j < rowCount; j++) {
      bool same = true;
      for (int k = 0; k < 8; k++) {
        if (arr[i][k] != arr[j][k]) {
          same = false;
          break;
        }
      }
      if (same) return j;
    }
  }
  return -1;
}

int findDuplicateRowPointer(uint8_t** arr, int rowCount) {
  for (int i = 0; i < rowCount; i++) {
    for (int j = i + 1; j < rowCount; j++) {
      bool same = true;
      for (int k = 0; k < 8; k++) {
        if (arr[i][k] != arr[j][k]) {
          same = false;
          break;
        }
      }
      if (same) return j;
    }
  }
  return -1;
}

int XChar_to_Pixel(int char_count_X)
{
  return char_count_X * 5;
}
int YChar_to_Pixel(int char_count_Y)
{
  return char_count_Y * 8;
}

void foo(const uint8_t* arr, size_t len, uint8_t (&out)[8]) {
  for (size_t i=0; i<len; i++) {
    out[i] = arr[i];
  }
  return;
}

const char* TimeFormater(uint8_t h,uint8_t m,uint8_t s)
{
  static char buffer[16];
  if (s == 255)
  {
    snprintf(buffer,sizeof(buffer), "%02d:%02d",h,m);
  }
  else
  {
  snprintf(buffer,sizeof(buffer), "%02d:%02d:%02d",h,m,s);
  }
  return buffer;
}

void Sleep_for(uint16_t ms)
{
  #ifdef REMAKE_328
  for (uint16_t _ = 0;_ < ms;_++)
  {
    _delay_ms(1);
  }
  #elif defined(NATIVE)
  SDL_Delay(ms);
  #endif
}

int add_ifdec(float value)
{
  if ((int)value == value)
  {
    return (int)value;
  }else
  {
    return ((int)value) + 1;
  }
}


#ifdef NATIVE
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
#endif