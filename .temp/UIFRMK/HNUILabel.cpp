#include "HNUILabel.hpp"

const char* HNLabel::CreateLabel(const char* args)
{
    UI::Label lbl_temp(0,0,"");
    lbls[lbl] = lbl_temp;
    lbl += 1;
    char* hiiiiii;
    itoa(lbl - 1,hiiiiii,10);
    return hiiiiii;
}

const char* HNLabel::SetPosition(const char* args)
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
                lbls[index_obj].SetPosition(posX,atoi(args_));
            }
        }
    }
    free(args_non_constent);
    return "";
}

const char* HNLabel::SetText(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");

    if (args_ != NULL)
    {
        size_t index_obj = atoi(args_);
        args_ = strtok(NULL,",");
        if (args_ != NULL)
        {
            lbls[index_obj].SetText(args_);
        }
    }
    free(args_non_constent);
    return "";
}

const char* HNLabel::SetVisibility(const char* args)
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
                lbls[index_obj].SetVisibility(true);
            }else if (strcmp(args_,"false") == 0)
            {
                lbls[index_obj].SetVisibility(false);
            }
        }
    }
    free(args_non_constent);
    return "";
}