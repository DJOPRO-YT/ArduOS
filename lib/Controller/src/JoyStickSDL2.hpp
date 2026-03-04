#ifndef JOTSTICK_SDL2_H
#define JOTSTICK_SDL2_H

#ifdef NATIVE
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <Utils.hpp>

using namespace std;

static SDL_Renderer* renderer;
static bool iscls = false;
static int posx,posy = 0;
static bool enabled = false;

namespace JoyStick {
void SDL2init(SDL_Renderer* renderer_);
void SetEnable(bool enable);
bool isClicked();
int GetPosX();
int GetPosY();
}

#endif
#endif