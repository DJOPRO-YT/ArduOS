#include "HN_utils.hpp"
#include "Huminal.hpp"

void replaceWord(char* str, const char* oldWord, const char* newWord) {
    char *pos, temp[1000]; // Assuming a sufficiently large buffer
    int index = 0;
    int oldWordLen = strlen(oldWord);
    //int newWordLen = strlen(newWord);

    while ((pos = strstr(str, oldWord)) != NULL) {
        // Store the part of the string before the old word
        index = pos - str;
        strncpy(temp, str, index);
        temp[index] = '\0'; // Null-terminate the copied part

        // Concatenate the new word
        strcat(temp, newWord);

        // Concatenate the remaining part of the string after the old word
        strcat(temp, pos + oldWordLen);

        // Copy the modified string back to the original buffer
        strcpy(str, temp);
    }
}

int findFirstNotOf(const char* str, const char* chars) {
    if (!str || !chars) return -1; // safety check
    size_t len = strlen(str);
    size_t charsLen = strlen(chars);

    for (size_t i = 0; i < len; i++) {
        bool found = false;
        for (size_t j = 0; j < charsLen; j++) {
            if (str[i] == chars[j]) {
                found = true;
                break;
            }
        }
        if (!found) return (int)i;
    }
    return -1; // not found
}

