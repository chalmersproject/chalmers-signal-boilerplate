///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder                                                     //
///////////////////////////////////////////////////////////////////////////////////////////
#include <RotaryEncoder.h>
//
// Global Variables
//
#define inputCLK 4 // pin
#define inputDT 5
RotaryEncoder encoder(5, 4);
//
// flags
//
bool change_to_push = false; // mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions

void ICACHE_RAM_ATTR encoder_change_trigger()
{
  encoder.tick();
  // Serial.println("interrupt triggered!"); // for debugging, but i wonder if this is messing with encoder timing? 
}


void rot_enc_Setup()
{
  attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);
}
