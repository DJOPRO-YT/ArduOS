#include "HNUIManager.hpp"

const char* HNUIManager::DrawPixel(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");
    char* list_args[4];
    for (int _ = 0; _ < 4;_++)
    {
        if (args_ != NULL)
        {
            list_args[_] = args_;
            args_ = strtok(NULL,",");
        }
        else
        {
            break;
        }
    }

    if (list_args[0] && list_args[1] && list_args[2] && list_args[3])
    {
        UIManager::DrawPixel(atoi(list_args[0]),atoi(list_args[1]),atoi(list_args[2]),atoi(list_args[3]));
    }

    free(args_non_constent);
    return "";
}

const char* HNUIManager::ErasePixel(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");
    char* list_args[4];
    for (int _ = 0; _ < 4;_++)
    {
        if (args_ != NULL)
        {
            list_args[_] = args_;
            args_ = strtok(NULL,",");
        }
        else
        {
            break;
        }
    }

    if (list_args[0] && list_args[1] && list_args[2] && list_args[3])
    {
        UIManager::ErasePixel(atoi(list_args[0]),atoi(list_args[1]),atoi(list_args[2]),atoi(list_args[3]));
    }
    
    free(args_non_constent);
    return "";
}

const char* HNUIManager::PrintText(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");
    char* list_args[3];
    for (int _ = 0; _ < 3;_++)
    {
        if (args_ != NULL)
        {
            list_args[_] = args_;
            args_ = strtok(NULL,",");
        }
        else
        {
            break;
        }
    }

    if (list_args[0] && list_args[1] && list_args[2])
    {
        UIManager::PrintText(atoi(list_args[0]),atoi(list_args[1]),list_args[2]);
    }
    
    free(args_non_constent);
    return "";
}

const char* HNUIManager::DrawCharacter(const char* args)
{
    char* args_non_constent = strdup(args);
    char* args_ = strtok(args_non_constent,",");
    char* list_args[2];

    unsigned char char_[8];

    for (int _ = 0; _ < 2;_++)
    {
        if (args_ != NULL)
        {
            list_args[_] = args_;
            args_ = strtok(NULL,",");
        }
        else
        {
            break;
        }
    }

    for (int _ = 0; _ < 8;_++)
    {
        if (args_ != NULL)
        {
            char_[_] = *args_;
            args_ = strtok(NULL,",");
        }
        else
        {
            break;
        }
    }

    if (list_args[0] && list_args[1])
    {
        UIManager::DrawCharacter(atoi(list_args[0]),atoi(list_args[1]),char_);
    }
    
    free(args_non_constent);
    return "";
}