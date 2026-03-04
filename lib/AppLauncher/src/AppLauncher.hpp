#ifndef APPLAUNCHER_H
#define APPLAUNCHER_H

#include <Huminal.hpp>


#include "libs/HNController.hpp"

#ifdef REMAKE_32
    #include <UIFramework.hpp>
    #include "libs/HNUILabel.hpp"
    #include "libs/HNUIButton.hpp"
#elif defined(REMAKE_328)
    #include "libs/HNUIManager.hpp"
#endif

class AppLauncher {
private:
    Huminal hns;
public:
    void Init();
    int Run(const char* code);
};

#endif