#pragma once

#include "Arduino.h"

#define DEBOUNCE_DELAY 50

class Button {
public:
  Button(uint8_t _pin) {
    this->pin = _pin;
    this->lastState = this->currentState = 0;
    this->didChange = false;
  }
  
  void update() {
    long currentTime = millis();
    
    uint8_t val = digitalRead(pin);
    
    if(val != lastState) lastTime = currentTime;
    lastState = val;
    
    if((currentTime - lastTime) > DEBOUNCE_DELAY) {
      if(val != currentState) {
        currentState = val;
        didChange = true;
      }
    }
  }
  
  uint8_t state() {
    update();
    return currentState;
  }
  
  boolean wasPressed() {
    if(currentState == lastState) return false;
    else  {
      lastState = currentState;
      return true;
//      if(currentState == 1) return true;
//      else return false;
    }
  }

private:
  uint8_t pin;
  uint8_t lastState, currentState;
  bool didChange;
  
  long lastTime;
};
