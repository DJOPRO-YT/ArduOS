#include "HNController.hpp"

void HNController::init(){}

const char* HNController::GetPosX(const char* args)
{
    char out[4];
    itoa(cons.GetJPos().x,out,10);
    return out; 
}
const char* HNController::GetPosY(const char* args)
{
    char out[4];
    itoa(cons.GetJPos().y,out,10);
    return out; 
}
const char* HNController::IsBtnClicked(const char* args)
{
    if (cons.IsBtnClicked()){
        return "true"; 
    }
    else
    {
        return "false";
    }
}