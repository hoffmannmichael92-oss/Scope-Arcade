#include "pong.h"
#include "Display.h"
#include "VectorFont.h"
#include "Sound.h"
#include <math.h>

// 1:1 deine Variablen
float ballX = 128;
float ballY = 128;
float ballWinkel = 0.0; // In Grad (0° = nach rechts)
float ballSpeed = 1.0;  // Feste Ball-Geschwindigkeit
int meinRadius = 15;

Punkt schlaegerLinks = {0, 50};
Punkt schlaegerRechts = {240, 50};
int aktuellePunkteSpieler1 = 0;
int aktuellePunkteSpieler2 = 0;
bool Gewonnen = false;
int PotiLinks = 0;
int PotiRechts = 0;
int KISchwierigkeit = 1; // 1 = leicht, 2 = mittel, 3 = schwer
bool spielGestartet = false;
bool gewinnerTextSichtbar = true;
bool countdownAktiv = false;
int countdownZahl = 3;
unsigned long letzterCountdownWechsel = 0;
unsigned long letztesWiederhohlen = 0;
bool Pongsound = false;

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

void lesePoti() {
    // 1. Analogwerte einlesen
    PotiLinks = analogRead(36); 

    PotiRechts = analogRead(39); 

    schlaegerLinks.y = map(PotiLinks, 0, 4095, 0, 255 - 60);
    schlaegerRechts.y = map(PotiRechts, 0, 4095, 0, 255 - 60);
}
void lesePotiKI() {
    // 1. Analogwerte einlesen
    PotiLinks = analogRead(36); 
 
    schlaegerLinks.y = map(PotiLinks, 0, 4095, 0, 255 - 60);
}



bool ballBeruehrtSchlaeger(Punkt schlaeger)
{
    // Zunächst den Ballmittelpunkt übernehmen
    float naechsterX = ballX;
    float naechsterY = ballY;

    // X auf den Bereich des Schlägers begrenzen
    if (naechsterX < schlaeger.x)
    {
        naechsterX = schlaeger.x;
    }
    else if (naechsterX > schlaeger.x + 15)
    {
        naechsterX = schlaeger.x + 15;
    }

    // Y auf den Bereich des Schlägers begrenzen
    if (naechsterY < schlaeger.y)
    {
        naechsterY = schlaeger.y;
    }
    else if (naechsterY > schlaeger.y + 60)
    {
        naechsterY = schlaeger.y + 60;
    }

    // Abstand vom Ballmittelpunkt zum nächsten Schlägerpunkt
    float abstandX = ballX - naechsterX;
    float abstandY = ballY - naechsterY;

    return abstandX * abstandX + abstandY * abstandY
           <= meinRadius * meinRadius;
}

