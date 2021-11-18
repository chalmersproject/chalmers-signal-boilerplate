
//
// JSON support and  memory storage sizes for parts of the JSON API requests
//
#include <ArduinoJson.h>
#define REQBUFF_SIZE 256    // request buffer
#define VARBUFF_SIZE 256    // variable buffer
#define RESPBUFF_SIZE 2048  // response buffer

const char *_API_HOST = "https://api.cloud.chalmersproject.com/graphql";

//
// When sending PUSH string to _API_HOST
// PUSH sends a graphql mutation of signalId.measurement value to postgres
// variable values are packaged later and sent along with this request in the reqJson variable
//

// Attempting to do a multi-line string literals variable assignment: HOWTO?
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

//
// PULL retrieves 
//
const char *PULL = "               \
query CheckSignalMeasurement(      \
  $signalId: ID!                   \
) {                                \
    signal(id: $signalId)  {       \
      value                        \
    }                              \
}";

// typedef struct graphqlQuery
// {
//     char req[REQBUFF_SIZE];
//     char var[VARBUFF_SIZE];
//     int status;
//     String resp;
// } GraphqlQuery;