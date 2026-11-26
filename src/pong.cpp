#include "pong.h"
#include "Display.h"
#include "VectorFont.h"
#include "Sound.h"
#include "ArcadeFont.h"
#include <math.h>

const int FELD_GROESSE = 255;
const int FELD_MITTE = 128;

const int SCHLAEGER_BREITE = 15;
const int SCHLAEGER_HOEHE = 60;
const int SCHLAEGER_HALB = SCHLAEGER_HOEHE / 2;

const int BALL_RADIUS = 7;
const int BALL_TAKT_MS = 10;
const float BALL_START = 1.5f;
const float BALL_PLUS = 0.15f;
const float BALL_MAX = 3.8f;
const float MAX_WINKEL = 45.0f;

const int SIEG_PUNKTE = 10;


float ballX = FELD_MITTE;
float ballY = FELD_MITTE;
float ballWinkel = 0.0; 
float ballSpeed = BALL_START;  

Punkt schlaegerLinks = {0, 50};
Punkt schlaegerRechts = {240, 50};
int aktuellePunkteSpieler1 = 0;
int aktuellePunkteSpieler2 = 0;
bool Gewonnen = false;
int PotiLinks = 0;
int PotiRechts = 0;
bool spielGestartet = false;
bool gewinnerTextSichtbar = true;
bool countdownAktiv = false;
int countdownZahl = 3;
unsigned long letzterCountdownWechsel = 0;
unsigned long letztesWiederhohlen = 0;
bool kiZielGewaehlt = false;
int kiZielVersatz = 0;

void StarteCountdown()
{
    spielGestartet = false;
    countdownAktiv = true;
    countdownZahl = 3;
    letzterCountdownWechsel = millis();
}
void countdownAktualisieren()
{
    unsigned long jetzt = millis();
    if(countdownAktiv)
    {
        if(jetzt - letzterCountdownWechsel >= 1000)
        {
            letzterCountdownWechsel = jetzt;
            countdownZahl = countdownZahl - 1;

            if(countdownZahl == 0)
            {
                countdownAktiv = false;
                spielGestartet = true;
            }
        }
    }
}

void lesePoti() 
{
    PotiLinks = analogRead(36); 

    PotiRechts = analogRead(39); 

    schlaegerLinks.y = map(PotiLinks, 0, 4095, 0, FELD_GROESSE - SCHLAEGER_HOEHE);
    schlaegerRechts.y = map(PotiRechts, 0, 4095, 0, FELD_GROESSE - SCHLAEGER_HOEHE);
}
void lesePotiKI() 
{
    PotiLinks = analogRead(36); 
 
    schlaegerLinks.y = map(PotiLinks, 0, 4095, 0, FELD_GROESSE - SCHLAEGER_HOEHE);
}


bool ballBeruehrtSchlaeger(Punkt schlaeger)
{
    float naechsterX = ballX;
    float naechsterY = ballY;

    if (naechsterX < schlaeger.x)
    {
        naechsterX = schlaeger.x;
    }
    else if (naechsterX > schlaeger.x + SCHLAEGER_BREITE)
    {
        naechsterX = schlaeger.x + SCHLAEGER_BREITE;
    }

    // Y auf den Bereich des Schlägers begrenzen
    if (naechsterY < schlaeger.y)
    {
        naechsterY = schlaeger.y;
    }
    else if (naechsterY > schlaeger.y + SCHLAEGER_HOEHE)
    {
        naechsterY = schlaeger.y + SCHLAEGER_HOEHE;
    }


    float abstandX = ballX - naechsterX;
    float abstandY = ballY - naechsterY;

    return abstandX * abstandX + abstandY * abstandY
           <= BALL_RADIUS * BALL_RADIUS;
}

void resetPong() {
    ballX = FELD_MITTE;
    ballY = FELD_MITTE;
    ballWinkel = 0.0;
    ballSpeed = BALL_START;
    aktuellePunkteSpieler1 = 0;
    aktuellePunkteSpieler2 = 0;
    schlaegerLinks.y = 50;
    schlaegerRechts.y = 50;
    spielGestartet = false;
    Gewonnen = false;
    kiZielGewaehlt = false;
    kiZielVersatz = 0;
    StarteCountdown();

}



void KIBewegungLeicht()
{
    static unsigned long letzteKIBewegung = 0;
    unsigned long jetzt = millis();

    if (jetzt - letzteKIBewegung >= 8)
    {
        letzteKIBewegung = jetzt;

        // Reagiert erst, wenn der Ball in ihrer Hälfte ist
        if (ballX < FELD_MITTE)
        {
            return;
        }

        float schlaegerMitte = schlaegerRechts.y + SCHLAEGER_HALB;
        float unterschied = ballY - schlaegerMitte;

        if (unterschied > 3)
        {
            schlaegerRechts.y += 1;
        }
        else if (unterschied < -3)
        {
            schlaegerRechts.y -= 1;
        }
    }
}

