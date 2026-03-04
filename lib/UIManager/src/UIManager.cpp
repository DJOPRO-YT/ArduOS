#include "UIManager.hpp"

// DEFINE THE EXTERNS
#ifdef REMAKE_328
LiquidCrystal_I2C lcd(0x27,20,4);
#elif defined(NATIVE)
LCDCHAR_SDL2 lcd;
#endif

#ifdef UISMEM_H
    UISMem_byte::_3D Memory(4,20,8);
    UISMem_byte::_2D MemoryScreen(8,8);
#else
uint8_t Memory[4][20][8];
uint8_t MemoryScreen[8][8];
#endif
int id_to_recover = 0;

#ifdef REMAKE_328
const uint8_t borders[6][8] PROGMEM = {
#elif defined(NATIVE)
uint8_t borders[6][8] = {
#endif
    {
        0b00000,
        0b00000,
        0b00000,
        0b11111,
        0b11111,
        0b00000,
        0b00000,
        0b00000
    },
    {
        0b01100,
        0b01100,
        0b01100,
        0b01100,
        0b01100,
        0b01100,
        0b01100,
        0b01100
    },
    {
        0b00000,
        0b00000,
        0b00000,
        0b01111,
        0b01111,
        0b01100,
        0b01100,
        0b01100
    },
    {
        0b00000,
        0b00000,
        0b00000,
        0b11100,
        0b11100,
        0b01100,
        0b01100,
        0b01100
    },
    {
        0b01100,
        0b01100,
        0b01100,
        0b01111,
        0b01111,
        0b00000,
        0b00000,
        0b00000
    },
    {
        0b01100,
        0b01100,
        0b01100,
        0b11100,
        0b11100,
        0b00000,
        0b00000,
        0b00000
    }
};

#ifdef REMAKE_328
const uint8_t icons[][8] PROGMEM = {
#elif defined(NATIVE)
uint8_t icons[][8] = {
#endif
    {
        0b00000,
	    0b00000,
	    0b00100,
	    0b01110,
	    0b11111,
	    0b00000,
	    0b00000,
	    0b00000
    },
    {
        0b00000,
	    0b00000,
    	0b11111,
	    0b01110,
    	0b00100,
	    0b00000,
	    0b00000,
	    0b00000
    }
};

// END AND BEGIN FUNCS

void UIManager::init()
{
    #ifdef REMAKE_328
    lcd.init();
    #endif
    lcd.backlight();

    #ifdef UISMEN_H
    UISMem::Init();
    #endif
}
#ifdef NATIVE
void UIManager::SDL2init(SDL_Renderer* renderer)
{
    lcd.init(renderer,10,20,20,4);
}
#endif
void UIManager::FullRefresh() {
    for (int line = 0;line < 4;line++) {
        for (int index = 0;index < 20;index++) {
            UIManager::Refresh(index,line);
        }
    }
}

void UIManager::Refresh(const int &index,const int &line)
{
    /*
        11101011 [EXAMPLE] -| AND
        11100000 [0xE0]    -| (&)
        ________
        11100000 [RESULT]
    */
    #ifdef UISMEM_H
    byte hi[8];
    foo(Memory[line][index],8,hi);
    if (!IsValueFalseArrayByte(hi) || (Memory[line][index][0] & 0xE0) == 0xE0)
    {
        int test_temp = findDuplicateRowPointer(MemoryScreen, 8);
        if (test_temp > 0)
        {
            memset(MemoryScreen[test_temp],0,8);
        }

        int __index__ = -1;
        for (size_t i = 0; i < 8; i++) {
            byte hi___[8];
            foo(MemoryScreen[i],8,hi___);

            if (MemoryScreen[i] && IfByteArraysAreSame(hi, hi___)) {
                __index__ = i;
                break;
            }
        }
    
    #else
    
    if (!IsValueFalseArrayByte(Memory[line][index]) || (Memory[line][index][0] & 0xE0) == 0xE0)
    {
        int test_temp = findDuplicateRow(MemoryScreen, 8);
        if (test_temp > 0)
        {
            memset(MemoryScreen[test_temp],0,8);
        }

        int __index__ = -1;
        for (size_t i = 0; i < 8; i++) {
            if (MemoryScreen[i] && IfByteArraysAreSame(Memory[line][index], MemoryScreen[i])) {
                __index__ = i;
                break;
            }
        }

    #endif
        if (__index__ == -1) {
            if (id_to_recover >= 8)
            {
                // OUT_OF_MEMORY
                //return;
                id_to_recover = 0;
            }

                /*
                for (int u = 0; u < 8;u++)
                {
                    MemoryScreen[id_to_recover][u] = Memory[line][index][u];
                }
                */
            memcpy(MemoryScreen[id_to_recover],Memory[line][index],8);

            lcd.createChar(id_to_recover, Memory[line][index]);
            lcd.setCursor(index,line);
            lcd.write(uint8_t(id_to_recover));
            id_to_recover += 1;
        }else{
            lcd.setCursor(index,line);
            lcd.write(uint8_t(__index__));
        }

    }
}

void UIManager::DrawPixel(int posX,int posY,int pixelX,int pixelY)
{
    posX = constrain(posX,1,20) - 1;
    posY = constrain(posY,1,4) - 1;
    pixelX = 4 - (constrain(pixelX,1,5) - 1);
    pixelY = constrain(pixelY,1,8) - 1;

    /*
        00010010 [EXAMPLE] -| AND
        00011111 [0x1F]    -| (&)
        ________
        00010010 [RESULT]
    */
    Memory[posY][posX][0] = Memory[posY][posX][0] & 0x1F;
    uint8_t temp__[8];
    foo(Memory[posY][posX],8,temp__);
    if (!IsValueFalseArrayByte(temp__))
    {

    for (size_t i = 0;i < 8;i++)
    {
        uint8_t temp__ABA[8];
        foo(MemoryScreen[i],8,temp__ABA);
        if (MemoryScreen[i] && IfByteArraysAreSame(temp__,temp__ABA))
        {
            for (int row = 0; row < 8; row++)
            {
                if (row == pixelY){
                    uint8_t temp_AAAAA = MemoryScreen[i][row];
                    temp_AAAAA |= 1 << pixelX;
                    MemoryScreen[i][row] = temp_AAAAA;
                }
                else
                {
                    MemoryScreen[i][row] = Memory[posY][posX][row];
                }
            }

            lcd.createChar(i,MemoryScreen[i]);
            break;
       }
    }
    
    }

    uint8_t temp_AAAAA = Memory[posY][posX][pixelY];
    temp_AAAAA |= 1 << pixelX;
    Memory[posY][posX][pixelY] = temp_AAAAA;

    UIManager::Refresh(posX,posY);
}

void UIManager::ErasePixel(int posX,int posY,int pixelX,int pixelY)
{
    posX = constrain(posX,1,20) - 1;
    posY = constrain(posY,1,4) - 1;
    pixelX = 4 - (constrain(pixelX,1,5) - 1);
    pixelY = constrain(pixelY,1,8) - 1;

    /*
        00010010 [EXAMPLE] -| AND
        00011111 [0x1F]    -| (&)
        ________
        00010010 [RESULT]
    */
    Memory[posY][posX][0] = Memory[posY][posX][0] & 0x1F;
    uint8_t temp__[8];
    foo(Memory[posY][posX],8,temp__);
    if (!IsValueFalseArrayByte(temp__))
    {

    for (size_t i = 0;i < 8;i++)
    {
        uint8_t temp__ABA[8];
        foo(MemoryScreen[i],8,temp__ABA);
        if (MemoryScreen[i] && IfByteArraysAreSame(temp__,temp__ABA))
        {
            for (int row = 0; row < 8; row++)
            {
                if (row == pixelY){
                    uint8_t temp_AAAA = MemoryScreen[i][row];
                    /*
                        0100 -- ~ ==> 1011    
                    */
                    temp_AAAA &= ~(1 << pixelX);
                    MemoryScreen[i][row] = temp_AAAA;
                }
                else
                {
                    MemoryScreen[i][row] = Memory[posY][posX][row];
                }
            }

            if (IsValueFalseArrayByte(temp__ABA))
            {
                for (int i_ = i;i_ <= id_to_recover;i_++)
                {
                    memcpy(MemoryScreen[i_],MemoryScreen[i_ + 1],8);
                }
                id_to_recover--;
                lcd.setCursor(posX,posY);
                lcd.print(" ");
                return;
            }else{
                lcd.createChar(i,MemoryScreen[i]);
                break;
            }
       }
    }
    
    }
    uint8_t temp_AAAAAA = Memory[posY][posX][pixelY];
    temp_AAAAAA &= ~(1 << pixelX);
    Memory[posY][posX][pixelY] = temp_AAAAAA;
    
    UIManager::Refresh(posX,posY);
}

void UIManager::PrintText(int posX,int posY,const char* text)
{
    //if (strlen(text) > (size_t)80 - (posY * 20 + posX)){return;}
    posX = constrain(posX,1,20) - 1;
    posY = constrain(posY,1,4) - 1;
    
    /*
    unused  LCD dis
    [000]   [00000]
    ^^^^^
    ALL 1 = a text
    ALL 0 = no text
    */

    lcd.setCursor(posX,posY);
    lcd.print(text);
    
    for (size_t i = 0;i < strlen(text);i++)
    {
        /*
        00010010 [EXAMPLE] -| OR
        11100000 [0xE0]    -| (|)
        ________
        11110010 [RESULT]
        */
        Memory[posY][posX + i][0] = Memory[posY][posX + i][0] | 0xE0;
    }
}

void UIManager::DrawCharacter(int posX,int posY,uint8_t (&char_)[8])
{
    posX = constrain(posX,1,20) - 1;
    posY = constrain(posY,1,4) - 1;
    /*
        00010010 [EXAMPLE] -| AND
        00011111 [0x1F]    -| (&)
        ________
        00010010 [RESULT]
    */
   
   memcpy(Memory[posY][posX],char_,8);

   UIManager::Refresh(posX,posY);
}
#ifdef REMAKE_328
void UIManager::DrawICO_P(int posX,int posY,const uint8_t progmem [2][3][8] PROGMEM)
{
    uint8_t buffer[8];
    for (int d1 = 0;d1 < 2;d1++)
    {
        for (int d2 = 0;d2 < 3;d2++)
        {
            memcpy_P(buffer,progmem[d1][d2],8);
            UIManager::DrawCharacter(posX + d2,posY + d1,buffer);
        }
    }
}
#elif defined(NATIVE)
void UIManager::DrawICO(int posX,int posY,const uint8_t progmem [2][3][8])
{
    uint8_t buffer[8];
    for (int d1 = 0;d1 < 2;d1++)
    {
        for (int d2 = 0;d2 < 3;d2++)
        {
            memcpy(buffer,progmem[d1][d2],8);
            UIManager::DrawCharacter(posX + d2,posY + d1,buffer);
        }
    }
}
#endif

void UIManager::ClearScreen() 
{
    UIManager::ResetScreen();
}

void UIManager::ResetScreen()
{
    memset(Memory,0,sizeof(Memory));
    memset(MemoryScreen,0,sizeof(MemoryScreen));
    lcd.clear();
    id_to_recover = 0;
}


void UIManager::ShowDialog(const char title[8],const char* text)
{
    uint8_t buffer[8];
    size_t len_title = strlen(title);
    size_t len_text = strlen(text);
    size_t d2 = add_ifdec(len_text / 18.0); 

    UIManager::ResetScreen();

    #ifdef REMAKE_328
    memcpy_P(buffer,borders[0],8);
    #elif defined(NATIVE)
    memcpy(buffer,borders[0],8);
    #endif
    for (int x = 2;x < 20;x++)
    {
        UIManager::DrawCharacter(x,4,buffer);
        UIManager::DrawCharacter(x,1,buffer);
    }

    #ifdef REMAKE_328
    memcpy_P(buffer,borders[1],8);
    #elif defined(NATIVE)
    memcpy(buffer,borders[1],8);
    #endif

    for (int x = 2;x < 4;x++)
    {
        UIManager::DrawCharacter(1,x,buffer);
        UIManager::DrawCharacter(20,x,buffer);
    }
    
    for (int i = 2;i < 6;i++)
    {
        #ifdef REMAKE_328
        memcpy_P(buffer,borders[i],8);
        #elif defined(NATIVE)
        memcpy(buffer,borders[i],8);
        #endif
        if (i==2)
        {
            UIManager::DrawCharacter(1,1,buffer);
        }else if (i==3)
        {
            UIManager::DrawCharacter(20,1,buffer);
        }
        else if (i==4)
        {
            UIManager::DrawCharacter(1,4,buffer);
        }else if (i==5)
        {
            UIManager::DrawCharacter(20,4,buffer);
        }
    }
    if (len_title%2 == 0) {
        UIManager::PrintText(11 - (len_title / 2),1,title);
        UIManager::PrintText(10 - (len_title / 2),1," ");
        UIManager::PrintText((11 - (len_title / 2)) + len_title,1," ");
    }else
    {
        UIManager::PrintText(10 - int(len_title / 2),1,title);
        UIManager::PrintText(9 - (len_title / 2),1," ");
        UIManager::PrintText((10 - (len_title / 2)) + len_title,1," ");
    }

    char text_s[d2][19];
    
    size_t choice = 0;
    for (size_t i = 0;i < d2;i++)
    {
        memcpy(text_s[i],&text[i * 18],18);
        for (size_t j = strlen(text_s[i]); j < 19; j++)
        {
            text_s[i][j] = ' ';
        }
        text_s[i][18] = '\0';
    }
    auto refresh_text = [](size_t choice, size_t d2, char text_s[][19]) {

        if (choice == (d2 - 1))
        {
            UIManager::PrintText(2,2,text_s[choice]);
            UIManager::PrintText(2,3," [Press Continue] ");
        }
        else
        {
            UIManager::PrintText(2,2,text_s[choice]);
            UIManager::PrintText(2,3,text_s[choice + 1]);
        }

    };

    refresh_text(choice,d2,text_s);
    
    while (true)
    {
        JoyStickPos pos = Controller::GetJPos();
        if (pos.y > 600)
        {
            if (choice > 0)
            {
                choice -= 1;
                refresh_text(choice,d2,text_s);
            }
        }else if(pos.y < 400)
        {
            if (choice < (d2 - 1))
            {
                choice += 1;
                refresh_text(choice,d2,text_s);
            }
        }
        if (Controller::IsBtnClicked())
        {
            UIManager::ClearScreen();
            break;
        }
        Sleep_for(100);
    }
    return;
}