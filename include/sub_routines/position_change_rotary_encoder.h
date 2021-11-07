//
// keep OCCUPANCY within 0-CAPACITY RANGE
//
int occupancy_range_limiter(int OCCUPANCY, int CAPACITY)
{
    if (OCCUPANCY <= 0)
    {
        OCCUPANCY = 0;
    }
    else if (OCCUPANCY >= CAPACITY)
    {
        OCCUPANCY = CAPACITY;
    }
    return OCCUPANCY;
}

//
// if rotary encoder has moved to a new position, if position shift is counter-clockwise OCCUPANCY-1, if position shift is clockwise OCCUPANCY+1
// also enable global flag change_to_push

int position_change_rotary_encoder(RotaryEncoder encoder, int OCCUPANCY, int CAPACITY)
{
    static int pos = 0;

    int newPos = encoder.getPosition();
    if (pos != newPos)
    {
        //
        // enable global flag that a change needs to be pushed to cloud db
        //
        change_to_push = true;
        Serial.println("Pos: " + (String)newPos);
        if (pos > newPos)
        {
            OCCUPANCY--;
        }
        else if (newPos > pos)
        {
            OCCUPANCY++;
        }
        Serial.println("OCCUPANCY: " + (String)OCCUPANCY);
        pos = newPos;
    }

    //
    // ensure OCCUPANCY is within 0-CAPACITY RANGE before returning
    //
    return occupancy_range_limiter(OCCUPANCY, CAPACITY);
}