void KIBewegungMittel()
{
    static unsigned long letzteKIBewegung = 0;
    unsigned long jetzt = millis();

    if (jetzt - letzteKIBewegung >= 11)
    {
        letzteKIBewegung = jetzt;

        // Reagiert ab dem ersten Viertel des Spielfelds
        if (ballX < FELD_GROESSE / 4)
        {
            return;
        }

        float schlaegerMitte = schlaegerRechts.y + SCHLAEGER_HALB;
        float unterschied = ballY - schlaegerMitte;

        if (unterschied > 3)
        {
            schlaegerRechts.y += 2;
        }
        else if (unterschied < -3)
        {
            schlaegerRechts.y -= 2;
        }
    }
}

void KIBewegungSchwer()
{
    static unsigned long letzteKIBewegung = 0;
    unsigned long jetzt = millis();

    float richtungX = cos(ballWinkel * PI / 180.0);

    // Ball fliegt von der KI weg:
    // Beim nächsten Anflug darf sie neu entscheiden.
    if (richtungX < 0)
    {
        kiZielGewaehlt = false;
        kiZielVersatz = 0;
    }

    // Einmal pro Anflug eine Schlagabsicht auswählen
    if (richtungX > 0 && !kiZielGewaehlt)
    {
        kiZielVersatz = 0;

        // Spieler steht oben → Ball nach unten spielen und umgekehrt
        if (schlaegerLinks.y + SCHLAEGER_HALB > FELD_MITTE)
        {
            kiZielVersatz = 15;
        }
        else if (schlaegerLinks.y + SCHLAEGER_HALB < FELD_MITTE)
        {
            kiZielVersatz = -25;
        }

        kiZielGewaehlt = true;
    }

    if (jetzt - letzteKIBewegung >= 8)
    {
        letzteKIBewegung = jetzt;

        // Gewünschte Schlägermitte:
        // bei positivem Versatz oberhalb des Balls
        float zielMitte = ballY + kiZielVersatz;

        // Schlägermitte kann nur innerhalb des Spielfelds liegen
        if (zielMitte < SCHLAEGER_HALB) zielMitte = SCHLAEGER_HALB;
        if (zielMitte > FELD_GROESSE - SCHLAEGER_HALB) zielMitte = FELD_GROESSE - SCHLAEGER_HALB;

        float schlaegerMitte = schlaegerRechts.y + SCHLAEGER_HALB;
        float unterschied = zielMitte - schlaegerMitte;

        if (unterschied > 3)
        {
            schlaegerRechts.y += 2;
        }
        else if (unterschied < -3)
        {
            schlaegerRechts.y -= 2;
        }
    }
}
void KIBewegung(int KISchwierigkeit)
{
    if (KISchwierigkeit == 1)
    {
        KIBewegungLeicht();
    }
    else if (KISchwierigkeit == 2)
    {
        KIBewegungMittel();
    }
    else if (KISchwierigkeit == 3)
    {
        KIBewegungSchwer();

    }
}
void gewinnerAnzeigen()
{
    unsigned long jetzt = millis();
    int gewinner = (aktuellePunkteSpieler1 >= SIEG_PUNKTE) ? 1 : 2;
    if (jetzt - letztesWiederhohlen >= 500)
    {
        letztesWiederhohlen = jetzt;
        gewinnerTextSichtbar = !gewinnerTextSichtbar;
    }
    arcadeZahl(40, 220, aktuellePunkteSpieler1, 3);
    arcadeZahl(210, 220, aktuellePunkteSpieler2, 3);
    zeichneRechteck(0, 0, FELD_GROESSE, FELD_GROESSE);
    zeichneSchlaeger(schlaegerLinks, SCHLAEGER_BREITE, SCHLAEGER_HOEHE);
    zeichneSchlaeger(schlaegerRechts, SCHLAEGER_BREITE, SCHLAEGER_HOEHE);

    if (gewinnerTextSichtbar)
    {
        arcadeText(40, 160, "SPIELER", 5);
        arcadeZahl(190, 160, gewinner, 5);
        arcadeText(61, 120, "GEWINNT", 5);
    }
}

void schlaegerBegrenzen()
{
    if (schlaegerLinks.y < 0)
        schlaegerLinks.y = 0;

    if (schlaegerLinks.y + SCHLAEGER_HOEHE > FELD_GROESSE)
        schlaegerLinks.y = FELD_GROESSE - SCHLAEGER_HOEHE;

    if (schlaegerRechts.y < 0)
        schlaegerRechts.y = 0;

    if (schlaegerRechts.y + SCHLAEGER_HOEHE > FELD_GROESSE)
        schlaegerRechts.y = FELD_GROESSE - SCHLAEGER_HOEHE;
}

