#include "EndlessRunner.h"
#include "VectorFont.h"
#include "Display.h"
#include "ArcadeFont.h"

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
    bool istDoppelt;     
};

struct Grashalm
{
    int x;
    int y;
    int breite;
    float geschwindigkeit;
};


const float START_TEMPO   = -3.5f;
const float TEMPO_PLUS    = -0.15f;
const float MAX_TEMPO     = -8.0f;
const float SPRUNGKRAFT   = 5.2f;
const float SCHWERKRAFT   = 0.4f;
const float SCHNELLFALLEN = 0.8f;
const int   NACHSICHT     = 2;

Grashalm grashalm1   = {0, 30, 255, 1.5};
Hindernis hindernis = {255.0, 30, false, 21, 28, START_TEMPO, false, false, false};
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
    hindernis.istDoppelt = false;

    // jedes dritte Hindernis ist eine Fledermaus
    hindernis.istFledermaus = (random(0, 3) == 0);

    if (hindernis.istFledermaus)
    {
        hindernis.y = 50;
        hindernis.breite = 24;
        hindernis.hoehe = 14;
    }
    else
    {
        hindernis.y = 30;
        hindernis.breite = 21;
        hindernis.hoehe = 28;

        // ab Tempo 5: jeder dritte Kaktus ist doppelt so breit
        if (hindernis.geschwindigkeit <= -5.0f && random(0, 3) == 0)
        {
            hindernis.istDoppelt = true;
            hindernis.breite = 42;
        }
    }
}
void ResetEndlessRunner()
{
    hindernis.geschwindigkeit = START_TEMPO;
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
    ZeichneGrashalme(grashalm1.x, grashalm1.y, grashalm1.breite);
    zeichneRechteck(0, 0, 255, 255);
    zeichneLinie(0, 30, 255, 30); 
    zeichneDino(spieler1.x, spieler1.y, spieler1.laufBild, spieler1.DinoGeduckt);
    arcadeZahl(115, 180, spieler1.aktuellePunkteSpieler1, 5);
    
    if (hindernis.istFledermaus)
    {
        zeichneFledermaus(hindernis.x, hindernis.y, hindernis.laufbild);
    }
    else
    {
        zeichneKaktus(hindernis.x, hindernis.y);
        if (hindernis.istDoppelt)
        {
            zeichneKaktus(hindernis.x + 21, hindernis.y);
        }
    }
    if (verloren)
    {
        arcadeText(20, 100, "GAME OVER", 6);
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
   const int nachsicht = NACHSICHT;

if ((spieler1.x + 5 + nachsicht) < hindernis.x + hindernis.breite - nachsicht &&
    spieler1.x + spieler1.breite - nachsicht > hindernis.x + nachsicht &&
    (spieler1.y + 2 + nachsicht) < hindernis.y + hindernis.hoehe - nachsicht &&
    spieler1.y + spieler1.hoehe - nachsicht > hindernis.y + nachsicht)
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
        if (hindernis.x < 0)
        {
            hindernis.geschwindigkeit += TEMPO_PLUS;
            if (hindernis.geschwindigkeit < MAX_TEMPO)
            {
                hindernis.geschwindigkeit = MAX_TEMPO;
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
            spieler1.geschwindigkeit = SPRUNGKRAFT;
        }

        
        if (Pfeileingabe > 300 && spieler1.y > 30)
        {
            spieler1.geschwindigkeit -= SCHNELLFALLEN;
        }

        spieler1.y += spieler1.geschwindigkeit;
        spieler1.geschwindigkeit -= SCHWERKRAFT;

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




