#include <Arduino.h>
#include "Sound.h"

static const int summerPin = 4;

static bool tonAktiv = false;
static unsigned long tonStart = 0;
static unsigned long tonDauer = 0;

static const unsigned long GAME_OVER_FOLGE[] = {300, 200, 300, 200, 300, 200, 1200};
static const int GAME_OVER_LAENGE = sizeof(GAME_OVER_FOLGE) / sizeof(GAME_OVER_FOLGE[0]);

static bool folgeLaeuft = false;
static int folgeSchritt = 0;

void SoundInitialisieren()
{
    pinMode(summerPin, OUTPUT);
    digitalWrite(summerPin, LOW);
}

// Ein einzelner kurzer Ton (für Menü, Pong, Schuss)
static void kurzerTon(unsigned long dauer)
{
    folgeLaeuft = false;      // eine laufende Folge abbrechen
    tonDauer = dauer;
    tonStart = millis();
    tonAktiv = true;
    digitalWrite(summerPin, HIGH);
}

void MenueAuswahlTon() { kurzerTon(70); }
void PongSound()       { kurzerTon(30); }
void SchussSound()     { kurzerTon(20); }

void GameOverSound()
{
    folgeLaeuft = true;
    folgeSchritt = 0;

    tonDauer = GAME_OVER_FOLGE[0];
    tonStart = millis();
    tonAktiv = true;
    digitalWrite(summerPin, HIGH);
}

void SoundAktualisieren()
{
    if (!tonAktiv)
    {
        return;
    }
    if (millis() - tonStart < tonDauer)
    {
        return;   // aktueller Schritt läuft noch
    }

    // Gibt es in der Folge noch einen nächsten Schritt?
    if (folgeLaeuft && folgeSchritt + 1 < GAME_OVER_LAENGE)
    {
        folgeSchritt++;
        tonDauer = GAME_OVER_FOLGE[folgeSchritt];
        tonStart = millis();

        // gerade Schritte (0, 2, 4 ...) = Ton an, ungerade = Pause
        if (folgeSchritt % 2 == 0)
        {
            digitalWrite(summerPin, HIGH);
        }
        else
        {
            digitalWrite(summerPin, LOW);
        }
        return;
    }

    // fertig
    digitalWrite(summerPin, LOW);
    tonAktiv = false;
    folgeLaeuft = false;
}