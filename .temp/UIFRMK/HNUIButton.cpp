#include "HNUIButton.hpp"

const char* HNButton::CreateButton(const char* args)
{
    UI::Button lbl_temp(0,0,"");
    btns[btn] = lbl_temp;
    btn += 1;
    char* hiiiiii;
    itoa(btn - 1,hiiiiii,10);
    return hiiiiii;
}

const char* HNButton::SetPosition(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");

    if (args_ != NULL)
    {
        size_t index_obj = atoi(args_);
        args_ = strtok(NULL,",");
        if (args_ != NULL)
        {
            size_t posX = atoi(args_);
            args_ = strtok(NULL,",");
            if (args_ != NULL)
            {
                btns[index_obj].SetPosition(posX,atoi(args_));
            }
        }
    }
    free(args_non_constent);
    return "";
}

const char* HNButton::SetText(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");

    if (args_ != NULL)
    {
        size_t index_obj = atoi(args_);
        args_ = strtok(NULL,",");
        if (args_ != NULL)
        {
            btns[index_obj].SetText(args_);
        }
    }
    free(args_non_constent);
    return "";
}

const char* HNButton::SetVisibility(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");

    if (args_ != NULL)
    {
        size_t index_obj = atoi(args_);
        args_ = strtok(NULL,",");
        if (args_ != NULL)
        {
            if (strcmp(args_,"true") == 0)
            {
                btns[index_obj].SetVisibility(true);
            }else if (strcmp(args_,"false") == 0)
            {
                btns[index_obj].SetVisibility(false);
            }
        }
    }
    free(args_non_constent);
    return "";
}

const char* HNButton::Connect(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");

    if (args_ != NULL)
    {
        size_t index_obj = atoi(args_);
        args_ = strtok(NULL,",");
        if (args_ != NULL)
        {
           // btns[index_obj].Connect(); /////////
        }
    }
    free(args_non_constent);
    return "";
}