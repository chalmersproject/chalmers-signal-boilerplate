int position_change_rotary_encoder(RotaryEncoder encoder, int OCCUPANCY)
{
    static int pos = 0;

    int newPos = encoder.getPosition();
    if (pos != newPos)
    {
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
    return OCCUPANCY;
}

//
// keep OCCUPANCY within 0/CAPACITY RANGE
//

int occupancy_range_limiter(int OCCUPANCY, int CAPACITY)
{
    if (OCCUPANCY < 0)
    {
        OCCUPANCY = 0;
        return OCCUPANCY;
    }else if (OCCUPANCY > CAPACITY){
        OCCUPANCY = CAPACITY;
        return OCCUPANCY;
    }else
    {
        return OCCUPANCY;
    }
}