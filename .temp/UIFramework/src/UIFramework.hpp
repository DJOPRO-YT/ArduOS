#ifndef UI_FRAMEWORK_H
#define UI_FRAMEWORK_H

#include <Arduino.h>
#include <UIManager.hpp>
#include <Controller.hpp>
#include <System.hpp>
#include "KLayout.hpp"
class UI 
{
private:
    static UIManager main_ui;
    static Controller control;
    static int btns_index;

    struct Position2 {int x;int y;int size_x;int size_y;};
    struct Position {
        int x;
        int y;
    };
    struct UIControl_btn
    {
        int type_btn = 0; //0: Normal /1: Custom /2:Custom With Custom Selection
        bool clickable = false;
        bool visible = true;
        String text;
        byte Selection_chars[2][8];
        byte Normal_chars[2][8];
        int Rows;
        Position pos;
        void (*func)();
    };
    static UIControl_btn btns[5];

public:
    static const int WIDTH = 20;
    static const int HEIGHT = 4;
    int delay_ms_disable = 1000;

    void init();
    void Activate_UI_Control();

    class Label {
    private:
        Position pos;
        String text;
        bool vis = false;
    public:
        Label();
        Label(const int &X,const int &Y,const String &text);
        
        void SetPosition(const int &X,const int &Y);
        void SetText(const String &text);
        void AddCharToText(const char Char_);
        void SetVisibility(const bool &vis);
    };

    class Button {
    private:
        UIControl_btn *btn_addrs;
        int index;
    public:
        Button();
        Button(const int &X,const int &Y,const String &text);
        
        void SetPosition(const int &X,const int &Y);
        void SetText(const String &text);
        void SetVisibility(const bool &vis);
        void Connect(void (*func)());
        void Disconnect();
        void Delete();
    };

    class CButton {
    private:
        UIControl_btn *btn_addrs;
        int index;
    public:
        CButton(const int &X,const int &Y,byte char_[10][8],int Rows);
        
        void SetPosition(const int &X,const int &Y);
        void SetCharacter(byte char_[10][8],int Rows);
        void SetVisibility(const bool &vis);
        void Connect(void (*func)(),bool custom_selection = false,byte char_[10][8] = nullptr);
        void Disconnect();
        void Delete();
    };

    class Canvas {
    private:
        Position2 pos;
    public:
        Canvas(const int &X,const int &Y,const int &SizeX, const int &SizeY);
        
        void DrawPixel(int posX,int posY,int pixelX,int pixelY);
        void ErasePixel(int posX,int posY,int pixelX,int pixelY);
        void DrawCharacter(int posX,int posY,byte (&char_)[8]);
        void EraseCharacter(int posX,int posY);
    };

    class Input {
    private:
        bool direct_input = false;
    public:
        Input();
        const String GetInput();
        void DirectInputOff();
        void DirectInputOn();

    };
};


#endif