#include "UIFramework.hpp"

UIManager UI::main_ui;
Controller UI::control;
UI::UIControl_btn UI::btns[5];
int UI::btns_index;

void UI::init() {main_ui.init();btns_index = -1;}
void UI::Activate_UI_Control()
{
    if (btns_index == -1){return;}

    int index_select = 0;
    bool run_UIControll = true;

    UI::Label c1(0,0,"[");
    UI::Label c2(0,0,"]");
    c1.SetVisibility(false);
    c2.SetVisibility(false);
    void (*func)() = nullptr;
    while (run_UIControll)
    {

        index_select = constrain(index_select,0,btns_index);
        while (!btns[index_select].clickable) 
        {
            if (index_select >= btns_index)
            {
                while (!btns[index_select].clickable)
                {
                    if (index_select <= 0){return;}
                    index_select--;
                    index_select = constrain(index_select,0,btns_index);
                }
                break;
            }
            index_select++;
            index_select = constrain(index_select,0,btns_index);
        }

        if (btns[index_select].type_btn < 2) 
        {
            c1.SetPosition(btns[index_select].pos.x - 1,btns[index_select].pos.y);
            
            if (btns[index_select].type_btn == 0) {
                c2.SetPosition(btns[index_select].pos.x + btns[index_select].text.length(),btns[index_select].pos.y);
            }else{
                c2.SetPosition(btns[index_select].pos.x + btns[index_select].Rows,btns[index_select].pos.y);
            }
        }
        else if(btns[index_select].type_btn == 2)
        {
            String spaces = "";
            for (int i = 0;i < btns[index_select].Rows; i++) {
                spaces += ' ';
            }
            UI::main_ui.PrintText(btns[index_select].pos.x,btns[index_select].pos.y,spaces);
            for (int i = 0;i < btns[index_select].Rows; i++)
            {
                UI::main_ui.DrawCharacter(btns[index_select].pos.x + i,btns[index_select].pos.y,btns[index_select].Selection_chars[i]);
            }
        }

        while (1)
        {
        if (control.IsBtnClicked())
        {
            int tick = millis();
            while (1)
            {

                if (!control.IsBtnClicked())
                {
                    //selected item

                    func = btns[index_select].func;
                    break;

                }
                else if((int)millis() - tick >= delay_ms_disable)
                {
                    break;
                }
                delay(100);
            }
           
            if (btns[index_select].type_btn == 2)
            {
                String spaces = "";
                for (int i = 0;i < btns[index_select].Rows; i++) {
                    spaces += ' ';
                }
                UI::main_ui.PrintText(btns[index_select].pos.x,btns[index_select].pos.y,spaces);
                for (int i = 0;i < btns[index_select].Rows; i++)
                {
                    UI::main_ui.DrawCharacter(btns[index_select].pos.x + i,btns[index_select].pos.y,btns[index_select].Normal_chars[i]);
                }
            }
            run_UIControll = false;
            break;
        }

        if(control.GetJPos().x > 800)
        {
            if (btns[index_select].type_btn == 2)
            {
                String spaces = "";
                for (int i = 0;i < btns[index_select].Rows; i++) {
                    spaces += ' ';
                }
                UI::main_ui.PrintText(btns[index_select].pos.x,btns[index_select].pos.y,spaces);
                for (int i = 0;i < btns[index_select].Rows; i++)
                {
                    UI::main_ui.DrawCharacter(btns[index_select].pos.x + i,btns[index_select].pos.y,btns[index_select].Normal_chars[i]);
                }
            }
            index_select++;
            break;
        }else if(control.GetJPos().x < 300)
        {
            if (btns[index_select].type_btn == 2)
            {
                String spaces = "";
                for (int i = 0;i < btns[index_select].Rows; i++) {
                    spaces += ' ';
                }
                UI::main_ui.PrintText(btns[index_select].pos.x,btns[index_select].pos.y,spaces);
                for (int i = 0;i < btns[index_select].Rows; i++)
                {
                    UI::main_ui.DrawCharacter(btns[index_select].pos.x + i,btns[index_select].pos.y,btns[index_select].Normal_chars[i]);
                }
            }
            index_select--;
            break;
        }
        delay(100);
        }
    }
    c1.SetVisibility(false);
    c2.SetVisibility(false);
    if (func != nullptr){func();}
}

// LABEL FRAMEWORK
#define LABEL_FRK UI::Label

LABEL_FRK::Label() : text("")
{
    this->pos.x = 1;
    this->pos.y = 1;
    UI::main_ui.PrintText(1,1,"");
}

LABEL_FRK::Label(const int &X,const int &Y,const String &text) : text(text)
{
    this->pos.x = X;
    this->pos.y = Y;
    UI::main_ui.PrintText(X,Y,text);
}

