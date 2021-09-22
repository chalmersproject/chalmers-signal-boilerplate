///////////////////////////////////////////////////////////////////////////////////////////
//                    TFT DISPLAY                                                        //
///////////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>
#include <RotaryEncoder.h>
// #include "GUIslice.h"
// #include "GUIslice_ex.h"
// #include "GUIslice_drv.h"

//
// Global Variables
//
// displays from creatron and aliexpress require different coordinates
#define y1 ((display_color == 1) ? 18 : 42) //top left of top digit
#define __DC 0
#define __CS 2
// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

//
// GUIslice global variables 
//
// gslc_tsGui m_gui;
// gslc_tsDriver m_drv;
// gslc_tsFont m_asFont[MAX_FONT];
// gslc_tsPage m_asPage[MAX_PAGE];
// gslc_tsElem m_asPageElem[MAX_ELEM_PG_MAIN];
// gslc_tsElemRef m_asPageElemRef[MAX_ELEM_PG_MAIN];
// #define MAX_FONT 1          // Max # fonts
// #define MAX_PAGE 2          // Max # pages in GUI
// #define MAX_ELEM_PG_MAIN 15 // Max # of elements on main page

//
// GUIslice fonts instatiate
// https://github.com/ImpulseAdventure/GUIslice/wiki/User-Guide
/* Before outputting text to the display, at least one font needs to be defined. Note that the font name and size parameters are dependent upon the platform type (eg. Raspberry Pi vs Arduino).
When creating fonts, elements and pages, it is easiest to use enumerations so that these structures can be referenced later. In the above, E_FONT_TXT was previously defined in the code as an enumeration: enum {E_FONT_TXT};
*/

// gslc_FontAdd(&m_gui, E_FONT_TXT, "droidSans.ttf", 12); // RPi
// gslc_FontAdd(&m_gui, E_FONT_TXT, "", 1);               // Arduino

//instatiate TFT!
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

//TODO: There has to be a better way to resize numbers..
int last_MEASUREMENT; //used to detect when occupancy has grown by one digit ( e.g. 9 -> 10 ) and occupancy has to be wiped from the LCD

void tft_Setup()
{
  tft.begin();
  tft.setRotation(2);
  tft.setCursor(0, 0);
}

void example_tft_show()
{
  tft.clearScreen(BLACK);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.println("CHALMERS");
}

