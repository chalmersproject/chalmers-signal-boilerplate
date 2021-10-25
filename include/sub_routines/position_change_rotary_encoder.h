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