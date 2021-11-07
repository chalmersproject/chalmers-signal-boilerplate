// HTTP POST to chalmersproject API
void occupancy_request(WiFiClientSecure client, String push_or_pull)
{
    // GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
    HTTPClient http;
    DynamicJsonDocument reqJson(1024);
    DynamicJsonDocument varJson(1024);
    DynamicJsonDocument resJson(1024);

    varJson["signalId"] = SIGNAL_ID;
    varJson["signalSecret"] = SIGNAL_SECRET;
    varJson["measurement"] = OCCUPANCY;

    Serial.println("Measurement value: " + (String) varJson["measurement"]);
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
        Serial.print("Response: ");
        serializeJsonPretty(resJson, Serial);
    }
}