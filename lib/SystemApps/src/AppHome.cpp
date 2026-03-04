#include "AppHome.hpp"
int last_chrg = -1;
int last_min = -1;
bool wascharg = false;

typedef void (*launchapp)(void);

typedef struct
{
    char nameapp[10];
    launchapp app;
    int id_ico;
} Launcher;

uint8_t btr[8] = {
        0b01110,
	    0b11111,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b11111
};

void UpdateTopbar()
{
    // Battery Shower
    if (System::IsCharging()) {
        if (!wascharg) {
            UIManager::PrintText(16,1,"---%");
            for (int i = 1; i <= 5; i++)
            {  
                for (int temp = 1;temp <= 3;temp++)
                {
                    UIManager::DrawPixel(20,1,temp + 1,8-i);
                }
                    
            }
            UIManager::ErasePixel(20,1,4,3);
            UIManager::ErasePixel(20,1,3,4);
            UIManager::ErasePixel(20,1,4,5);
            UIManager::ErasePixel(20,1,3,6);
            wascharg = true;
        }
    } else {
        wascharg = false;
        int chrg = System::GetChargPercent();
        chrg = abs(chrg);
        int level = map(chrg,0,100,1,5);

        if (chrg != last_chrg) {

            for (int i = 1; i <= 5; i++)
            {
                
                for (int temp = 1;temp <= 3;temp++)
                {
                    if (i <= level) {
                        UIManager::DrawPixel(20,1,temp + 1,8-i);
                    }
                    else
                    {
                        UIManager::ErasePixel(20,1,temp + 1,8-i);
                    }
                }
                
            }

            UIManager::PrintText(16,1,"   ");
            char chrg_c_str[5];
            itoa(chrg,chrg_c_str,10);
            
            strcat(chrg_c_str,"%");

            if (chrg >= 100)
            {
                UIManager::PrintText(16,1,chrg_c_str);
            }else if(chrg >= 10){
                UIManager::PrintText(17,1,chrg_c_str);
            }else{
                UIManager::PrintText(18,1,chrg_c_str);
            }
            last_chrg = chrg;
        }
    }
    System::DateTime tm = System::GetTime();
    if (last_min != tm.MINUTES){
        UIManager::PrintText(1,1,TimeFormater(tm.HOUR,tm.MINUTES,255));
        last_min=tm.MINUTES;
    }
}

int item = 0;
int last_item = -1;
Launcher items[] = {
    #ifdef REMAKE_328
    {"Module",Module::Launch,0},
    #endif
    {"Settings",SettingsApp::Launch,1}
};

void UpdateMiddleSection()
{
    int nbitems = sizeof(items) / sizeof(items[0]);

    if (nbitems > item)
    {
        if (item != last_item) {
            UIManager::ClearScreen();

            #ifdef REMAKE_328
            UIManager::DrawICO_P(9,2,ICOs[items[item].id_ico]);
            #elif defined(NATIVE)
            UIManager::DrawICO(9,2,ICOs[items[item].id_ico]);
            #endif

            if (item > 0)
            {
                UIManager::PrintText(2,3,"<");
            }
            if(item < (nbitems - 1))
            {
                UIManager::PrintText(19,3,">");
            }

            UIManager::PrintText(10 - (strlen(items[item].nameapp) / 2),4,items[item].nameapp);
            last_item = item;
            last_chrg = -1;
            last_min = -1;
            wascharg = false;
            UIManager::DrawCharacter(20,1,btr);
        }
    }
    else
    {
        item = nbitems - 1;
    }
    
    if (Controller::IsBtnClicked())
    {
        last_chrg = -1;
        last_min = -1;
        last_item = -1;
        wascharg = !wascharg;
        items[item].app();
        /*
        switch (item) {
            
            
            case 0: //Module
            #ifdef REMAKE_328
                if (Module::IsConnected())
                {
                    Module::Start();
                }
                else
                {
                    UIManager::ShowDialog("Error","No Module is connected.");
                }
                break;
            #elif defined(NATIVE)
            UIManager::ShowDialog("Error","Module not supported.");
            #endif
            return;
        }
        */
    }
    JoyStickPos pospos = Controller::GetJPos();

    if (pospos.x < 400)
    {
        if (item < nbitems)
        {
            item += 1;
        }
    }else if (pospos.x > 600)
    {
        if (item > 0){
            item -= 1;
        }
    }

}

#ifdef NATIVE
void HomeApp::Launch(/*SDL_Window* win,*/SDL_Renderer* renderer)
#else
void HomeApp::Launch()
#endif
{
    UIManager::ClearScreen();
    UIManager::DrawCharacter(20,1,btr);
    #ifdef REMAKE_328
    bool aa = Module::Connect();
    if (aa)
    {
        int len = strlen(Module::GetModuleInfos().name);
        strncpy(items[0].nameapp,Module::GetModuleInfos().name,9);
        if (len >= 10){
            items[0].nameapp[9] = '\0';
        }else if (len < 10){
            items[0].nameapp[len] = '\0';
        }
    }
    #endif

    while (1)
    {
        #ifdef NATIVE
        if (!renderer) {break;}
        
        #endif

        UpdateTopbar();
        UpdateMiddleSection();
    }
    
}