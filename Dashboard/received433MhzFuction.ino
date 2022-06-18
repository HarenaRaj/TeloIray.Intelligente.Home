void initializeReception(int bound, int pin)
{
    vw_setup(bound);
    vw_rx_start();
    vw_set_rx_pin(pin);
}

char getReceivedData()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen))
    {
        int i;
        digitalWrite(13, true);
        delay(100);
        digitalWrite(13, false);
        delay(100);
        return buf[0];
    }
    return ' ';
}