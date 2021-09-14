void watch_rot_enc_pos()
{
    static int pos = 0;
    int newPos = encoder.getPosition();
    if (pos != newPos)
    {
        Serial.print("Pos: ");
        Serial.print(newPos);
        Serial.println();
        if (pos > newPos)
        {
            occupancy--;
        }
        else if (newPos > pos)
        {
            occupancy++;
        }
        Serial.print("occupancy: ");
        Serial.print(occupancy);
        Serial.println();
        pos = newPos;

        //set barriers on occupancy
        if (0 >= occupancy)
        { 
            occupancy = 0;
        }
        else if (occupancy >= capacity)
        {
            occupancy = capacity;
        }
    }
}
