#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef NATIVE
#include "JoyStickSDL2.hpp"
#include <thread>
#include <chrono>
#else
#include <Arduino.h>
#endif
struct JoyStickPos {int x;int y;};

#ifdef REMAKE_328
#include <SystemPins.hpp>
#endif

namespace Controller {
    #ifdef NATIVE
    void SDL2init(SDL_Renderer* renderer_);
    void SetEnable(bool enable);
    #endif
    void Init();
    JoyStickPos GetJPos();
    bool IsBtnClicked();
};

#endif