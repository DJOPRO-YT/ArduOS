#ifndef HN_UIBUTTON_H
#define HN_UIBUTTON_H

#include <UIFramework.hpp>
#include <stdlib.h>
#include <stdint.h>

extern void ButtonConnection(size_t index);

size_t btn = 0;
UI::Button btns[10];

class HNButton {
public:
static const char* CreateButton(const char* args);
static const char* SetPosition(const char* args);
static const char* SetText(const char* args);
static const char* SetVisibility(const char* args);

static const char* Connect(const char* args);
};
#endif