//////////////////////////////////////////////////////////
//            CHALMERS SIGNAL OCCUPANCY                 //
//////////////////////////////////////////////////////////
/*
The Chalmers Signal Occuapncy Device is a client tally counter
for shelter reception staff. 

Written an Maintained by the Chalmers project info@chalmersproject.com
F/OSS under M.I.T License
*/

// ------------------------------------------------
// TEST programs & TROUBLESHOOTING flags
// ------------------------------------------------
bool enable_cycle_OCCUPANCY_test = false;
bool enable_internet = true;

// ------------------------------------------------
// Headers to include
// ------------------------------------------------

#include <Arduino.h>
#include <SPI.h>

#include "shelter_secrets.h"
// ------------------------------------------------
// Global Variables
// ------------------------------------------------
unsigned int now;
int OCCUPANCY = 0;
int CAPACITY = 160;
#include "setup_interrupts_globals/graphql_init.h"
#include "setup_interrupts_globals/wifi_globals.h"
#include "../GUIsliceProjects/GUIsliceProjects_GSLC.h"
#include "setup_interrupts_globals/rotary_encoder_init.h"
#include "setup_interrupts_globals/guislice_init.h"
#include "setup_interrupts_globals/led_globals.h"



#include "sub_routines/occupancy_cycle_test.h"
#include "sub_routines/position_change_rotary_encoder.h"

#include "sub_routines/graphql_request.h"
// #include "sub_routines/graphql_sync_remote_data_to_local.h"
#include "sub_routines/guislice_callbacks.h"

#include "timer_interrupts/wait_millis_for_push.h"

    void
    setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();
  if (enable_internet) initWifi();
  LED_Setup();
  rotary_encoder_setup();
  example_show_LED();
}

// -----------------------------------
// Main event loop
// -----------------------------------


// int dial_pos;
void loop()
{
  //
  // record how many *millis*econds since esp startup -- for timers used throughout this program
  //
  now = millis();

  //
  // set OCCUPANCY to where rotary encoder's current position
  // (or cycle OCCUPANCY if test is enabled)
  OCCUPANCY = (enable_cycle_OCCUPANCY_test == false) ? 
                position_change_rotary_encoder(encoder, OCCUPANCY, CAPACITY) : 
                occupancy_cycle_test(200, now, OCCUPANCY, CAPACITY);

  // ------------------------------------------------
  // PUSH/PULL to cloud DB periodically
  // ------------------------------------------------
  wait_to_pull(3000, OCCUPANCY, enable_internet);

  // ------------------------------------------------
  // Update all GUISlice elements
  // ------------------------------------------------

  //
  // Update OCCUPANCY and CAPACITY GUI numbers
  //
  char string_to_write[MAX_STR];
  
  snprintf(string_to_write, MAX_STR, "%u", OCCUPANCY);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2, string_to_write);
  
  snprintf(string_to_write, MAX_STR, "%u", CAPACITY);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_3, string_to_write);

  //
  // Update GUISlice gauge
  //
  int gauge_pos = map(OCCUPANCY, 0, CAPACITY, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, gauge_pos);

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}