int findLastNotOf(const char* str, const char* chars) {
    if (!str || !chars) return -1; // safety check
    size_t len = strlen(str);
    size_t charsLen = strlen(chars);

    if (len == 0) return -1;

    for (int i = (int)len - 1; i >= 0; i--) {
        bool found = false;
        for (size_t j = 0; j < charsLen; j++) {
            if (str[i] == chars[j]) {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }
    return -1; // not found
}





const char* GetValueType(const char* value)
{
    if (value[0] == '\"' && value[strlen(value) - 1] == '\"')
    {
        return "string";
    }
    else if (findFirstNotOf(value,"1234567890") == -1)
    {
        return "integer";
    }
    else if (strcmp(value,"false") == 0 || strcmp(value,"true") == 0)
    {
        return "boolean";
    }
    else if (strcmp(value,"null") == 0)
    {
        return "null";
    }

    return "error";
}

void ssUtils::DecVar(const char* name,const char* value)
{
    if (strcmp(GetVarType(value),"error") == 0) {
        vars_[vars_counter] = {name,value};
    }else{
        vars_[vars_counter] = {name,GetVarValue(value)};
    }
    vars_counter += 1;
}

const char* ssUtils::GetVarValue(const char* name)
{
    for (size_t index = 0; index < vars_counter;index++)
    {
        if (strcmp(vars_[index].name, name) == 0)
        {
            return vars_[index].value;
        }
    }
    return "";
}

const char* ssUtils::GetVarType(const char* name)
{
    for (size_t index = 0; index < vars_counter;index++)
    {
        if (strcmp(vars_[index].name , name) == 0)
        {
            if (strlen(vars_[index].value) > 0) {
                if (vars_[index].value[0] == '\"' && vars_[index].value[strlen(vars_[index].value) - 1] == '\"')
                {
                    return "string";
                }
                else if (findFirstNotOf(vars_[index].value,"1234567890") == -1)
                {
                    return "integer";
                }
                else if (strcmp(vars_[index].value,"false") == 0|| strcmp(vars_[index].value,"true") == 0)
                {
                    return "boolean";
                }
                else if (strcmp(vars_[index].value,"null") == 0)
                {
                    return "null";
                }
            }

            return "error";
        }
    }
    return "error";
}

void ssUtils::SetVarValue(const char* name,const char* value)
{
    for (size_t index = 0; index < vars_counter;index++)
    {
        if (strcmp(vars_[index].name , name) == 0)
        {
            vars_[index].value = value;
        }
    }
}

void ssUtils::FuncDec(const char* name,size_t start_index,const char* args)
{
    Funcs hi;
    hi.name = name;
    hi.cpptype = false;
    hi.index_line_start = start_index;
    
    hi.args = args;

    funcs_[funcs_counter] = hi;
    funcs_counter += 1;
}

void ssUtils::CPPFuncDec(const char* name,const char* (*function)(const char* args_f),const char* args)
{
    Funcs hi;
    hi.name = name;
    hi.cpptype = true;
    hi.args = args;
    hi.function = function;

    funcs_[funcs_counter] = hi;
    funcs_counter += 1;
}

/*

void ssUtils::CallFunc(const char* name,const char* args_const,char* code,const char* name_var_return)
{
    for (size_t index = 0; index < funcs_counter; index++)
    {
        if (strcmp(funcs_[index].name, name) == 0)
        {
            SimpleScript ss;
            char* finished_args_for_cpp = strdup(args_const); // start with a copy we can modify

            if (strcmp(args_const, "") != 0) {
                char* args = strdup(args_const);

                char* onearg_ptr;
                char* hihihi_ptr;
                char* onearg = strtok_r(args, ",", &onearg_ptr);
                char* hihihi;

                char* temp = strdup(funcs_[index].args);
                hihihi = strtok_r(temp, ",", &hihihi_ptr);

                while (onearg != NULL && hihihi != NULL)
                {
                    const char* type = GetVarType(onearg);
                    if (strcmp(type,"error") != 0)
                    {
                        if (strcmp(GetValueType(onearg),"error") == 0)
                        {
                            free(args);
                            free(temp);
                            free(finished_args_for_cpp);
                            return;
                        }
                        else
                        {
                            if (!funcs_[index].cpptype)
                            {
                                ss.PreDefine_Vars(hihihi, GetVarValue(onearg));
                            }
                            else
                            {
                                char* new_str = replaceWord(finished_args_for_cpp, onearg, GetVarValue(onearg));
                                free(finished_args_for_cpp); // free old buffer
                                finished_args_for_cpp = new_str;
                            }
                        }
                    }

                    onearg = strtok_r(NULL, ",", &onearg_ptr);
                    hihihi = strtok_r(NULL, ",", &hihihi_ptr);
                }
                free(args);
                free(temp);
            }

            if (!funcs_[index].cpptype)
            {
                ss.Run(code, true, funcs_[index].index_line_start, name_var_return);
            }
            else
            {
                if (strcmp(name_var_return, "") != 0) {
                    const char* r = funcs_[index].function(finished_args_for_cpp);
                    DecVar(name_var_return, r);
                }
                else
                {
                    funcs_[index].function(finished_args_for_cpp);
                }
            }

            free(finished_args_for_cpp);
        }
    }
}


*/
void ssUtils::CallFunc(const char* name,const char* args_const,char* code,const char* name_var_return)
{
    for (size_t index = 0; index < funcs_counter;index++)
    {
        if (strcmp(funcs_[index].name , name) == 0)
        {

            Huminal ss;
            char* finished_args_for_cpp = strdup(args_const);
            if (strcmp(args_const,"") != 0) {
                char* args = strdup(args_const);
                char* onearg_ptr;
                char* hihihi_ptr;
                char* onearg = strtok_r(args,",",&onearg_ptr);
                char* temp = strdup(funcs_[index].args);
                char* hihihi = strtok_r(temp,",",&hihihi_ptr);
                
                //cout << onearg << " --> " << hihihi << endl;
                
                while (onearg != NULL && hihihi != NULL)
                {
                    const char* type = GetVarType(onearg);
                    if (strcmp(type,"error") != 0)
                    {
                        if (1) {
                            if (!funcs_[index].cpptype)
                            {
                                ss.PreDefine_Vars(hihihi,GetVarValue(onearg));
                            }
                            else
                            {
                                replaceWord(finished_args_for_cpp,onearg,GetVarValue(onearg));
                            }
                        }
                    }

                    onearg = strtok_r(NULL,",",&onearg_ptr);
                    hihihi = strtok_r(NULL,",",&hihihi_ptr);
                }
                free(args);
                free(temp);
            }
            
            for (size_t index__ = 0; index__ < funcs_counter; index__++)
            {
                
                if (funcs_[index__].cpptype && strcmp(funcs_[index__].name , name) != 0)
                {
                    ss.CPPFuncDec(funcs_[index__].name,funcs_[index__].function,funcs_[index__].args);
                }
            }
            
            if (funcs_[index].cpptype == false)
            {
                ss.Run(code,true,funcs_[index].index_line_start,name_var_return);
            }else
            {
                if (strcmp(name_var_return,"") != 0) {
                    const char* r= funcs_[index].function(finished_args_for_cpp);
                    DecVar(name_var_return,r);
                }
                else
                {
                    funcs_[index].function(finished_args_for_cpp);
                }
            }
            free(finished_args_for_cpp);
        }
    }
}

