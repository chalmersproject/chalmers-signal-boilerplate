#include <ArduinoJson.h>
//
// verify values stored locally are the same as the ones in the cloud
// cloud database is always regarded as source of truth
//
int verify_cloud_values(int OCCUPANCY, int CAPACITY, String SHELTER_CLASS,
                        int OCCUPANCY_REMOTE, int CAPACITY_REMOTE, String SHELTER_CLASS_REMOTE)
{

    //
    // hash LOCAL_DATA, REMOTE_DATA and then compare their strings
    //
    String LOCAL_DATA = (String) OCCUPANCY + (String) CAPACITY + SHELTER_CLASS;
    String REMOTE_DATA = (String)OCCUPANCY_REMOTE + (String)CAPACITY_REMOTE + SHELTER_CLASS_REMOTE;
    if (LOCAL_DATA == REMOTE_DATA){
        return true;
    }
    else
    {
        return false;
    }
}

//
// pull all remote_data (OCCUPANCY, CAPACITY, SHELTER_CLASS) from cloud database
// then set all local_data values to remote_data values
//
void graphql_pull(WiFiClientSecure client)
{
    HTTPClient http;
    DynamicJsonDocument reqJson(1024);
    DynamicJsonDocument varJson(1024);
    DynamicJsonDocument resJson(1024);

    http.begin(client, _API_HOST);
    http.addHeader("Content-Type", "application/json");

    varJson["signalId"] = SIGNAL_ID;
    varJson["signalSecret"] = SIGNAL_SECRET;
    reqJson["query"] = PULL;
    reqJson["variables"] = varJson;

    String request;
    serializeJson(reqJson, request);
    http.POST(request);

    Serial.println((String) resJson);
    Serial.print(" Response Int: ");
    Serial.println(resJson["data"]["signal"]["value"].as<int>());
//     OCCUPANCY = resJson["data"]["signal"]["value"].as<int>();
//     CAPACITY = resJson["data"]["signal"]["value"].as<int>();
//     SHELTER_CLASS = resJson["data"]["signal"]["value"].as<int>();
}