void ballBewegen()
{
        float rad = ballWinkel * (PI / 180.0);
        float bewegungX = ballSpeed * cos(rad);
        float bewegungY = ballSpeed * sin(rad);

        ballX += bewegungX;
        ballY += bewegungY;

        if (bewegungX < 0 &&
            ballBeruehrtSchlaeger(schlaegerLinks))
        {
            PongSound();
            float treffer = ballY - (schlaegerLinks.y + SCHLAEGER_HALB);

            if (treffer > SCHLAEGER_HALB) treffer = SCHLAEGER_HALB;
            if (treffer < -SCHLAEGER_HALB) treffer = -SCHLAEGER_HALB;

            ballWinkel = (treffer / SCHLAEGER_HALB) * MAX_WINKEL;
            ballX = schlaegerLinks.x + SCHLAEGER_BREITE + BALL_RADIUS;

            ballSpeed += BALL_PLUS;
            if (ballSpeed > BALL_MAX) ballSpeed = BALL_MAX;
        }
        else if (bewegungX > 0 &&
                 ballBeruehrtSchlaeger(schlaegerRechts))
        {
            PongSound();
            float treffer = ballY - (schlaegerRechts.y + SCHLAEGER_HALB);

            if (treffer > SCHLAEGER_HALB) treffer = SCHLAEGER_HALB;
            if (treffer < -SCHLAEGER_HALB) treffer = -SCHLAEGER_HALB;

            ballWinkel = 180.0 - ((treffer / SCHLAEGER_HALB) * MAX_WINKEL);
            ballX = schlaegerRechts.x - BALL_RADIUS;

            ballSpeed += BALL_PLUS;
            if (ballSpeed > BALL_MAX) ballSpeed = BALL_MAX;
        }
        else if (ballX - BALL_RADIUS <= 0)
        {
            aktuellePunkteSpieler2++;

            ballX = FELD_MITTE;
            ballY = FELD_MITTE;
            ballWinkel = 0.0;
            ballSpeed = BALL_START;

            StarteCountdown();
        }
        else if (ballX + BALL_RADIUS >= FELD_GROESSE)
        {
            aktuellePunkteSpieler1++;

            ballX = FELD_MITTE;
            ballY = FELD_MITTE;
            ballWinkel = 180.0;
            ballSpeed = BALL_START;

            StarteCountdown();
        }
        if (spielGestartet)
        {
            float richtungY = sin(ballWinkel * PI / 180.0);

            if (ballY + BALL_RADIUS >= FELD_GROESSE)
            {
                PongSound();
                ballY = FELD_GROESSE - BALL_RADIUS;

                if (richtungY > 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
            else if (ballY - BALL_RADIUS <= 0)
            {
                PongSound();
                ballY = BALL_RADIUS;

                if (richtungY < 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
        }
}

void gewinnerPruefen()
{
    if (aktuellePunkteSpieler1 >= SIEG_PUNKTE ||
        aktuellePunkteSpieler2 >= SIEG_PUNKTE)
    {
        Gewonnen = true;
        spielGestartet = false;
        countdownAktiv = false;
        gewinnerTextSichtbar = true;
        letztesWiederhohlen = millis();
    }
}

void pongZeichnen()
{
    arcadeZahl(40, 220, aktuellePunkteSpieler1, 3);
    arcadeZahl(210, 220, aktuellePunkteSpieler2, 3);

    zeichneRechteck(0, 0, FELD_GROESSE, FELD_GROESSE);
    zeichneSchlaeger(schlaegerLinks, SCHLAEGER_BREITE, SCHLAEGER_HOEHE);
    zeichneSchlaeger(schlaegerRechts, SCHLAEGER_BREITE, SCHLAEGER_HOEHE);

    if (countdownAktiv)
    {
        arcadeZahl(118, 158, countdownZahl, 8);
    }
    else
    {
        ZeichneMittelstrich(FELD_MITTE, 0, FELD_GROESSE);
    }

    zeichneKreis(ballX, ballY, BALL_RADIUS);
}

// Ein Durchlauf von Pong, für beide Modi
void pongSpielen(bool gegenKI, int schwierigkeit)
{
    if (Gewonnen)
    {
        gewinnerAnzeigen();
        return;
    }
    if (gegenKI)
    {
        lesePotiKI();
    }
    else
    {
        lesePoti();
    }
    countdownAktualisieren();

    if (gegenKI && spielGestartet)
    {
        KIBewegung(schwierigkeit);
    }
    schlaegerBegrenzen();
    unsigned long jetzt = millis();
    static unsigned long letzteBewegung = 0;
    if (spielGestartet && jetzt - letzteBewegung >= BALL_TAKT_MS)
    {
        letzteBewegung = jetzt;
        ballBewegen();
    }
    gewinnerPruefen();
    pongZeichnen();
}

void loopPong()
{
    pongSpielen(false, 0);
}

void loopPongKI(int KISchwierigkeit)
{
    pongSpielen(true, KISchwierigkeit);
}
