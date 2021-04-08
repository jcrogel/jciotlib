#include "Keyboard.h"
#include <LinkedList.h>

#define MAX_ITEMS 8

char key1[] = {};
char key2[] = {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'D'};
char key3[] = {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'E'};
char key4[] = {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'M'};
char key5[] = {KEY_LEFT_CTRL, KEY_LEFT_GUI, 'k'};
char key6[] = {KEY_LEFT_CTRL, KEY_LEFT_GUI, 'j'};
char key7[] = {KEY_LEFT_CTRL, KEY_LEFT_GUI, 'p'};
char key8[] = {KEY_LEFT_CTRL, KEY_LEFT_GUI, 'c'};

int key_combos_len[] = {0,3,3,3,3,3,3,3};
char *key_combos[] = { key1, key2, key3, key4, key5, key6, key7, key8};
int button_status[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
const unsigned long debounceTime = 30;
unsigned long lastPressed = 0;
boolean pressed = 0;
 
void setup() { 
  // Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if(!digitalRead(1)){
    failsafe();
  }
 
 
  for(int i = 2; i < 10; i++){
    pinMode(i, INPUT_PULLUP);
  }
}
 
void loop() {
  //for(int i = 0; i < 8; i++){
  //  buttons[i].update();
    //Serial.print("ABCD");
  //}

  for(int i = 0; i < 8; i++){
    int keylen = key_combos_len[i];
    char *key_combo_ptr = key_combos[i];
    int pin = i+2;
    //Serial.print(pin);
    int state = digitalRead(pin);

  
    if(state == button_status[i] || millis() - lastPressed  <= debounceTime){
      continue;
    }

    lastPressed = millis();
    if(state == LOW){
      for (int k=0; k < keylen; k++){
        Keyboard.press(key_combo_ptr[k]);
      }
      
    } else {
      // Release
      Keyboard.releaseAll();
    }
    
    delay(100);
    button_status[i] = state;

    
    
  }
}
 
void failsafe(){
  for(;;){} // Just going to hang out here for awhile :D
}
