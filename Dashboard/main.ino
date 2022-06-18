//////////////////////////////////////////
//                                      //
//          ARDUINO UNO CARD            //
//            MAIN PROGRAM              //
//                                      //
//////////////////////////////////////////

#include <VirtualWire.h>

/**
 * @brief
 *
 *  ARDUINO PINS
 *
 * */
#define DATA_PIN 2
#define LATCH_PIN 3
#define CLOCK_PIN 4
#define INSIDE_ALARME_PIN 5
#define RECEIVED_DATA_PIN 7

#define FIL_SENSOR_PIN A0
#define LASER_SENSOR_PIN A1

/**
 * @brief
 *
 * SHIFT OUT PINS
 *
 */
#define OUTSIDE_ALARME_ACTIVE_PIN 0
#define OUTSIDE_ALARME_ALIMENTATION_PIN 1
#define LED_INDICATOR_PIN 2
#define BUZZER_PIN 3

bool insideAlarmActif = true;
bool outsideAlarmActif = false;

bool isAlarmActif = false;

void setup()
{

    /* Pin initialize arduino */
    pinMode(INSIDE_ALARME_PIN, OUTPUT);

    pinMode(FIL_SENSOR_PIN, INPUT);
    pinMode(LASER_SENSOR_PIN, INPUT);

    /* Shift Out intitialize */
    intializePin(LATCH_PIN, CLOCK_PIN, DATA_PIN); // latch, clock, data

    /* VirtualWire initialize */
    initializeReception(2000, RECEIVED_DATA_PIN);

    /* Defaut state */
    digitalWriteShiftOut(OUTSIDE_ALARME_ALIMENTATION_PIN, HIGH);
}
void loop()
{
    char dataReceived = getReceivedData();
    if (dataReceived == '1')
    {
        insideAlarmActif = !insideAlarmActif;
        buzzerIndicator(2);
    }
    if (dataReceived == '2')
    {
        outsideAlarmActif = !outsideAlarmActif;
        buzzerIndicator(3);
    }

    int nAlarme = 0;
    if (insideAlarmActif)
        nAlarme++;
    if (outsideAlarmActif)
        nAlarme++;

    blinkIndicator(nAlarme);

    if (insideAlarmActif)
    {

        if (analogRead(FIL_SENSOR_PIN) < 300)
        {
            activateAlarme();
        }
    }
    // else if (outsideAlarmActif)
    // {
    //     if (analogRead(LASER_SENSOR_PIN) < 500)
    //     {
    //         activateAlarme();
    //     }
    // }
    else
    {
        if (isAlarmActif)
        {
            analogWrite(INSIDE_ALARME_PIN, 0);
            resetOutside();
            isAlarmActif = false;
        }
    }
}

void activateAlarme()
{
    alerteInside();
    if (!isAlarmActif)
    {
        alerteOutside();
    }
    isAlarmActif = true;
}

void alerteInside()
{
    analogWrite(INSIDE_ALARME_PIN, 200);
    delay(50);
    analogWrite(INSIDE_ALARME_PIN, 500);
    delay(50);
}

void alerteOutside()
{
    digitalWriteShiftOut(OUTSIDE_ALARME_ACTIVE_PIN, HIGH);
    delay(200);
    digitalWriteShiftOut(OUTSIDE_ALARME_ACTIVE_PIN, LOW);
    delay(200);
}

void resetOutside()
{
    digitalWriteShiftOut(OUTSIDE_ALARME_ALIMENTATION_PIN, LOW);
    delay(200);
    digitalWriteShiftOut(OUTSIDE_ALARME_ALIMENTATION_PIN, HIGH);
    delay(200);
}

void buzzerIndicator(int once)
{
    for (int i = 0; i < once; i++)
    {
        digitalWriteShiftOut(BUZZER_PIN, HIGH);
        delay(50);
        digitalWriteShiftOut(BUZZER_PIN, LOW);
        delay(50);
    }
}

bool ledState = false;
int previousTime = 0;
void blinkIndicator(int speed)
{
    int currentTime = millis();

    if (speed != 0)
    {
        if ((currentTime - previousTime) > 500 / speed)
        {
            previousTime = currentTime;
            ledState = !ledState;
            digitalWriteShiftOut(LED_INDICATOR_PIN, ledState);
        }
    }
}