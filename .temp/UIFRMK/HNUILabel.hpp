#ifndef HN_UILABEL_H
#define HN_UILABEL_H

#include <UIFramework.hpp>
#include <stdlib.h>
#include <stdint.h>

size_t lbl = 0;
UI::Label lbls[10];

class HNLabel {
public:
static const char* CreateLabel(const char* args);
static const char* SetPosition(const char* args);
static const char* SetText(const char* args);
static const char* SetVisibility(const char* args);
};
#endif