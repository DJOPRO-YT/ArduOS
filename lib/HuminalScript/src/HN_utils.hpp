#ifndef HUMINAL_UTILS_H
#define HUMINAL_UTILS_H

#ifdef REMAKE_328
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#elif defined(NATIVE)
#include <cstdint>
#include <cstring>
#include <cstddef>
#include <cstdlib>
#endif

class Huminal;

class ssUtils {
private:
    struct Vars {
        const char* name;
        const char* value;
    };
    struct Funcs {
        const char* name;
        const char* args;

        bool cpptype = false;

        size_t index_line_start;
        const char* (*function)(const char* args);
    };

    size_t vars_counter = 0;
    size_t funcs_counter = 0;
    Vars vars_[10];
    Funcs funcs_[10];
public:
    void DecVar(const char* name,const char* value);
    const char* GetVarType(const char* name);
    const char* GetVarValue(const char* name);
    void SetVarValue(const char* name,const char* value);

    void FuncDec(const char* name,size_t start_index,const char* args = "");
    void CPPFuncDec(const char* name,const char* (*function)(const char* args_f),const char* args = "");
    void CallFunc(const char* name,const char* args_const,char* code,const char* name_var_return = "");
};

#endif