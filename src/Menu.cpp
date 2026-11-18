#include "Menu.h"
#include "Display.h"
#include "VectorFont.h"
#include "pong.h"
#include "EndlessRunner.h"
#include "Sound.h"
extern int spielZustand; // wird in Main.cpp definiert
bool auswahlBereit = true;

// -----------------------------------------------------------------------------
// Hauptmenue: Pong, Flappy Bird und Endless Runner
// -----------------------------------------------------------------------------
void loopMenu()
{
    if (digitalRead(5) == LOW)
    {
        auswahlBereit = true; // Taster wurde losgelassen
    }
    static int pfeilY = 140;
    menueZeichnen();
    zeichneEins(215, 190, 50);
    zeichneRechteck(210, 185, 35, 60);
    ZeichnePingPong(125, 12, 40, 8);
    ZeichneFlappy(67.5, 12, 40, 8);
    ZeichneVertikalerStrich(0, 180, 255);
    ZeichneRunner(10, 12, 40, 8);
    int Pfeileingabe = analogRead(36);

    if (Pfeileingabe < 682)
    {
        pfeilY = 140;
    }

    else if (Pfeileingabe > 682 && Pfeileingabe < 1365)
    {
        pfeilY = 80;
    }
    else if (Pfeileingabe > 1365 && Pfeileingabe < 2047)
    {
        pfeilY = 25;
    }

    zeichneAuswahlPfeil(20, pfeilY, 15);
    if (pfeilY == 140 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 1;
    }

    else if (pfeilY == 80 && digitalRead(5) == HIGH && auswahlBereit)
    {

        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 7;
    }
    else if (pfeilY == 25 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 8;
    }
    else if (Pfeileingabe > 2047)
    {
        spielZustand = 9; // Zweites Menü
    }
    delayMicroseconds(3);
}

// -----------------------------------------------------------------------------
// Zweite Menue-Seite: Mario und Asteroids
// -----------------------------------------------------------------------------
void Menu2()
{
    int Pfeileingabe = analogRead(36);
    static int pfeilY = 140;
    menueZeichnen();
    ZeichneVertikalerStrich(0, 180, 255);
    zeichneZwei(215, 190, 50);
    zeichneRechteck(210, 185, 35, 60);
    ZeichneMario(125, 12, 40, 8);
    ZeichneAsteroids(67.5, 12, 40, 8);
    zeichneRechteck(0, 0, 255, 255);
    zeichneAuswahlPfeil(20, pfeilY, 15);
    if (Pfeileingabe < 2047)
    {
        spielZustand = 0; // Zurück zum Hauptmenü
    }
    if (Pfeileingabe > 2047 && Pfeileingabe < 2730)
    {
        pfeilY = 140;
    }
    else if (Pfeileingabe > 2730 && Pfeileingabe < 3412)
    {
        pfeilY = 80;
    }
    else if (Pfeileingabe > 3412)
    {
        pfeilY = 20;
    }

    delayMicroseconds(3);

    if (pfeilY == 80 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 10;
    }
}

// -----------------------------------------------------------------------------
// Pong: Spieler gegen Spieler oder KI
// -----------------------------------------------------------------------------
void MenuPvPoderKI()
{
    if (digitalRead(5) == LOW)
    {
        auswahlBereit = true;
    }
    static int pfeilY = 148;
    zeichneRechteck(0, 0, 255, 255);
    ZeichneModusPVP(40, 130, 176, 50);
    ZeichneModusKI(40, 60, 176, 50);
    int Pfeileingabe = analogRead(36);

    if (Pfeileingabe > 2200)
    {
        pfeilY = 78;
    }
    else if (Pfeileingabe < 1800)
    {
        pfeilY = 148;
    }
    zeichneAuswahlPfeil(20, pfeilY, 15);

    if (pfeilY == 148 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        resetPong();
        spielZustand = 3; // PvP
    }
    else if (pfeilY == 78 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 2; // Schwierigkeitsauswahl
    }
}

// -----------------------------------------------------------------------------
// Pong-KI: Schwierigkeitsgrad auswaehlen
// -----------------------------------------------------------------------------
void SchwierigkeitsgradAuswahl()
{
    if (digitalRead(5) == LOW)
    {
        auswahlBereit = true;
    }

    int Pfeileingabe = analogRead(36);
    int pfeilY;

    if (Pfeileingabe >= 2730)
    {
        pfeilY = 195;
    }
    else if (Pfeileingabe >= 1365)
    {
        pfeilY = 120;
    }
    else
    {
        pfeilY = 45;
    }

    zeichneRechteck(0, 0, 255, 255);
    ZeichneModusLeicht(40, 170, 176, 50);
    ZeichneModusMittel(40, 95, 176, 50);
    ZeichneModusSchwer(40, 20, 176, 50);
    zeichneAuswahlPfeil(20, pfeilY, 15);

    if (digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        resetPong();

        if (pfeilY == 195)
        {
            spielZustand = 4; // Leicht
        }
        else if (pfeilY == 120)
        {
            spielZustand = 5; // Mittel
        }
        else
        {
            spielZustand = 6; // Schwer
        }
    }
}
