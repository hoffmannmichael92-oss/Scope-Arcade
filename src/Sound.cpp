#include <Arduino.h>
#include "Sound.h"

static const int summerPin = 4;

static bool tonAktiv = false;
static unsigned long tonStart = 0;
static unsigned long tonDauer = 0;

void SoundInitialisieren()
{
    pinMode(summerPin, OUTPUT);
    digitalWrite(summerPin, LOW);
}

void MenueAuswahlTon()
{
    tonDauer = 70;
    tonStart = millis();
    tonAktiv = true;

    digitalWrite(summerPin, HIGH);
}

void PongSound()
{
    tonDauer = 30;
    tonStart = millis();
    tonAktiv = true;

    digitalWrite(summerPin, HIGH);
}

void SchussSound()
{
    tonDauer = 20;
    tonStart = millis();
    tonAktiv = true;

    digitalWrite(summerPin, HIGH);
}


void SoundAktualisieren()
{
    if (tonAktiv && millis() - tonStart >= tonDauer)
    {
        digitalWrite(summerPin, LOW);
        tonAktiv = false;
    }
}