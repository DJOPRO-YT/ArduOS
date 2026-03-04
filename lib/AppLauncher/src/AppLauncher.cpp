#include "AppLauncher.hpp"

void AppLauncher::Init()
{
    // Controllers
    hns.CPPFuncDec("GetJPosX",HNController::GetPosX);
    hns.CPPFuncDec("GetJPosY",HNController::GetPosY);
    hns.CPPFuncDec("IsBtnClicked",HNController::IsBtnClicked);

    // UI
    #ifdef REMAKE_328
    hns.CPPFuncDec("UIDrawPixel",HNUIManager::DrawPixel,"POSX,POSY,PIXELX,PIXELY");
    hns.CPPFuncDec("UIErasePixel",HNUIManager::ErasePixel,"POSX,POSY,PIXELX,PIXELY");
    hns.CPPFuncDec("UIPrintText",HNUIManager::PrintText,"POSX,POSY,TEXT");
    hns.CPPFuncDec("UIDrawCharacter",HNUIManager::PrintText,"POSX,POSY,CHARA,CHARB,CHARC,CHARD,CHARE,CHARF,CHARG,CHARH");
    #elif define(REMAKE_32)
    hns.CPPFuncDec("CreateLabel",HNLabel::CreateLabel); // -> ID_LBL
    hns.CPPFuncDec("LabelSetPosition",HNLabel::SetPosition,"ID,x,y");
    hns.CPPFuncDec("LabelSetText",HNLabel::SetText,"ID,TEXT");
    hns.CPPFuncDec("LabelSetVisibility",HNLabel::SetVisibility,"ID,BOOL");

    hns.CPPFuncDec("CreateButton",HNButton::CreateButton); // -> ID_LBL
    hns.CPPFuncDec("ButtonSetPosition",HNButton::SetPosition,"ID,x,y");
    hns.CPPFuncDec("ButtonSetText",HNButton::SetText,"ID,TEXT");
    hns.CPPFuncDec("ButtonSetVisibility",HNButton::SetVisibility,"ID,BOOL");
    hns.CPPFuncDec("ButtonConnect",HNButton::Connect);
    #endif
}

int AppLauncher::Run(const char* code)
{
    return hns.Run(code);
}