void LABEL_FRK::SetPosition(const int &X,const int &Y)
{
    String spaces = "";
    for (size_t i = 0; i < this->text.length(); i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText(this->pos.x,this->pos.y,spaces);
    UI::main_ui.PrintText(X,Y,text);
    this->pos.x = X;
    this->pos.y = Y;
}

void LABEL_FRK::SetText(const String &text)
{
    String spaces = "";
    for (size_t i = 0; i < this->text.length(); i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText(this->pos.x,this->pos.y,spaces);
    UI::main_ui.PrintText(this->pos.x,this->pos.y,text);
    this->text=text;
}

void LABEL_FRK::SetVisibility(const bool &vis)
{
    if (!vis)
    {
        String spaces = "";
        for (size_t i = 0; i < this->text.length(); i++) {
            spaces += ' ';
        }
        UI::main_ui.PrintText(this->pos.x,this->pos.y,spaces);
    }
    else
    {
        UI::main_ui.PrintText(this->pos.x,this->pos.y,text);
    }
    this->vis = vis;
}

void LABEL_FRK::AddCharToText(const char Char_)
{
    String spaces = "";
    for (size_t i = 0; i < this->text.length(); i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText(this->pos.x,this->pos.y,spaces);
    this->text+=Char_;
    UI::main_ui.PrintText(this->pos.x,this->pos.y,this->text);
}
// BUTTON FRAMEWORK
#define BUTTON_FRK UI::Button

BUTTON_FRK::Button()
{
    int X = 1;
    int Y = 1;
    String text = "";
    
    UIControl_btn hi;
    hi.pos = Position{X,Y};
    UI::main_ui.PrintText(X,Y,text);

    hi.type_btn = 0;
    hi.text = text;

    btns[++btns_index] = hi;
    this->btn_addrs = &btns[btns_index];
    this->index = btns_index;

}

BUTTON_FRK::Button(const int &X,const int &Y,const String &text)
{
    UIControl_btn hi;
    hi.pos = Position{X,Y};
    UI::main_ui.PrintText(X,Y,text);

    hi.type_btn = 0;
    hi.text = text;

    btns[++btns_index] = hi;
    this->btn_addrs = &btns[btns_index];
    this->index = btns_index;

}

void BUTTON_FRK::SetPosition(const int &X,const int &Y)
{
    String spaces = "";
    for (size_t i = 0;i < (*btn_addrs).text.length(); i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);
    UI::main_ui.PrintText(X,Y,(*btn_addrs).text);
    (*btn_addrs).pos.x = X;
    (*btn_addrs).pos.y = Y;
}

void BUTTON_FRK::SetText(const String &text)
{
    String spaces = "";
    for (size_t i = 0;i < (*btn_addrs).text.length(); i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);
    UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.x,text);
    btn_addrs->text=text;
}

void BUTTON_FRK::SetVisibility(const bool &vis)
{
    if (!vis)
    {
        String spaces = "";
        for (int i = 0;i < (*btn_addrs).Rows; i++) {
            spaces += ' ';
        }
        UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);
    }
    else
    {
        UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,(*btn_addrs).text);
    }
    (*btn_addrs).visible = vis;
}

void BUTTON_FRK::Connect(void (*func)())
{
    (*btn_addrs).func = func;
    (*btn_addrs).clickable = true;
}

void BUTTON_FRK::Disconnect()
{
    (*btn_addrs).clickable = false;
}

void BUTTON_FRK::Delete()
{
    for (int i_ = index; i_ <= btns_index; i_++) {
        btns[i_] = btns[i_ + 1];
    }
    btns_index--;
}

// CBUTTON FRAMEWORK
#define CBUTTON_FRK UI::CButton

CBUTTON_FRK::CButton(const int &X,const int &Y,byte char_[10][8],int Rows)
{
    UIControl_btn hi;
    hi.Rows = Rows;

    hi.pos = Position{X,Y};

    btns[++btns_index] = hi;
    this->btn_addrs = &btns[btns_index];
    this->index = btns_index;

    for (int i = 0;i < Rows; i++)
    {   
        for (int iii = 0;iii < 8;iii++)
        {
            btn_addrs->Normal_chars[i][iii] = char_[i][iii];
        } //memcpy corrumpt the data (sometimes)
        UI::main_ui.DrawCharacter(X + i,Y,char_[i]);
    }
}

void CBUTTON_FRK::SetPosition(const int &X,const int &Y)
{
    String spaces = "";
    for (int i = 0;i < (*btn_addrs).Rows; i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);

    for (int i = 0;i < (*btn_addrs).Rows; i++)
    {   
        UI::main_ui.DrawCharacter(X + i,Y,(*btn_addrs).Normal_chars[i]);
    }
    (*btn_addrs).pos.x = X;
    (*btn_addrs).pos.y = Y;
}

