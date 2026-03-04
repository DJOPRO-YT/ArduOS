#ifndef HN_UIMANAGER_H
#define HN_UIMANAGER_H

#include <UIManager.hpp>
#include <stdlib.h>
#include <stdint.h>

class HNUIManager {
    
public:
static const char* DrawPixel(const char* args);
static const char* ErasePixel(const char* args);
static const char* PrintText(const char* args);
static const char* DrawCharacter(const char* args);
};
#endif