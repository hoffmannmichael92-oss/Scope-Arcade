#include "Menu.h"
#include "Display.h"
#include "VectorFont.h"
#include "ArcadeFont.h"
#include "pong.h"
#include "EndlessRunner.h"
#include "Sound.h"
extern int spielZustand; 
bool auswahlBereit = true;


static void menuePunkt(int kastenY, const char* text)
{
    const int skala = 4;
    const int kastenHoehe = 50;
    const int textHoehe = 4 * skala;   // 5 Zeilen -> 4 Abstaende

    zeichneRechteck(40, kastenY, 176, kastenHoehe);
    arcadeTextMitte(kastenY + (kastenHoehe - textHoehe) / 2, text, skala);
}

static void menueKopf(int seite)
{
    zeichneRechteck(0, 0, 255, 255);

    zeichneRechteck(59, 185, 138, 60);
    arcadeTextMitte(201, "MENU", 7);

    // Seitennummer im Kasten rechts oben
    zeichneRechteck(210, 185, 35, 60);
    arcadeZiffer(216, 199, seite, 8);

    ZeichneVertikalerStrich(0, 180, 255);
}


void loopMenu()
{
    int Pfeileingabe = analogRead(36);
    if (digitalRead(5) == LOW)
    {
        auswahlBereit = true; 
    }
    static int pfeilY = 140;

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

    menueKopf(1);
    menuePunkt(120, "PING PONG");
    menuePunkt(62, "FLAPPY");
    menuePunkt(5, "RUNNER");
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
        spielZustand = 9; 
    }
}

void Menu2()
{
    int Pfeileingabe = analogRead(36);
    static int pfeilY = 140;

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

    menueKopf(2);
    menuePunkt(120, "MARIO");
    menuePunkt(62, "ASTEROIDS");
    zeichneAuswahlPfeil(20, pfeilY, 15);

    if (pfeilY == 80 && digitalRead(5) == HIGH && auswahlBereit)
    {
        auswahlBereit = false;
        MenueAuswahlTon();
        spielZustand = 10;
    }
}


void MenuPvPoderKI()
{
    int Pfeileingabe = analogRead(36);
    if (digitalRead(5) == LOW)
    {
        auswahlBereit = true;
    }
    static int pfeilY = 148;

    if (Pfeileingabe > 2200)
    {
        pfeilY = 78;
    }
    else if (Pfeileingabe < 1800)
    {
        pfeilY = 148;
    }

    zeichneRechteck(0, 0, 255, 255);
    arcadeTextMitte(205, "PONG", 6);
    menuePunkt(130, "PVP");
    menuePunkt(60, "KI");
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
    menuePunkt(170, "LEICHT");
    menuePunkt(95, "MITTEL");
    menuePunkt(20, "SCHWER");
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