
//
// REQUEST FORMAT:
//

/*
{
  query: "...the raw query text...",
  variables: {
    signalId: "...",
    signalSecret: "...",
    _MEASUREMENT: 10
  }
}

reqJson = {
  query: "...",
  variables: varJson
}
*/
#define SIGNAL_ID "U2lnbmFsOmQ3NWE3YjVkLWI0YzctNDczZS1iZTA4LTBlNjdkNDQwODE3Yg"
#define SIGNAL_SECRET "aad11b98-f604-4d4c-aa49-0562980dc2d1"
// #define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.cloud.chalmersproject.com/graphql";
// Attempting to do a multi-line variable declaration: HOWTO?
const char *PUSH = "               \
mutation CreateSignalMeasurement(  \
  $signalId: ID!                   \
  $signalSecret: String!           \
  $measurement: Int!               \
) {                                \
  createSignalMeasurement(         \
    input: {                       \
      signalId: $signalId          \
      signalSecret: $signalSecret  \
      measurement: $measurement    \
    }                              \
  ) {                              \
    measurement {                  \
      id                           \
    }                              \
  }                                \
}";

const char *PULL = "               \
query CheckSignalMeasurement(      \
  $signalId: ID!                   \
) {                                \
    signal(id: $signalId)  {       \
      value                        \
    }                              \
}";

typedef struct graphqlQuery
{
    char req[REQBUFF_SIZE];
    char var[VARBUFF_SIZE];
    int status;
    String resp;
} GraphqlQuery;

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
    varJson["measurement"] = 66;

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