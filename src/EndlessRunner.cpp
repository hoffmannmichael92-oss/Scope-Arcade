#include "EndlessRunner.h"
#include "VectorFont.h"
#include "Display.h"

struct Spieler
{
    float x;
    float y;
    int breite;
    int hoehe;
    float geschwindigkeit;
    bool laufBild;
    unsigned long letzteAnimation;
    bool DinoGeduckt;
    int aktuellePunkteSpieler1;
};



struct Hindernis
{
    float x;
    int y;
    bool laufbild;
    int breite;
    int hoehe;
    float geschwindigkeit;
    bool punktGezaehlt;
    bool istFledermaus;
};
struct Grashalm
{
    int x;
    int y;
    int breite;
    float geschwindigkeit;
};


Grashalm grashalm1   = {0, 30, 255, 1.5};
Hindernis hindernis = {200.0, 30, false, 16, 13, -2.0f, false, false};
Spieler spieler1 = {40, 30, 25, 36, 0.0, false, 0, false, 0};
bool laufBild = true; 
bool SpielGestartet = false;
bool verloren = false;
unsigned long letzteBewegung = 0;
bool JoystickBereit = true; // Merker, ob der Joystick wieder in der Mitte war

void HindernisSpanwnen()
{
    hindernis.x = 255;
    hindernis.punktGezaehlt = false;
    hindernis.laufbild = false;

    hindernis.istFledermaus = (random(0,2) == 1);

    if(hindernis.istFledermaus)
    {
        hindernis.y = 60;
        hindernis.breite = 24;
        hindernis.hoehe = 14;
    }
    else
    {
        hindernis.y = 30;
        hindernis.breite = 21;
        hindernis.hoehe = 28;
    }

}
void ResetEndlessRunner()
{
    hindernis.geschwindigkeit = -2.0f;
    HindernisSpanwnen();

    spieler1.y = 30;
    spieler1.geschwindigkeit = 0;
    spieler1.aktuellePunkteSpieler1 = 0;
    spieler1.DinoGeduckt = false;
    spieler1.hoehe = 36;
    verloren = false;
    SpielGestartet = false;
    JoystickBereit = true; 
    
}


void RunnerZeichnen(int Pfeileingabe)
{   
    zeichneRechteck(
    spieler1.x + 5,
    spieler1.y + 2,
    spieler1.breite - 5,
    spieler1.hoehe - 2
);

zeichneRechteck(
    hindernis.x,
    hindernis.y,
    hindernis.breite,
    hindernis.hoehe
);
    ZeichneGrashalme(grashalm1.x, grashalm1.y, grashalm1.breite);
    zeichneRechteck(0, 0, 255, 255);
    zeichneLinie(0, 30, 255, 30); 
    zeichneDino(spieler1.x, spieler1.y, spieler1.laufBild, spieler1.DinoGeduckt);
    ZerlegeZiffer(115, 180, 26, spieler1.aktuellePunkteSpieler1);
    
    if (hindernis.istFledermaus)
    {
        zeichneFledermaus(hindernis.x, hindernis.y, hindernis.laufbild);
    }
    else
    {
        zeichneKaktus(hindernis.x, hindernis.y);
    }
    if (verloren)
    {
        ZeichneGameOver(40, 100, 175, 60);
        SpielGestartet = false;
    }
}

void AnimationenAktualisieren()
{
    unsigned long aktuelleMillis = millis();
    if (aktuelleMillis - spieler1.letzteAnimation >= 200 && SpielGestartet)
    {
        spieler1.letzteAnimation = aktuelleMillis;
        hindernis.laufbild = !hindernis.laufbild;
        spieler1.laufBild = !spieler1.laufBild;
        
    }
}
void KollisionPruefen()
{
   if ((spieler1.x + 5) < hindernis.x + hindernis.breite &&
    spieler1.x + spieler1.breite > hindernis.x &&
    (spieler1.y + 2) < hindernis.y + hindernis.hoehe &&
    spieler1.y + spieler1.hoehe > hindernis.y)
   {
        verloren = true;
        SpielGestartet = false; // Spiel sofort stoppen
        JoystickBereit = false;
        return;
   }
   else if (hindernis.x + hindernis.breite < spieler1.x && !hindernis.punktGezaehlt)
    {
         spieler1.aktuellePunkteSpieler1++; // Punkte erhöhen
         hindernis.punktGezaehlt = true;
    }

}
void BewegungAktualisieren(int Pfeileingabe)
{    

    unsigned long aktuelleMillisBewegung = millis();
    if (!SpielGestartet && JoystickBereit &&
    (Pfeileingabe < -300 || Pfeileingabe > 300))
    {
        if (verloren)
        {
            ResetEndlessRunner();
        }

        SpielGestartet = true;
        verloren = false;
    }
    if (aktuelleMillisBewegung - letzteBewegung >= 20 && SpielGestartet)
    {
        letzteBewegung = aktuelleMillisBewegung;
        hindernis.x += hindernis.geschwindigkeit;
        if(hindernis.x < 0)
        {
            hindernis.geschwindigkeit = hindernis.geschwindigkeit - 0.15f;
            if (hindernis.geschwindigkeit < -5.0)
        {
            hindernis.geschwindigkeit = -5.0f;
        }
            HindernisSpanwnen();
        }
        
        if (Pfeileingabe > 300 && spieler1.y == 30)
        {
            spieler1.DinoGeduckt = true;
            spieler1.hoehe = 20;
        }
        else
        {
            spieler1.DinoGeduckt = false;
            spieler1.hoehe = 36;
        }
        if (Pfeileingabe < -300 && JoystickBereit && spieler1.y == 30)
        {
            JoystickBereit = false;
            spieler1.geschwindigkeit = 4.8f;
        }
    
        spieler1.y += spieler1.geschwindigkeit;
        spieler1.geschwindigkeit -= 0.3f;

        if (spieler1.y <= 30)
        {
            spieler1.y = 30;
            spieler1.geschwindigkeit = 0;
        }
    }
}
    

void loopEndlessRunner()
{
    int Joystickmitte = 1850;
    int Pfeileingabe = analogRead(34) - Joystickmitte;

    if (abs(Pfeileingabe) < 200)
    {
        JoystickBereit = true;
    }

    BewegungAktualisieren(Pfeileingabe);

    if (SpielGestartet)
    {
        KollisionPruefen();
    }  
    AnimationenAktualisieren();
    RunnerZeichnen(Pfeileingabe);
    Serial.println(Pfeileingabe);
}




