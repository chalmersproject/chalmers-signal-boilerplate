//<App !Start!>
// FILE: [GUIsliceProjects.ino]
// Created by GUIslice Builder version: [0.16.b011]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------

#include <Arduino.h>
#include <SPI.h>

#include "../GUIsliceProjects/GUIsliceProjects_GSLC.h"

#include "setup_interrupts_globals/wifi_globals.h"
#include "setup_interrupts_globals/rotary_encoder_init.h"
#include "setup_interrupts_globals/guislice_init.h"
#include "setup_interrupts_globals/led_globals.h"
#include "setup_interrupts_globals/graphql_requests_init.h"

//
// initializes graphql-query/shelter object
//
#include "setup_interrupts_globals/graphql_shelter_obj_init.h"

#include "sub_routines/occupancy_cycle_test.h"
#include "sub_routines/position_change_rotary_encoder.h"
#include "sub_routines/guislice_callbacks.h"



void setup()
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
  initWifi();
  LED_Setup();
  rotary_encoder_setup();
  example_show_LED();
}

// -----------------------------------
// Main event loop
// -----------------------------------
unsigned int now;
int OCCUPANCY = 0;
int CAPACITY = 160;

void loop()
{
  //
  // record how many *millis*econds since esp startup -- for timers used throughout this program
  //
  now = millis();

  // OCCUPANCY = occupancy_cycle_test(200, now, OCCUPANCY, CAPACITY); // test program that runs the Occupancy up to max and back to 0 in a loop. Adds/Subtracts 1 occupancy every n millis
  
  OCCUPANCY = position_change_rotary_encoder(encoder, OCCUPANCY);
  OCCUPANCY = occupancy_range_limiter(OCCUPANCY, CAPACITY);

  // ------------------------------------------------
  // Update GUI Elements
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
  int dial_pos = map(OCCUPANCY, 0, CAPACITY, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, dial_pos);
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}

