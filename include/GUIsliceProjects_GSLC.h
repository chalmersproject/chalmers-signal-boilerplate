//<File !Start!>
// FILE: [GUIsliceProjects_GSLC.h]
// Created by GUIslice Builder version: [0.16.b011]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Num.h"
#include "elem/XRingGauge.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be arduino
#endif
#include <TFT_eSPI.h>
// #define DOSISBOOK16_VLW "FreeMono12pt7b.h"
// #define DOSISBOOK20_VLW "FreeMono18pt7b.h"
#define Font16 "Font16.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_POP_KEYPAD_NUM};
enum {CAPACITY_HEADER,CAPACITY_NUM_MONITOR,OCCUPANCY_GAGE
      ,OCCUPANCY_HEADER,OCCUPANCY_NUM_MONITOR,E_ELEM_KEYPAD_NUM};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,E_FONT16,E_DOSISBOLD20V,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                2

#define MAX_ELEM_PG_MAIN 5 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXRingGauge               m_sXRingGauge1;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_OCCUPANCY;
extern gslc_tsElemRef* m_CAPACITY;
extern gslc_tsElemRef* m_pElemXRingGauge1;
extern gslc_tsElemRef* m_pElemKeyPadNum;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    // if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    // if (!gslc_FontSet(&m_gui,E_DOSISBOLD16V,GSLC_FONTREF_FNAME,DOSISBOOK16_VLW,16)) { return; }
    // gslc_FontSetMode(&m_gui, E_DOSISBOLD16V, GSLC_FONTREF_MODE_1);	
    // if (!gslc_FontSet(&m_gui,E_DOSISBOLD20V,GSLC_FONTREF_FNAME,DOSISBOOK20_VLW,20)) { return; }

gslc_FontSet(&m_gui, E_FONT16, GSLC_FONTREF_FNAME, Font16, 16);
gslc_FontSetMode(&m_gui, E_FONT16, GSLC_FONTREF_MODE_1);
// TODO: remove E_DOSISBOLD* references
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN

  // Create ring gauge OCCUPANCY_GAGE
  static char m_sRingText1[11] = "";
  
  //
  // this RingGauge creates an upside down U shaped gage near bottom screen
  //
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui, OCCUPANCY_GAGE, E_PG_MAIN, &m_sXRingGauge1,
                                       (gslc_tsRect){3, 23, 120, 140},
                                       (char *)m_sRingText1, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui, pElemRef, 250, 220, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_CYAN, GSLC_COL_GREEN_DK3);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);

/*
  //
  // this RingGuage creates a circle gage near middle screen
  //
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui, OCCUPANCY_GAGE, E_PG_MAIN, &m_sXRingGauge1,
                                       (gslc_tsRect){7, 20, 113, 97},
                                       (char *)m_sRingText1, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui, pElemRef, 0, 360, true);
  // gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, pElemRef, GSLC_COL_GREEN_LT2);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_GREEN_LT2, GSLC_COL_GREEN_DK3);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
*/
  //
  // creates reference for this ringgauge so it can be updated later
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  m_pElemXRingGauge1 = pElemRef;
  
  // Create CAPACITY_HEADER text label
  // pElemRef = gslc_ElemCreateTxt(&m_gui,CAPACITY_HEADER,E_PG_MAIN,(gslc_tsRect){10,70,25,10},
  //   (char*)"",0,E_BUILTIN5X8);
  
  // Create OCCUPANCY_NUM_MONITOR numeric input field
  static char m_sInputNumber1[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,OCCUPANCY_NUM_MONITOR,E_PG_MAIN,(gslc_tsRect){20,70,30,30},
  (char*)m_sInputNumber1,7,E_FONT16);
  // gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  // gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  // gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  // gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_OCCUPANCY = pElemRef;
  /*
  // Create OCCUPANCY_HEADER text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,OCCUPANCY_HEADER,E_PG_MAIN,(gslc_tsRect){10,40,25,10},
    (char*)"",0,E_BUILTIN5X8);
  
  // Create CAPACITY_NUM_MONITOR numeric input field
  static char m_sInputNumber2[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,CAPACITY_NUM_MONITOR,E_PG_MAIN,(gslc_tsRect){40,70,67,22},
    (char*)m_sInputNumber2,7,E_DOSISBOLD16V);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal2 = pElemRef;

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
  */
  //<InitGUI !End!>

  //<Startup !Start!>
  gslc_GuiRotate(&m_gui, 0);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
