#include "Huminal.hpp"

void Huminal::PreDefine_Vars(const char* name,const char* value)
{
    utils.DecVar(name,value);
}

void Huminal::CPPFuncDec(const char* name_func,const char* (*hi)(const char* args),const char* args)
{
    utils.CPPFuncDec(name_func,hi,args);
}

int Huminal::Run(const char* run_const,bool func_mode,size_t began_on_line,const char* name_var_return)
{
    char* run;
    run = strdup(run_const);

    char* line_ptr;
    char* line;
    size_t line_index = 0;
    bool skipper_until_end = false;
    line = strtok_r(run,"\n",&line_ptr);
    
    if (func_mode) {

        for (size_t i = 0;i < began_on_line;i++)
        {
            line = strtok_r(NULL,"\n",&line_ptr);
            if (line == NULL){return -1;}
            line_index += 1;
        }
    }
    
    while (line != NULL) {
    char* line_c = line;
    char* token = strtok(line_c," ");

    if (token != NULL)
    {
        if (strcmp(token,"create") == 0 && !skipper_until_end) {
            token = strtok(NULL," ");
            if (token != NULL && strcmp(token,"variable") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL)
                {
                    const char* name_var = token;
                    token = strtok(NULL," ");
                    if (token != NULL && strcmp(token,"=") == 0)
                    {
                        token = strtok(NULL," ");
                        if (token != NULL)
                        {
                            utils.DecVar(name_var,token);
                        }
                    }
                }
            }
            else if (token != NULL && strcmp(token,"function") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL)
                {
                    const char* name_func = token;
                    token = strtok(NULL," ");
                    if (token != NULL && strcmp(token,"(") == 0)
                    {
                        token = strtok(NULL," ");
                        if (token != NULL)
                        {
                            char* args = token;
                            token = strtok(NULL," ");
                            if (token != NULL && strcmp(token,")") == 0)
                            {
                                utils.FuncDec(name_func,line_index + 1,args);
                                skipper_until_end=true;
                            }
                        }
                    }else if (token != NULL && strcmp(token,"()") == 0)
                    {
                        utils.FuncDec(name_func,line_index + 1);
                        skipper_until_end=true;
                    }
                }
            }
            else if (token != NULL && strcmp(token,"comment") == 0)
            {
                continue;
            }
            else if (token != NULL && strcmp(token,"condition") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL && strcmp(token,"if") == 0)
                {
                    token = strtok(NULL," ");
                    if (token != NULL)
                    {
                        char* name_var = token;
                        token = strtok(NULL," ");

                        if (token != NULL && strcmp(token,"then") == 0)
                        {
                            if (strcmp(utils.GetVarType(name_var),"error") != 0)
                            {
                                name_var = strdup(utils.GetVarValue(name_var));
                            }
                            if (strcmp(name_var,"true") == 0)
                            {
                                skipper_until_end = true;
                            }else if(strcmp(name_var,"false") == 0)
                            {
                                skipper_until_end = false;
                            }
                            
                            free(name_var);
                            continue;
                        }
                    }
                }
            }
        }else if (strcmp(token,"change") == 0 && !skipper_until_end)
        {
            token = strtok(NULL," ");
            if (token != NULL && strcmp(token,"variable") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL)
                {
                    const char* name_var = token;
                    token = strtok(NULL," ");
                    if (token != NULL && strcmp(token,"=") == 0)
                    {
                        token = strtok(NULL," ");
                        if (token != NULL)
                        {
                            utils.SetVarValue(name_var,token);
                        }
                    }
                }
            }
        }else if (strcmp(token,"call") == 0 && !skipper_until_end)
        {
            token = strtok(NULL," ");
            if (token != NULL && strcmp(token,"function") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL)
                {
                    const char* name_var = token;
                    token = strtok(NULL," ");
                    if (token != NULL && strcmp(token,"(") == 0)
                    {
                        token = strtok(NULL," ");
                        if (token != NULL)
                        {
                            char* args = token;
                            token = strtok(NULL," ");
                            if (token != NULL && strcmp(token,")") == 0)
                            {
                                char* run_char_func = strdup(run_const);

                                token = strtok(NULL," ");
                                if (token == NULL)
                                {
                                    utils.CallFunc(name_var,args,run_char_func);
                                }else{
                                    if (strcmp(token,"save") == 0)
                                    {
                                        token = strtok(NULL," ");
                                        if (token != NULL && strcmp(token,"to") == 0)
                                        {
                                            token = strtok(NULL," ");
                                            if (token != NULL)
                                            {
                                                utils.CallFunc(name_var,args,run_char_func);
                                            }
                                        }
                                    }
                                }

                                free(run_char_func);
                            }
                        }
                    }else if (token != NULL && strcmp(token,"()") == 0)
                    {
                    char* run_char_func = strdup(run_const);

                    token = strtok(NULL," ");
                    if (token == NULL)
                    {
                        utils.CallFunc(name_var,"",run_char_func);
                    }else{
                        if (strcmp(token,"save") == 0)
                        {
                            token = strtok(NULL," ");
                            if (token != NULL && strcmp(token,"to") == 0)
                            {
                                token = strtok(NULL," ");
                                if (token != NULL)
                                {
                                    utils.CallFunc(name_var,"",run_char_func,token);
                                }
                            }
                        }
                    }

                    free(run_char_func);
                    }
                }
            }/*else if (token != NULL && strcmp(token,"object") == 0)
            {
                token = strtok(NULL," ");
                if (token != NULL)
                {
                    const char* name_obj = token;
                    token = strtok(NULL," ");
                    if (token != NULL)
                    {}
                }
            }*/
            
        }else if (strcmp(token,"wait") == 0)
        {
            token = strtok(NULL," ");
            if (token != NULL)
            {
                const char* value = token;
                token = strtok(NULL," ");
                if (token != NULL && strcmp(token,"millis"))
                {
                    DELAY(atoi(value));
                }
                else if (token != NULL && strcmp(token,"second"))
                {
                    DELAY(atoi(value) * 1000);
                }
                else if (token != NULL && strcmp(token,"minutes"))
                {
                    DELAY((atoi(value) * 1000) * 60);
                }
                else
                {
                    return -1;
                }
                continue;
            }
        }
        else if (strcmp(token,"end") == 0 && (func_mode || skipper_until_end))
        {
            if (func_mode) {return 0;}
            else if (skipper_until_end) {skipper_until_end = false;continue;}
        }else if (strcmp(token,"return") == 0 && func_mode)
        {
            token = strtok(NULL," ");
            if (token == NULL)
            {
                return -1;
            }else
            {
                utils.DecVar(name_var_return,utils.GetVarValue(token));
                return 0;
            }
        }else if ((strcmp(token,"--") == 0 || strcmp(token,"//")) == 0 && !skipper_until_end)
        {
            continue;
        }
    }

    line = strtok_r(NULL,"\n",&line_ptr);
    line_index += 1;
    }

    free(run);
    return 0;
}