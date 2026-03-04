#include "Controller.hpp"

#ifdef NATIVE
void Controller::SDL2init(SDL_Renderer* renderer_)
{
    thread t1(JoyStick::SDL2init,renderer_);
    t1.detach();
    //JoyStick::SDL2init(renderer_);
}
#endif

void Controller::Init()
{
    #ifdef REMAKE_328
    pinMode(JOY_BTN,INPUT_PULLUP);
    #endif
}

JoyStickPos Controller::GetJPos()
{
    #ifdef NATIVE
    return {JoyStick::GetPosX(),JoyStick::GetPosY()};
    #elif defined(REMAKE_328)
    return {analogRead(VRX_PIN),analogRead(VRY_PIN)};
    #endif
}

bool Controller::IsBtnClicked()
{
    #ifdef NATIVE
    return JoyStick::isClicked();
    #elif defined(REMAKE_328)
    return !digitalRead(JOY_BTN);
    #endif
}

#ifdef NATIVE
void Controller::SetEnable(bool enable)
{
    JoyStick::SetEnable(enable);
}
#endif