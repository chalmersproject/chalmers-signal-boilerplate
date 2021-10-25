unsigned int occupancy_test_timer = 0;
bool forward = true;
int occupancy_cycle_test(int speed, unsigned int now, int OCCUPANCY, int CAPACITY)
{
    if (now - occupancy_test_timer >= speed && forward)
    {
        OCCUPANCY++;
        occupancy_test_timer = now;
    }
    else if (now - occupancy_test_timer >= speed && !forward)
    {
        OCCUPANCY--;
        occupancy_test_timer = now;
    }
    else if (OCCUPANCY >= CAPACITY)
    {
        forward = false;
    }
    else if (OCCUPANCY <= 0)
    {
        forward = true;
    };
    return OCCUPANCY;
}