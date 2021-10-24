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

#include "setup_routines_and_globals/wifi_globals.h"
#include "../GUIsliceProjects/GUIsliceProjects_GSLC.h"
#include "setup_routines_and_globals/guislice_init.h"
#include "setup_routines_and_globals/led_globals.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------


// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
#include "sub_routines/guislice_callbacks.h"

int OCCUPANCY = 0;
int CAPACITY = 160;
int dial_pos;
unsigned int now, dial_tick_interval;
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
  example_show_LED();
}

// -----------------------------------
// Main event loop
// -----------------------------------
bool forward = true;
void loop()
{
  now = millis();
  if (now - dial_tick_interval >= 50 && forward)
  {
    OCCUPANCY++;
    dial_tick_interval = now;
  }
  else if (now - dial_tick_interval >= 50 && !forward)
  {
    OCCUPANCY--;
    dial_tick_interval = now;
  }
  else if (OCCUPANCY >= CAPACITY)
  {
    forward = false;
  }
  else if (OCCUPANCY <= 0)
  {
    forward = true;
  };
  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  char string_to_write[MAX_STR];
  snprintf(string_to_write, MAX_STR, "%u", OCCUPANCY);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2, string_to_write);
  snprintf(string_to_write, MAX_STR, "%u", CAPACITY);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_3, string_to_write);
  dial_pos = map(OCCUPANCY, 0, CAPACITY, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, dial_pos);
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}

