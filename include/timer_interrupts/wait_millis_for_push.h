//
// wait at least 3 seconds since last change before pushing to api.chalmers.project
//

int last_graphql_push = 0;
void wait_to_push(int wait, int OCCUPANCY, bool enable_internet)
{
    if (now - last_graphql_push >= wait && change_to_push)
    {
        if (enable_internet == true)
        {
            Serial.println("pushing to api.chalmersproject.com");
            occupancy_request(client, OCCUPANCY, "push");
            change_to_push = false;
            last_graphql_push = now;
        }
    }
}

int last_graphql_pull = 0;
void wait_to_pull(int wait, int OCCUPANCY, bool enable_internet)
{
    if ( (now - last_graphql_pull >= wait) && (change_to_push == false) )
    {
        if (enable_internet == true)
        {
            Serial.println("pulling from api.chalmersproject.com");
            occupancy_request(client, OCCUPANCY, "pull");
            last_graphql_pull = now;
        }
    }
}