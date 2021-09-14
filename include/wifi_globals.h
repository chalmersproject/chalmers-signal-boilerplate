///////////////////////////////////////////////////////////////////////////////////////////
//                    WIFI                                                              //
///////////////////////////////////////////////////////////////////////////////////////////
//WiFi and HTTPS requests
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection
#include <WiFiManager.h>

WiFiClientSecure client;
void initWifi()
{
  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  bool res;
  res = wm.autoConnect("Chalmers-Signal", "fart"); // password protected ap
  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
  // client.setInsecure();

  if (WiFi.status() == WL_CONNECTED)
  {
    tft.setTextSize(2);
    tft.setTextSize(2);
    tft.setCursor(0, 36);
    tft.println("   Wi-Fi");
    tft.println(" CONNECTED");
    delay(4000);
  }
}