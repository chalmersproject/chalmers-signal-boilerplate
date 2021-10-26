#include <ArduinoJson.h>
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