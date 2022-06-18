#include <VirtualWire.h>

/**
 * @brief
 *
 *  ARDUINO PINS
 *
 * */
#define LED_INDICATOR_PIN 2
#define BUTTON_1 3
#define BUTTON_2 4
#define BUTTON_3 5
#define BUTTON_4 6
#define SEND_DATA_DATA 7

void setup()
{

    // Serial.begin(115200);

    /* Pin initialize arduino */
    pinMode(LED_INDICATOR_PIN, OUTPUT);
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);
    pinMode(BUTTON_4, INPUT);

    /* VirtualWire initialize */
    vw_set_ptt_inverted(true);
    vw_setup(2000);
    vw_set_tx_pin(SEND_DATA_DATA);
}
void loop()
{
    if (digitalRead(BUTTON_1))
    {
        sendData("1");
        blinkIndicator(2);
    }
    if (digitalRead(BUTTON_2))
    {
        sendData("2");
        blinkIndicator(3);
    }
    if (digitalRead(BUTTON_3))
    {
        sendData("3");
        blinkIndicator(4);
    }
    if (digitalRead(BUTTON_4))
    {
        sendData("4");
        blinkIndicator(5);
    }
}

void sendData(char *data)
{
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(200);
}

void blinkIndicator(int once)
{
    for (int i = 0; i < once; i++)
    {
        digitalWrite(LED_INDICATOR_PIN, HIGH);
        delay(100);
        digitalWrite(LED_INDICATOR_PIN, LOW);
        delay(100);
    }
}