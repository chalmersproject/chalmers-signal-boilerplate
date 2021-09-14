void shrink_one_digit(int occupancy, int last_occupancy)
{
    // used to detect when occupancy has grown by one digit ( e.g. 10 -> 9 ) and occupancy has to be wiped from the LCD
    if (occupancy == 9 && last_occupancy == 10 || occupancy == 99 && last_occupancy == 100)
    {
        // tft.fillRect(35, y1, tft.width(), (y2 - 25), BLACK);
        // last_occupancy = occupancy;
    }
}
