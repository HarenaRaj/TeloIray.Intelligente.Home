// Pin connected to 12 of 74HC595
int latchPin = 3;
// Pin connected to 11 of 74HC595
int clockPin = 4;
// Pin connected to 14 of 74HC595
int dataPin = 2;

byte data = 0xFF;
byte dataArray[10];

void intializePin(int latchP, int clockP, int dataP)
{
    latchPin = latchP;
    clockPin = clockP;
    dataPin = dataP;
    pinMode(latchPin, OUTPUT);
    Serial.println("fichier 2");
}

void digitalWriteShiftOut(int pin, bool state)
{
    if (!state)
    {
        data = data | (0x01 << pin);
    }
    else
    {
        data = data & ((0x01 << pin) ^ 0xFF);
    }

    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, data);
    digitalWrite(latchPin, 1);
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut)
{
    int i = 0;
    int pinState;
    pinMode(myClockPin, OUTPUT);
    pinMode(myDataPin, OUTPUT);
    digitalWrite(myDataPin, 0);
    digitalWrite(myClockPin, 0);
    for (i = 7; i >= 0; i--)
    {
        digitalWrite(myClockPin, 0);
        if (myDataOut & (1 << i))
        {
            pinState = 1;
        }
        else
        {
            pinState = 0;
        }
        digitalWrite(myDataPin, pinState);
        digitalWrite(myClockPin, 1);
        digitalWrite(myDataPin, 0);
    }
    digitalWrite(myClockPin, 0);
}