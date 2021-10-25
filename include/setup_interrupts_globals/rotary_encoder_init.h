#include <RotaryEncoder.h>
#define inputCLK 4 // pin
#define inputDT 5
RotaryEncoder encoder(5, 4);

// flag to mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions
bool change_to_push = false;

void ICACHE_RAM_ATTR encoder_change_trigger()
{
    encoder.tick();
    Serial.println("interrupt triggered!");
}

void rotary_encoder_setup()
{
    attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
    attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);
}