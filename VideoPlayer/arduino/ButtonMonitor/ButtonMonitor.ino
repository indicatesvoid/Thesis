#include "Button.h"

uint8_t lastState = 0;

#define NUM_BUTTONS 1
const char Opcode = '#';

Button *buttons[NUM_BUTTONS] = {
  new Button(2)
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(size_t idx = 0; idx < NUM_BUTTONS; idx++) {
    uint8_t currentState = buttons[idx]->state();
    if(currentState != lastState) {
      lastState = currentState;
      if(currentState == 1) {
        Serial.write(Opcode);
        Serial.write(idx);
      }
    }
  }
}
