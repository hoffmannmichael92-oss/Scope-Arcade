#include <Arduino.h>
#include "Display.h"
#include "VectorFont.h"
#include "pong.h"
#include "Menu.h"
#include "Radar.h"
#include "EndlessRunner.h"
#include "FlappyBird.h"
#include "Asteroids.h"
#include "Sound.h"
// Spielzustaende:
//  0: Hauptmenue        1: Pong-Moduswahl     2: KI-Schwierigkeit
//  3: Pong PvP          4: KI leicht          5: KI mittel
//  6: KI schwer         7: Flappy Bird        8: Endless Runner
//  9: Zweite Menue-Seite                     10: Asteroids
int spielZustand = 0;
const int potiPin = 36;
// -----------------------------------------------------------------------------
// Initialisierung: Display, Eingaben und Sound
// -----------------------------------------------------------------------------
void setup()
{
    Serial.begin(115200);
    initDisplay();
    // Joystick 1
    pinMode(14, INPUT);
    pinMode(12, INPUT);

    // Joystick 2
    pinMode(34, INPUT);
    pinMode(35, INPUT);

    // Taster: passend zu deiner bisherigen Abfrage HIGH = gedrückt.
    // Voraussetzung: externe Pull-down-Widerstände sind vorhanden.
    pinMode(2, INPUT);
    pinMode(5, INPUT);

    // Summer
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    SoundInitialisieren();

}

// -----------------------------------------------------------------------------
// Hauptablauf: aktuellen Spielzustand ausfuehren
// -----------------------------------------------------------------------------
void loop()
{
    strahlParken();
    SoundAktualisieren();
    // Hauptmenue
    if (spielZustand == 0)
    {
        loopMenu();
    }
    // Pong-Moduswahl
    else if (spielZustand == 1)
    {
        MenuPvPoderKI();
    }
    // KI-Schwierigkeit
    else if (spielZustand == 2)
    {
        SchwierigkeitsgradAuswahl();
    }
    // Pong PvP
    else if (spielZustand == 3)
    {
        loopPong();
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            MenueAuswahlTon();
            resetPong();
            spielZustand = 0;
        }
    }

    // Pong KI: leicht
    else if (spielZustand == 4)
    {
        loopPongKI(1); // leicht
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            MenueAuswahlTon();
            resetPong();
            spielZustand = 0;
        }
    }
    // Pong KI: mittel
    else if (spielZustand == 5)
    {

        loopPongKI(2); // mittel
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            MenueAuswahlTon();
            resetPong();
            spielZustand = 0;
        }
    }

    // Pong KI: schwer
    else if (spielZustand == 6)
    {
        loopPongKI(3); // schwer
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            MenueAuswahlTon();
            resetPong();
            spielZustand = 0;
        }
    }

    // Flappy Bird
    else if (spielZustand == 7)
    {
        loopFlappy();
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            ResetFlappy();
            MenueAuswahlTon();
            spielZustand = 0;
        }
    }
    // Endless Runner
    else if (spielZustand == 8)
    {
        loopEndlessRunner();
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            ResetEndlessRunner();
            MenueAuswahlTon();
            spielZustand = 0;
        }
    }
    // Zweite Menue-Seite
    else if (spielZustand == 9)
    {
        Menu2();
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
    }
    // Asteroids
    else if (spielZustand == 10)
    {
        loopAsteroids();
        if (digitalRead(5) == LOW)
        {
            auswahlBereit = true;
        }
        if (digitalRead(5) == HIGH && auswahlBereit)
        {
            auswahlBereit = false;
            ResetAsteroids();
            MenueAuswahlTon();
            spielZustand = 9;
        }
    }

}
