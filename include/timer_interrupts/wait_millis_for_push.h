//
// wait at least 3 seconds since last change before pushing to api.cloud.chalmersproject.com
//

void wait_to_push(int wait, int last, bool change_to_push, int _millis, bool enable_internet)
{
    int now = _millis;
    if (now - last >= wait && change_to_push)
    {
        if (enable_internet == true)
        {
            Serial.println("pushing to api.chalmersproject.com");
            // occupancy_request(client, occupancy, "push");
            change_to_push = false;
        }
    }
}