// Wird beim Wechsel ins Menü / Neustart aufgerufen
void resetPong() {
    ballX = 128;
    ballY = 128;
    ballWinkel = 0.0;
    ballSpeed = 1.0;
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

void loopPong()
{
    if(ballBeruehrtSchlaeger(schlaegerLinks) || ballBeruehrtSchlaeger(schlaegerRechts))
    {
        PongSound();
    }
    
    // 1. Gewinneranzeige
    if (Gewonnen)
    {
        unsigned long jetzt = millis();
        int gewinner = (aktuellePunkteSpieler1 >= 10) ? 1 : 2;

        if (jetzt - letztesWiederhohlen >= 500)
        {
            letztesWiederhohlen = jetzt;
            gewinnerTextSichtbar = !gewinnerTextSichtbar;
        }

        ZerlegeZiffer(20, 230, 12, aktuellePunkteSpieler1);
        ZerlegeZiffer(230, 230, 12, aktuellePunkteSpieler2);
        zeichneRechteck(0, 0, 255, 255);
        zeichneSchlaeger(schlaegerLinks, 15, 60);
        zeichneSchlaeger(schlaegerRechts, 15, 60);

        if (gewinnerTextSichtbar)
        {
            ZeichneGewinner(40, 100, 175, 60, gewinner);
        }

        return;
    }

    // 2. Eingaben und Countdown aktualisieren
    lesePoti();
    countdownAktualisieren();

    // 3. Schläger auf das Spielfeld begrenzen
    if (schlaegerLinks.y < 0)
        schlaegerLinks.y = 0;

    if (schlaegerLinks.y + 60 > 255)
        schlaegerLinks.y = 255 - 60;

    if (schlaegerRechts.y < 0)
        schlaegerRechts.y = 0;

    if (schlaegerRechts.y + 60 > 255)
        schlaegerRechts.y = 255 - 60;

    // Bewegung und Kollisionen nur im laufenden Spiel
    if (spielGestartet)
    {
        // 4. Ball bewegen
        float rad = ballWinkel * (PI / 180.0);
        float bewegungX = ballSpeed * cos(rad);
        float bewegungY = ballSpeed * sin(rad);

        ballX += bewegungX;
        ballY += bewegungY;

        // 5. Linker Schläger
        if (bewegungX < 0 &&
            ballBeruehrtSchlaeger(schlaegerLinks))
        {
            float treffer = ballY - (schlaegerLinks.y + 30);

            if (treffer > 30) treffer = 30;
            if (treffer < -30) treffer = -30;

            ballWinkel = (treffer / 30.0) * 45.0;
            ballX = schlaegerLinks.x + 15 + meinRadius;

            ballSpeed += 0.2;
            if (ballSpeed > 3.0) ballSpeed = 3.0;
        }
        // Rechter Schläger
        else if (bewegungX > 0 &&
                 ballBeruehrtSchlaeger(schlaegerRechts))
        {
            float treffer = ballY - (schlaegerRechts.y + 30);

            if (treffer > 30) treffer = 30;
            if (treffer < -30) treffer = -30;

            ballWinkel = 180.0 - ((treffer / 30.0) * 45.0);
            ballX = schlaegerRechts.x - meinRadius;

            ballSpeed += 0.2;
            if (ballSpeed > 3.0) ballSpeed = 3.0;
        }
        // 6. Links verfehlt: Punkt für Spieler 2
        else if (ballX - meinRadius <= 0)
        {
            aktuellePunkteSpieler2++;

            ballX = 128;
            ballY = 128;
            ballWinkel = 0.0;
            ballSpeed = 1.0;

            StarteCountdown();
        }
        // Rechts verfehlt: Punkt für Spieler 1
        else if (ballX + meinRadius >= 255)
        {
            aktuellePunkteSpieler1++;

            ballX = 128;
            ballY = 128;
            ballWinkel = 180.0;
            ballSpeed = 1.0;

            StarteCountdown();
        }

        // 7. Obere und untere Bande
        if (spielGestartet)
        {
            float richtungY = sin(ballWinkel * PI / 180.0);

            if (ballY + meinRadius >= 255)
            {
                ballY = 255 - meinRadius;

                if (richtungY > 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
            else if (ballY - meinRadius <= 0)
            {
                ballY = meinRadius;

                if (richtungY < 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
        }
    }

    // 8. Gewinner feststellen
    if (aktuellePunkteSpieler1 >= 10 ||
        aktuellePunkteSpieler2 >= 10)
    {
        Gewonnen = true;
        spielGestartet = false;
        countdownAktiv = false;
        gewinnerTextSichtbar = true;
        letztesWiederhohlen = millis();
    }

    // 9. Spielfeld und Punktestand zeichnen
    ZerlegeZiffer(20, 230, 12, aktuellePunkteSpieler1);
    ZerlegeZiffer(230, 230, 12, aktuellePunkteSpieler2);

    zeichneRechteck(0, 0, 255, 255);
    zeichneSchlaeger(schlaegerLinks, 15, 60);
    zeichneSchlaeger(schlaegerRechts, 15, 60);

    if (Gewonnen)
    {
        int gewinner = (aktuellePunkteSpieler1 >= 10) ? 1 : 2;
        ZeichneGewinner(40, 100, 175, 60, gewinner);
    }
    else
    {
        if (countdownAktiv)
        {
            if (countdownZahl == 1)
            {
                positioniereStrahl(138, 158);
            }
            else
            {
                positioniereStrahl(118, 198);
            }

            zeichneZiffer(118, 158, 40, countdownZahl);
        }
        else
        {
            ZeichneMittelstrich(128, 0, 255);
        }

        zeichneKreis(ballX, ballY, meinRadius);
    }
}

void KIBewegungLeicht()
{
    if(ballBeruehrtSchlaeger(schlaegerLinks) || ballBeruehrtSchlaeger(schlaegerRechts))
    {
        PongSound();
    }
    static unsigned long letzteKIBewegung = 0;
    unsigned long jetzt = millis();

    if (jetzt - letzteKIBewegung >= 20)
    {
        letzteKIBewegung = jetzt;

        float schlaegerMitte = schlaegerRechts.y + 30;
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
void KIBewegungMittel()
{
    if(ballBeruehrtSchlaeger(schlaegerLinks) || ballBeruehrtSchlaeger(schlaegerRechts))
    {
        PongSound();
    }
    static unsigned long letzteKIBewegung = 0;
    unsigned long jetzt = millis();

    if (jetzt - letzteKIBewegung >= 15)
    {
        letzteKIBewegung = jetzt;

        float schlaegerMitte = schlaegerRechts.y + 30;
        float unterschied = ballY - schlaegerMitte;

        if (unterschied > 3)
        {
            schlaegerRechts.y += 3;
        }
        else if (unterschied < -3)
        {
            schlaegerRechts.y -= 3;
        }
    }
}
void KIBewegungSchwer()
{
    if(ballBeruehrtSchlaeger(schlaegerLinks) || ballBeruehrtSchlaeger(schlaegerRechts))
    {
        PongSound();
    }
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

        // Mittelpunkt des Spielerschlägers liegt
        // oberhalb der Spielfeldmitte.
        if (schlaegerLinks.y + 30 > 128)
        {

            kiZielVersatz = 15;

        }
        else if(schlaegerLinks.y + 30 < 128)
        {
                kiZielVersatz = -25;
            
        }

        kiZielGewaehlt = true;
    }

    if (jetzt - letzteKIBewegung >= 10)
    {
        letzteKIBewegung = jetzt;

        // Gewünschte Schlägermitte:
        // bei positivem Versatz oberhalb des Balls
        float zielMitte = ballY + kiZielVersatz;

        // Schlägermitte kann nur zwischen 30 und 225 liegen
        if (zielMitte < 30) zielMitte = 30;
        if (zielMitte > 225) zielMitte = 225;

        float schlaegerMitte = schlaegerRechts.y + 30;
        float unterschied = zielMitte - schlaegerMitte;

        if (unterschied > 3)
        {
            schlaegerRechts.y += 3;
        }
        else if (unterschied < -3)
        {
            schlaegerRechts.y -= 3;
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


void loopPongKI(int KISchwierigkeit)
{
    if(ballBeruehrtSchlaeger(schlaegerLinks) || ballBeruehrtSchlaeger(schlaegerRechts))
    {
        PongSound();
    }
    // 1. Gewinneranzeige
    if (Gewonnen)
    {
        unsigned long jetzt = millis();
        int gewinner = (aktuellePunkteSpieler1 >= 10) ? 1 : 2;

        if (jetzt - letztesWiederhohlen >= 500)
        {
            letztesWiederhohlen = jetzt;
            gewinnerTextSichtbar = !gewinnerTextSichtbar;
        }

        ZerlegeZiffer(20, 230, 12, aktuellePunkteSpieler1);
        ZerlegeZiffer(230, 230, 12, aktuellePunkteSpieler2);
        zeichneRechteck(0, 0, 255, 255);
        zeichneSchlaeger(schlaegerLinks, 15, 60);
        zeichneSchlaeger(schlaegerRechts, 15, 60);

        if (gewinnerTextSichtbar)
        {
            ZeichneGewinner(40, 100, 175, 60, gewinner);
        }

        return;
    }

    // 2. Spielereingabe, Countdown und KI aktualisieren
    lesePotiKI();
    countdownAktualisieren();

    if (spielGestartet)
    {
        KIBewegung(KISchwierigkeit);
    }

    // 3. Schläger auf das Spielfeld begrenzen
    if (schlaegerLinks.y < 0)
        schlaegerLinks.y = 0;

    if (schlaegerLinks.y + 60 > 255)
        schlaegerLinks.y = 255 - 60;

    if (schlaegerRechts.y < 0)
        schlaegerRechts.y = 0;

    if (schlaegerRechts.y + 60 > 255)
        schlaegerRechts.y = 255 - 60;

    // Bewegung und Kollisionen nur im laufenden Spiel
    if (spielGestartet)
    {
        // 4. Ball bewegen
        float rad = ballWinkel * (PI / 180.0);
        float bewegungX = ballSpeed * cos(rad);
        float bewegungY = ballSpeed * sin(rad);

        ballX += bewegungX;
        ballY += bewegungY;

        // 5. Linker Schläger
        if (bewegungX < 0 &&
            ballBeruehrtSchlaeger(schlaegerLinks))
        {
            float treffer = ballY - (schlaegerLinks.y + 30);

            if (treffer > 30) treffer = 30;
            if (treffer < -30) treffer = -30;

            ballWinkel = (treffer / 30.0) * 45.0;
            ballX = schlaegerLinks.x + 15 + meinRadius;

            ballSpeed += 0.2;
            if (ballSpeed > 3.0) ballSpeed = 3.0;
        }
        // Rechter Schläger: KI
        else if (bewegungX > 0 &&
                 ballBeruehrtSchlaeger(schlaegerRechts))
        {
            float treffer = ballY - (schlaegerRechts.y + 30);

            if (treffer > 30) treffer = 30;
            if (treffer < -30) treffer = -30;

            ballWinkel = 180.0 - ((treffer / 30.0) * 45.0);
            ballX = schlaegerRechts.x - meinRadius;

            ballSpeed += 0.2;
            if (ballSpeed > 3.0) ballSpeed = 3.0;
        }
        // 6. Spieler verfehlt: Punkt für die KI
        else if (ballX - meinRadius <= 0)
        {
            aktuellePunkteSpieler2++;

            ballX = 128;
            ballY = 128;
            ballWinkel = 0.0;
            ballSpeed = 1.0;

            StarteCountdown();
        }
        // KI verfehlt: Punkt für Spieler 1
        else if (ballX + meinRadius >= 255)
        {
            aktuellePunkteSpieler1++;

            ballX = 128;
            ballY = 128;
            ballWinkel = 180.0;
            ballSpeed = 1.0;

            StarteCountdown();
        }

        // 7. Obere und untere Bande
        if (spielGestartet)
        {
            float richtungY = sin(ballWinkel * PI / 180.0);

            if (ballY + meinRadius >= 255)
            {
                ballY = 255 - meinRadius;

                if (richtungY > 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
            else if (ballY - meinRadius <= 0)
            {
                ballY = meinRadius;

                if (richtungY < 0)
                {
                    ballWinkel = -ballWinkel;
                }
            }
        }
    }

    // 8. Gewinner feststellen
    if (aktuellePunkteSpieler1 >= 10 ||
        aktuellePunkteSpieler2 >= 10)
    {
        Gewonnen = true;
        spielGestartet = false;
        countdownAktiv = false;
        gewinnerTextSichtbar = true;
        letztesWiederhohlen = millis();
    }

    // 9. Spielfeld und Punktestand zeichnen
    ZerlegeZiffer(20, 230, 12, aktuellePunkteSpieler1);
    ZerlegeZiffer(230, 230, 12, aktuellePunkteSpieler2);

    zeichneRechteck(0, 0, 255, 255);
    zeichneSchlaeger(schlaegerLinks, 15, 60);
    zeichneSchlaeger(schlaegerRechts, 15, 60);

    if (Gewonnen)
    {
        int gewinner = (aktuellePunkteSpieler1 >= 10) ? 1 : 2;
        ZeichneGewinner(40, 100, 175, 60, gewinner);
    }
    else
    {
        if (countdownAktiv)
        {
            if (countdownZahl == 1)
            {
                positioniereStrahl(138, 158);
            }
            else
            {
                positioniereStrahl(118, 198);
            }

            zeichneZiffer(118, 158, 40, countdownZahl);
        }
        else
        {
            ZeichneMittelstrich(128, 0, 255);
        }

        zeichneKreis(ballX, ballY, meinRadius);
    }
}
