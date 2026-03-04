#include "ChLCD_SDL2.hpp"

#ifdef NATIVE

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

static void DrawCharArea(SDL_Renderer* renderer, int x__,int y__,int pixelSize,float padBtwPixels)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,30);

    SDL_Rect ch = {x__,y__,pixelSize,pixelSize};
    for (int y = 0;y < 8;y++)
    {
        for (int x = 0;x < 5;x++)
        {
            ch.x = x__ + (x * ch.w) + (padBtwPixels * x);
            ch.y = y__ + (y * ch.h) + (padBtwPixels * y);
            SDL_RenderFillRect(renderer,&ch);
        }
    }
}

static void DrawCharByte(SDL_Renderer* renderer, int x__,int y__,int pixelSize,float padBtwPixels,uint8_t (bytes)[8])
{
    SDL_Rect ch = {0,0,pixelSize,pixelSize};
    for (int y = 0;y < 8;y++)
    {
        for (int x = 0;x < 5;x++)
        {
            //std::cout << ch.x << " " << ch.y << " | " << x << " " << y << " | " << (int)bytes[y] << " " << GetBit(bytes[y],4-x) << std::endl;
            ch.x = x__ + (x * ch.w) + (padBtwPixels * x);
            ch.y = y__ + (y * ch.h) + (padBtwPixels * y);
            if (GetBit(bytes[y],4-x) == 1) {
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderFillRect(renderer,&ch);
            }else{
                SDL_SetRenderDrawColor(renderer,8, 8, 252,255); //Main Background color
                SDL_RenderFillRect(renderer,&ch);
                SDL_SetRenderDrawColor(renderer,255,255,255,30);
                SDL_RenderFillRect(renderer,&ch);
            }
        }
    }
}

void LCDCHAR_SDL2::init(SDL_Renderer* renderer_,int posx,int posy,int SCharX,int SCharY)
{
    this->renderer = renderer_;
    this->PosX = posx;
    this->PosY = posy;
    this->SizeCharX = SCharX;
    this->SizeCharY = SCharY;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //enable transparent mode RGBA
    SDL_SetRenderDrawColor(renderer,8, 8, 252,255); //Main Background color
    SDL_Rect main_rect = {posx,posy,(((pixelSize * 5) + padBtwX)*SCharX)+(padX*2),(((pixelSize * 8) + padBtwY)*SCharY)+(padY*2)};
    SDL_RenderFillRect(renderer,&main_rect);
    for (int chY = 0;chY < SCharY;chY++)
    {
        for (int chX = 0;chX < SCharX;chX++)
        {
            DrawCharArea(renderer,(((pixelSize * 5) + padBtwX) * chX) + posx + padX,(((pixelSize * 8) + padBtwY) * chY) + posy + padY,pixelSize,padBtwPixels);
        }
    }
    SDL_RenderPresent(renderer);
}

void LCDCHAR_SDL2::setCursor(int x,int y)
{
    this->CursorPosX = x;
    this->CursorPosY = y;
}

void LCDCHAR_SDL2::print(const char* string)
{
    for (int index = 0;index < SDL_strlen(string);index++)
    {
        if (((int)string[index])-32 >= 0 && ((int)string[index])-32 <= sizeof(BasicChars) / 8)
        {
            DrawCharByte(this->renderer,(((pixelSize * 5) + padBtwX) * CursorPosX) + PosX + padX,(((pixelSize * 8) + padBtwY) * CursorPosY) + PosY + padY,pixelSize,padBtwPixels,BasicChars[((int)string[index])-32]);
            CursorPosX++;
        }
    }
    SDL_RenderPresent(renderer);
}

void LCDCHAR_SDL2::createChar(int index,uint8_t (byte)[8])
{
    if (index >= 0 && index < 8)
    {
        SDL_memcpy(Mem[index],byte,8);
    }
}

void LCDCHAR_SDL2::write(uint8_t byte)
{
    if (byte >= 0 && byte < 8)
    {
        DrawCharByte(this->renderer,(((pixelSize * 5) + padBtwX) * CursorPosX) + PosX + padX,(((pixelSize * 8) + padBtwY) * CursorPosY) + PosY + padY,pixelSize,padBtwPixels,Mem[(int)byte]);
        CursorPosX++;
    }
    SDL_RenderPresent(renderer);
}

void LCDCHAR_SDL2::backlight()
{
    return;
}

void LCDCHAR_SDL2::clear() {
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 20;j++)
        {
            LCDCHAR_SDL2::setCursor(j,i);
            LCDCHAR_SDL2::print(" ");
        }
    }
}
#endif