void CBUTTON_FRK::SetCharacter(byte char_[10][8],int Rows)
{
    String spaces = "";
    for (int i = 0;i < (*btn_addrs).Rows; i++) {
        spaces += ' ';
    }
    UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);
    (*btn_addrs).Rows=Rows;
    for (int i = 0;i < Rows; i++)
    {
        memcpy((*btn_addrs).Normal_chars[i],char_[i],8);
        UI::main_ui.DrawCharacter((*btn_addrs).pos.x + i,(*btn_addrs).pos.y,char_[i]);
    }
}

void CBUTTON_FRK::SetVisibility(const bool &vis)
{
    if (!vis)
    {
        String spaces = "";
        for (int i = 0;i < (*btn_addrs).Rows; i++) {
            spaces += ' ';
        }
        UI::main_ui.PrintText((*btn_addrs).pos.x,(*btn_addrs).pos.y,spaces);
    }
    else
    {
        for (int i = 0;i < (*btn_addrs).Rows; i++)
        {
        UI::main_ui.DrawCharacter((*btn_addrs).pos.x + i,(*btn_addrs).pos.y,(*btn_addrs).Normal_chars[i]);
        }
    }
    (*btn_addrs).visible = vis;
}

void CBUTTON_FRK::Connect(void (*func)(),bool custom_selection,byte char_[10][8])
{

    if (!custom_selection){(*btn_addrs).type_btn = 1;}
    else
    {
        (*btn_addrs).type_btn = 2;
        for (int i = 0;i < (*btn_addrs).Rows; i++)
        {
            for (int iii = 0;iii < 8;iii++)
            {
                btn_addrs->Selection_chars[i][iii] = char_[i][iii];
            }
        }
    }

    (*btn_addrs).func = func;
    (*btn_addrs).clickable = true;
}

void CBUTTON_FRK::Disconnect()
{
    (*btn_addrs).clickable = false;
}

void CBUTTON_FRK::Delete()
{
    for (int i_ = index; i_ <= btns_index; i_++) {
        btns[i_] = btns[i_ + 1];
    }
    btns_index--;
}

// CBUTTON FRAMEWORK
#define CANVAS_FRK UI::Canvas

CANVAS_FRK::Canvas(const int &X,const int &Y,const int &SizeX, const int &SizeY)
{
    this->pos.x = X;
    this->pos.y = Y;
    this->pos.size_x = SizeX;
    this->pos.size_y = SizeY;
}

void CANVAS_FRK::DrawPixel(int posX,int posY,int pixelX,int pixelY)
{
    pixelX = constrain(pixelX,1, 5);
    pixelY = constrain(pixelY,1, 8);
    posX = constrain(posX,1,pos.size_x);
    posY = constrain(posY,1,pos.size_y);

    UI::main_ui.DrawPixel(posX + (pos.x - 1),posY + (pos.y - 1),pixelX,pixelY);
}

void CANVAS_FRK::ErasePixel(int posX,int posY,int pixelX,int pixelY)
{
    pixelX = constrain(pixelX,1, 5);
    pixelY = constrain(pixelY,1, 8);
    posX = constrain(posX,1,pos.size_x);
    posY = constrain(posY,1,pos.size_y);

    UI::main_ui.ErasePixel(posX + (pos.x - 1),posY + (pos.y - 1),pixelX,pixelY);
}

void CANVAS_FRK::DrawCharacter(int posX,int posY,byte (&char_)[8])
{
    posX = constrain(posX,1,pos.size_x);
    posY = constrain(posY,1,pos.size_y * 8);
    
    UI::main_ui.DrawCharacter(posX + (pos.x - 1),posY + (pos.y - 1),char_);
}

void CANVAS_FRK::EraseCharacter(int posX,int posY)
{
    posX = constrain(posX,1,pos.size_x);
    posY = constrain(posY,1,pos.size_y * 8);
    
    UI::main_ui.PrintText(posX + (pos.x - 1),posY + (pos.y - 1)," ");
}

// INPUT FRAMEWORK
#define INPUT_FRK UI::Input

INPUT_FRK::Input() {direct_input = false;}

const String INPUT_FRK::GetInput()
{
    for (int i = 0; i <3; i++)
    {
        for (int btn_i = 1;btn_i <= 9;btn_i++)
        {
            if (i == 2 && btn_i == 9){
                byte arrw[2][8] = {
                    {
                        0b00000,
                        0b01100,
                        0b01100,
                        0b01111,
                        0b00111,
                        0b00000,
                        0b00000,
                        0b00000,
                    },
                    {
                        0b00000,
                        0b01100,
                        0b00110,
                        0b11111,
                        0b11111,
                        0b00110,
                        0b01100,
                        0b00000,
                    }
                };
                 
                UI::CButton btn(btn_i * 2,i + 2,arrw,2);
            }else{
                UI::Button btn(btn_i * 2,i + 2,K_MODEA[i][btn_i - 1]);
                btn.Connect([]{});
            }
        }
    }
    
    UI ui;
    ui.Activate_UI_Control();
    return "";
}