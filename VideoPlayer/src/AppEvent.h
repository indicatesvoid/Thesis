#pragma once
#include "ofMain.h"

class AppEvent : public ofEventArgs {

    public:
        static ofEvent<int> BUTTON_PRESSED;
};