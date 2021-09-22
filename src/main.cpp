//////////////////////////////////////////////////////////
//            CHALMERS SIGNAL OCCUPANCY                 //
//////////////////////////////////////////////////////////
/*
The Chalmers Signal Occuapncy Device Boilerplate
Used for testing parts of the device
This firmware (should) initialize all hardware correctly and supply the programmer with primitives to interact with them

Written an Maintained by the Chalmers project info@chalmersproject.com
F/OSS under M.I.T License
*/

///////////////////////////////////////////////////////////////////////////////////////////
//                    Globals                                                            //
///////////////////////////////////////////////////////////////////////////////////////////
int occupancy = 0;
int capacity = 0;

#include <Arduino.h>
#include <tft_globals.h>
#include <led_globals.h>
#include <wifi_globals.h>
#include <rot_enc_globals.h>

///////////////////////////////////////////////////////////////////////////////////////////
//                    Toggles                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

// some chalmers signals have red-pcb 1.44" displays from creatron
// others use the cheaper blue-pcb 1.44" displays from aliexpress
static int display_color = 1; //(blue_pcb = 1; red_pcb = 2)

// for debugging it's useful to turn off the chalmers signal's internet-y abilities. That way we can do things like make changes with it's interface without waiting for it to connect to the internet
static bool enable_internet = false;

// earlier versions of chalmers signals don't have their button attached to the ESP. It's useful to be able to quickly turn off all features of the chalmers signal that use this button.
static bool has_button = false;

///////////////////////////////////////////////////////////////////////////////////////////
//                    Subroutines                                                        //
///////////////////////////////////////////////////////////////////////////////////////////
#include <subroutines/watch_rot_enc_pos.h>
#include <subroutines/wait_millis_for_push.h>
#include <subroutines/shink_one_digit.h>

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  
  
  tft_Setup(); example_tft_show();
  LED_Setup(); example_show_LED();
  rot_enc_Setup();
  
  if ( enable_internet == true)
  {
    initWifi();
  }
}

unsigned long now, last;

void loop()
{
  // occupancy = watch_rot_enc_pos(occupancy);
  // Serial.println( "Occupancy: " + occupancy);
}