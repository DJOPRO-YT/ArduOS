#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
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

void DrawJoyStick(SDL_Renderer * renderer, int x, int y, int radius,int halftmaxzone, bool &isclicked, int &currentPosX, int &currentPosY)
{
    SDL_Rect zone_ = {x - (halftmaxzone + radius + 1),y - (halftmaxzone + radius + 1),2*(halftmaxzone + radius + 11),2*(halftmaxzone + radius + 1)};

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderFillCircle(renderer,x,y,radius);
    SDL_RenderPresent(renderer);

    bool run_ = true;
    bool clicked = false;
    //int currentPosX,currentPosY;
    //int posX,posY = 0;
    SDL_Event events;
    while (run_)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                {
                    run_ = false;
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    SDL_RenderFillRect(renderer,&zone_);

                    SDL_RenderFillCircle(renderer,constrain(events.motion.x,x-halftmaxzone,halftmaxzone + x),constrain(events.motion.y,y-halftmaxzone,halftmaxzone + y),radius);
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    SDL_RenderFillCircle(renderer,x,y,radius);

                    currentPosY = map(x,y-halftmaxzone,halftmaxzone + y,0,1024);
                    currentPosX = map(y,x-halftmaxzone,halftmaxzone + x,0,1024);

                    SDL_RenderPresent(renderer);

                    bool aa = events.button.x <= x + radius && events.button.x >= x - radius;
                    bool bb = events.button.y <= y + radius && events.button.y >= y - radius;
                    if (!clicked && aa && bb)
                    {

                        isclicked = true;
                        //{cout << "clicked";}
                        this_thread::sleep_for(chrono::milliseconds(100));//delay
                        isclicked = false;
                    }
                    else
                    {
                        clicked = false;
                    }
                }
                case SDL_MOUSEMOTION:
                {
                    int btnx,btny;
                    uint32_t buttons = SDL_GetMouseState(&btnx,&btny);
                    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                        //
                        if (!clicked) {
                            bool aa = events.motion.x <= x + radius && events.motion.x >= x - radius;
                            bool bb = events.motion.y <= y + radius && events.motion.y >= y - radius;
                            if (aa && bb) {
                                clicked = true;
                            }

                        }

                        if (clicked){

                            currentPosY = map(constrain(events.motion.y,y-halftmaxzone,halftmaxzone + y),y-halftmaxzone,halftmaxzone + y,0,1024);
                            currentPosX = map(constrain(events.motion.x,x-halftmaxzone,halftmaxzone + x),x-halftmaxzone,halftmaxzone + x,0,1024);
                            
                            SDL_SetRenderDrawColor(renderer,255,255,255,255);
                            SDL_RenderFillRect(renderer,&zone_);
                            //SDL_RenderFillCircle(renderer,events.motion.x - events.motion.xrel,events.motion.y - events.motion.yrel,radius);
                            SDL_SetRenderDrawColor(renderer,0,0,0,255);
                            SDL_RenderFillCircle(renderer,constrain(events.motion.x,x-halftmaxzone,x+halftmaxzone),constrain(events.motion.y,y-halftmaxzone,y+halftmaxzone),radius);
                            SDL_RenderPresent(renderer);
                        }
                    }else{
                        clicked = false;
                    }
                    break;
                }
            }
        }
    }
}
int main()
{
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 1;
        //printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("MyWindow",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,500,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    SDL_Event events;
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    bool iscls;
    int posx,posy;
    thread t1(DrawJoyStick,renderer,200,200,50,20,ref(iscls),ref(posx),ref(posy));
    t1.detach();
    //DrawJoyStick(renderer,200,200,50,20,iscls,posx,posy);

    bool run_ = true;
    bool clicked = false;
    while (run_)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                {
                    run_ = false;
                    break;
                }
            }
        }

        cout << posx << " " << posy << " " << (iscls ? "true" : "false") << endl;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}