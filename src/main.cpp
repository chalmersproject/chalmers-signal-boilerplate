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
gslc_tsElemRef *m_pElemVal1 = NULL;
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
  Serial.begin(9600);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
int m_nCount;
void loop()
{
  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders

  // example 
  char acTxt[MAX_STR];

  // General counter
  // m_nCount++;
  // delay(200);
  // // Update elements on active page

  // snprintf(acTxt, MAX_STR, "%u", m_nCount / 5);
  // gslc_ElemSetTxtStr(&m_gui, m_pElemXRingGauge1, acTxt);

  // gslc_ElemXProgressSetVal(&m_gui, m_pElemXRingGauge1, ((m_nCount / 1) % 100));

  // // NOTE: A more efficient method is to move the following
  // //       code into the slider position callback function.
  // //       Please see example 07.
  // int nPos = gslc_ElemXSliderGetPos(&m_gui, m_pElemSlider);
  // snprintf(acTxt, MAX_STR, "%u", nPos);
  // gslc_ElemSetTxtStr(&m_gui, m_pElemSliderTxt, acTxt);

  // gslc_ElemXProgressSetVal(&m_gui, m_pElemProgress1, (nPos * 80.0 / 100.0) - 15);


  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
}

