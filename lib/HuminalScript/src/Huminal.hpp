#ifndef HUMINAL_H
#define HUMINAL_H

#ifdef REMAKE_328
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#elif defined(NATIVE)
#include <cstdlib>
#include <cstring>
#include <cstddef>
#endif
#include "HN_utils.hpp"
#include <Utils.hpp>

#define DELAY(ms) Sleep_for(ms)

class Huminal {
private:
    ssUtils utils;
public:
    int Run(const char* run,bool func_mode = false,size_t began_on_line = 0,const char* name_var_return = "");
    void PreDefine_Vars(const char* name,const char* value);
    void CPPFuncDec(const char* name_func,const char* (*hi)(const char* args),const char* args = "");
    void CallFunction(const char* name,const char* args,char* code,const char* name_var_return = "");
};

#endif