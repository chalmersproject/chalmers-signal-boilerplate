//
// wait at least 3 seconds since last change before pushing to api.chalmers.project
//

int last_graphql_push = 0;
void wait_to_push(int wait, int OCCUPANCY, bool enable_internet)
{
    if (now - last_graphql_push >= wait && change_to_push)
    {
        Serial.println("pushing to api.chalmersproject.com, value of " + (String) OCCUPANCY);
        if (enable_internet == true)
        {
            occupancy_request(client, "push");
            change_to_push = false;
            last_graphql_push = now;
            last_graphql_pull = now;
        }
    }
}

//
// if it's been *wait* milliseconds since last push or pull, 
// pull data from database and sync it with local global variables
//
int last_graphql_pull = 0;
void wait_to_pull(int wait, int OCCUPANCY, bool enable_internet)
{
    if ( (now - last_graphql_pull >= wait) && (change_to_push == false) )
    {
        Serial.println("pulling from api.chalmersproject.com");
        if (enable_internet == true)
        {
            occupancy_request(client, "pull");
            last_graphql_pull = now;
        }
    }
    else
    {
        Serial.println("now:               " + (String)now);
        Serial.println("last_graphql_pull: "  + (String) last_graphql_pull);
    }
}