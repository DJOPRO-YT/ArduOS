#include <UIManager.hpp>
#include <Controller.hpp>
#include <System.hpp>
#include <Utils.hpp>
//#include <FileSystem.hpp>

// SystemApps
#include <AppHome.hpp>
// End
#ifdef REMAKE_328
#include <Arduino.h>
#elif defined(NATIVE)
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <thread>
#include <string>

int random2_(int a, int b) {
    return a + rand() % (b - a);
}

int random1_(int a) {
    return rand() % a;
}

#define random(...) _random_selector(__VA_ARGS__, random2_, random1_)(__VA_ARGS__)

#define _random_selector(_1,_2,NAME,...) NAME
#endif

void intro() {
  uint8_t fr[3][8] = {{
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
},
{
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
},
{
  0b00000,
  0b10001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b00000,
}};

for (int _ = 0; _ < random(6,20);_++)
{
  int X = random(20);
  int Y = random(4);

  for (int i = 0;i < 3;i++)
  {
    UIManager::DrawCharacter(X,Y,fr[i]);
    Sleep_for(100);
  }
  UIManager::PrintText(X,Y," ");
}
const char* name = "Ardu-Console";
for (size_t i = 0; i < strlen(name);i++) 
{
  UIManager::PrintText(5 + i,2,&name[i]);
  Sleep_for(100);
}

uint8_t fr1[6][8]
{{
	0b11111,
	0b11111,
	0b10001,
	0b10101,
	0b10011,
	0b10101,
	0b10101,
	0b11111
},
{
	0b11111,
	0b11111,
	0b10001,
	0b10111,
	0b10001,
	0b10111,
	0b10001,
	0b11111
},
{
	0b11111,
	0b11111,
	0b10101,
	0b10001,
	0b10101,
	0b10101,
	0b10101,
	0b11111
},
{
	0b11111,
	0b11111,
	0b10001,
	0b10101,
	0b10001,
	0b10101,
	0b10101,
	0b11111
},
{
	0b11111,
	0b11111,
	0b10101,
	0b10011,
	0b10111,
	0b10011,
	0b10101,
	0b11111
},
{
	0b11111,
	0b11111,
	0b10001,
	0b10111,
	0b10001,
	0b10111,
	0b10001,
	0b11111
}};

for (size_t i = 0; i < 6;i++) 
{
  UIManager::DrawCharacter(11 + i,3,fr1[i]);
  Sleep_for(random(201));
}

uint8_t fr2[2][8] = {
	{
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000
	},
	{
	0b00000,
	0b00000,
	0b00100,
	0b01110,
	0b00100,
	0b00000,
	0b00000,
	0b00000
	}
};

for (int side = 0; side < 2;side++){
	for (int _ = 0; _ < random(1,11);_++)
	{
		if (side == 0) {
			UIManager::DrawCharacter(random(1,4),random(1,4),fr2[random(0,2)]);
		}
		else
		{
			UIManager::DrawCharacter(random(18,21),random(1,4),fr2[random(0,2)]);
		}
	}
}
Sleep_for(100);

}

int main()
{
	// INIT 
	#ifdef REMAKE_328
	init();
	UIManager::init();
	#elif defined(NATIVE)
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 1;
	}
	std::string title__ = std::string("ArduOS ") + PrettyARDUOSv;
	SDL_Window* win = SDL_CreateWindow(title__.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,580,600,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	SDL_RenderClear(renderer);
	UIManager::SDL2init(renderer);
	Controller::SetEnable(false);
	Controller::SDL2init(renderer);
	#endif
	//MAIN CODE
	Controller::Init();
	System::InitSysPins();
	//FileSystem::init();

	intro();
	#ifdef NATIVE
	std::thread t_main(HomeApp::Launch/*,win*/,renderer);
	t_main.detach();//.join();
	//HomeApp::Launch(win,renderer);
	Controller::SetEnable(true);

	#elif defined(REMAKE_328)
	HomeApp::Launch();
	#endif

	// SDL2 HANDLER
	#ifdef NATIVE
	SDL_Event events;
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
	#endif

	return 0;
}