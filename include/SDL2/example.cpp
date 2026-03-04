#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"

void DrawCharArea(SDL_Renderer* renderer, int x__,int y__,int pixelSize)
{
    int padX = 1;
    int padY = 1;

    SDL_Rect ch = {x__,y__,pixelSize,pixelSize};
    for (int y = 0;y < 8;y++)
    {
        for (int x = 0;x < 5;x++)
        {
            ch.x = x__ + (x * ch.w) + (padX * x);
            ch.y = y__ + (y * ch.h) + (padY * y);
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            SDL_RenderFillRect(renderer,&ch);
        }
    }
}

static int GetBit(uint8_t byte,int index)
{
    /*
    
    1. shift to the right
    Example: [INDEX 3] 0b11000 => 0b00011
    2. remove every other bit using AND Gate
    Example: 0b00011 & 1 => 0b00001
    ( NOTE : 1 in BIN => 0b00001 )

    */
    return (byte>>index) & 1;
}

static void DrawCharByte(SDL_Renderer* renderer, int x__,int y__,int pixelSize,uint8_t (bytes)[8])
{
    int padX = 1;
    int padY = 1;

    SDL_Rect ch = {x__,y__,pixelSize,pixelSize};
    for (int y = 0;y < 8;y++)
    {
        for (int x = 0;x < 5;x++)
        {
            ch.x = x__ + (x * ch.w) + (padX * x);
            ch.y = y__ + (y * ch.h) + (padY * y);
            SDL_SetRenderDrawColor(renderer,255,255,255,GetBit(bytes[y],5-x)*255);
            SDL_RenderFillRect(renderer,&ch);
        }
    }
}

void DrawScreen(SDL_Renderer* renderer,int posx,int posy,int SCharX,int SCharY)
{
    uint8_t testByte[8] = { 0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110, 0b00000 };
    int padX=10;
    int padY=10;
    int padBtwX=7;
    int padBtwY=10;
    int pixelSize=5;

    SDL_SetRenderDrawColor(renderer,8, 8, 252,255);
    SDL_Rect main_rect = {posx,posy,(((pixelSize * 5) + padBtwX)*SCharX)+(padX*2),(((pixelSize * 8) + padBtwY)*SCharY)+(padY*2)};
    SDL_RenderFillRect(renderer,&main_rect);
    for (int chY = 0;chY < SCharY;chY++)
    {
        for (int chX = 0;chX < SCharX;chX++)
        {
            DrawCharByte(renderer,(((pixelSize * 5) + padBtwX) * chX) + posx + padX,(((pixelSize * 8) + padBtwY) * chY) + posy + padY,pixelSize,testByte);
            //DrawCharArea(renderer,(((pixelSize * 5) + padBtwX) * chX) + posx + padX,(((pixelSize * 8) + padBtwY) * chY) + posy + padY,pixelSize);
        }
    }
    SDL_RenderPresent(renderer);
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
    DrawScreen(renderer,10,10,20,4);


    bool run_ = true;
    while (run_)
    {
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                run_ = false;
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}