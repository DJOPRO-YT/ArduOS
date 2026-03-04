#ifndef HN_CONTROLLER_H
#define HN_CONTROLLER_H

#include <Controller.hpp>
#include <stdlib.h>
#include <stdint.h>

static Controller cons;

class HNController {

public:
static void init();
static const char* GetPosX(const char* args);
static const char* GetPosY(const char* args);
static const char* IsBtnClicked(const char* args);
};
#endif