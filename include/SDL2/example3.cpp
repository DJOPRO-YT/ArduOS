#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"
#include <cmath>
#include <iostream>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 400;

struct Joystick {
    SDL_FPoint center;
    float baseRadius;
    SDL_FPoint knobPos;
    float knobRadius;
    bool active = false;
};

float distance(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int w = -radius; w <= radius; ++w) {
        for (int h = -radius; h <= radius; ++h) {
            if (w*w + h*h <= radius*radius)
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
        }
    }
}

int main() {
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Virtual Joystick (Low CPU)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Enable VSync to avoid 100% CPU usage
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Joystick joy;
    joy.center = {100, WINDOW_HEIGHT - 100};
    joy.baseRadius = 60;
    joy.knobRadius = 25;
    joy.knobPos = joy.center;

    bool running = true;
    SDL_Event e;

    Uint32 lastFrame = SDL_GetTicks();
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (running) {
        // Wait up to 16ms for an event to reduce CPU load
        if (SDL_WaitEventTimeout(&e, frameDelay)) {
            if (e.type == SDL_QUIT)
                running = false;

            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                float mx = e.button.x;
                float my = e.button.y;
                if (distance(mx, my, joy.center.x, joy.center.y) <= joy.baseRadius)
                    joy.active = true;
            }

            else if (e.type == SDL_MOUSEBUTTONUP) {
                joy.active = false;
                joy.knobPos = joy.center;
            }

            else if (e.type == SDL_MOUSEMOTION && joy.active) {
                float mx = e.motion.x;
                float my = e.motion.y;
                float dx = mx - joy.center.x;
                float dy = my - joy.center.y;
                float dist = distance(mx, my, joy.center.x, joy.center.y);

                if (dist > joy.baseRadius) {
                    dx = dx / dist * joy.baseRadius;
                    dy = dy / dist * joy.baseRadius;
                }

                joy.knobPos.x = joy.center.x + dx;
                joy.knobPos.y = joy.center.y + dy;

                float normX = dx / joy.baseRadius;
                float normY = dy / joy.baseRadius;
                std::cout << "Joystick vector: (" << normX << ", " << normY << ")\r";
                std::flush(std::cout);
            }
        }

        // Frame rate limit
        Uint32 now = SDL_GetTicks();
        if (now - lastFrame < frameDelay)
            SDL_Delay(frameDelay - (now - lastFrame));
        lastFrame = now;

        // Render
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        drawCircle(renderer, (int)joy.center.x, (int)joy.center.y, (int)joy.baseRadius);

        SDL_SetRenderDrawColor(renderer, 180, 180, 255, 255);
        drawCircle(renderer, (int)joy.knobPos.x, (int)joy.knobPos.y, (int)joy.knobRadius);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
