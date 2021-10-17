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
#include "Arduino.h"
#include "GUIsliceProjects_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------
#define MAX_STR 15

// Save some element references for quick access
gslc_tsElemRef *m_pElemCnt = NULL;
gslc_tsElemRef *m_OCCUPANCY = NULL;
gslc_tsElemRef *m_pElemVal2 = NULL;
gslc_tsElemRef *m_pElemXRingGauge1 = NULL;
gslc_tsElemRef *m_pElemKeyPadNum = NULL;
// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }


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
  // gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, CAPACITY);
}

// -----------------------------------
// Main event loop
// -----------------------------------
int dial_tick = 0;
unsigned int now, dial_tick_interval;
void loop()
{
  now = millis();
  if (now - dial_tick_interval >= 200)
  {
    dial_tick++;
    dial_tick_interval=now;
  } else if (dial_tick >= 100)
  {
    dial_tick=0;
  }
  

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  char dial_tick_string[MAX_STR];
  snprintf(dial_tick_string, MAX_STR, "%u", dial_tick);
  gslc_ElemSetTxtStr(&m_gui, m_OCCUPANCY, dial_tick_string);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, dial_tick);
  //TODO - Add update code for any text, gauges, or sliders

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}

