#include <Arduino.h>
// HTTP POST to chalmersproject API
void occupancy_request(WiFiClientSecure client, int occupancy, String push_or_pull) 
{
    // GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
    HTTPClient http;
    DynamicJsonDocument reqJson(1024);
    DynamicJsonDocument varJson(1024);
    DynamicJsonDocument resJson(1024);

    varJson["signalId"] = SIGNAL_ID;
    varJson["signalSecret"] = SIGNAL_SECRET;
    varJson["measurement"] = occupancy;

    Serial.println("Sending HTTP POST");
    http.begin(client, _API_HOST);
    http.addHeader("Content-Type", "application/json");

    varJson["signalId"] = SIGNAL_ID;
    reqJson["query"] = (push_or_pull == "push") ? PUSH : PULL;
    reqJson["variables"] = varJson;

    String request;
    serializeJson(reqJson, request);
    Serial.print("Request: ");
    Serial.println(request);

    http.POST(request);

    if (push_or_pull == "pull")
    {
        deserializeJson(resJson, http.getStream());
        Serial.print(" Response Int: ");
        Serial.println(resJson["data"]["signal"]["value"].as<int>());
    }
    // Serial.print("Response: ");
    // Serial.println( resJson.getElement );
}

int time_since_last_request = 0;
void handle_occupancy_requests(int wait_since_last_request, unsigned int now, WiFiClientSecure client, int occupancy, String push_or_pull)
{
    if (now - time_since_last_request >= wait_since_last_request)
    {
        occupancy_request(WiFiClientSecure client, int occupancy, String push_or_pull);
    }
}