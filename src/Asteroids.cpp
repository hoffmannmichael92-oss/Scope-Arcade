#include <Arduino.h>
#include "Display.h"
#include "VectorFont.h"
#include "Asteroids.h"
#include <math.h>
#include "Sound.h"
#include "ArcadeFont.h"
struct Raumschiff
{
    float x;
    float y;
    float Hoehe;
    float Breite;
    float GeschwindigkeitX;
    float GeschwindigkeitY;
    float Winkel;
    int leben;
    int Punkte;
};

struct Asteroid
{
    float x;
    float y;
    float geschwindigkeitX;
    float geschwindigkeitY;
    int groesse;
    bool AsteroidAktiv;
};

struct Schuesse
{
    float x;
    float y;
    float geschwindigkeitX;
    float geschwindigkeitY;
    bool aktiv;
};

struct JoystickWerte
{
    int x;
    int y;
};

unsigned long jetzt = 0;
bool auswahlbereit = true;
JoystickWerte Werte {0, 0};
const int MAX_ASTEROIDEN = 20;
const int MAX_SCHUESSE = 10;
const int MAX_LEBEN = 3;
const int FELD_OBEN = 230; 

const int GROSS = 18;
const int MITTEL = 12;
const int KLEIN = 7;
const int PunkteGROSS = 20;
const int PunkteMITTEL = 50;
const int PunkteKLEIN = 100;
int Tasterpin = 2;
static bool verloren = false; 
Asteroid Asteroid1[MAX_ASTEROIDEN] = {};
Raumschiff Raumschiff1
{
    128, 128,       // Mittelpunkt
    15, 10,         // Höhe und Breite der Basis
    0.0f, 0.0f,     // Geschwindigkeit
    0.0f ,           // Winkel
    MAX_LEBEN, 0       // Leben und Punkte
};
Schuesse Schuss[MAX_SCHUESSE]{};
void AsteroidsSpawnen(Asteroid &Asteroid1);
void ResetAsteroids()
{
    jetzt = millis();
    Raumschiff1.x = 128;
    Raumschiff1.y = 128;
    Raumschiff1.GeschwindigkeitX = 0.0f;
    Raumschiff1.GeschwindigkeitY = 0.0f;
    Raumschiff1.Winkel = 0;
    Raumschiff1.leben = MAX_LEBEN;
    Raumschiff1.Punkte = 0;
    verloren = false;
    for (int i = 0; i < MAX_ASTEROIDEN; i++)
    {
        Asteroid1[i].AsteroidAktiv = false;
    }
    for (int i = 0; i < MAX_SCHUESSE; i++)
    {
        Schuss[i].aktiv = false;
    }

}


JoystickWerte JoysticksEinlesen()
{
    JoystickWerte Werte;

    Werte.x = analogRead(14);
    Werte.y = analogRead(12);

    return Werte;
}


// Drei Punkte relativ zur Schiffsmitte drehen.
// Anschließend die fertigen Punkte zum Zeichnen übergeben.
void DreieckTeilDrehen(
    float linksX, float linksY,
    float obenX, float obenY,
    float rechtsX, float rechtsY)
{
    float c = cos(Raumschiff1.Winkel);
    float s = sin(Raumschiff1.Winkel);

    float linksNeuX = linksX * c - linksY * s;
    float linksNeuY = linksX * s + linksY * c;

    float obenNeuX = obenX * c - obenY * s;
    float obenNeuY = obenX * s + obenY * c;

    float rechtsNeuX = rechtsX * c - rechtsY * s;
    float rechtsNeuY = rechtsX * s + rechtsY * c;

    zeichneDreieck(
        Raumschiff1.x + linksNeuX,
        Raumschiff1.y + linksNeuY,

        Raumschiff1.x + obenNeuX,
        Raumschiff1.y + obenNeuY,

        Raumschiff1.x + rechtsNeuX,
        Raumschiff1.y + rechtsNeuY
    );
}


void RechteckTeilDrehen(
    float mitteX,
    float mitteY,
    float Breite,
    float Hoehe)
{
    float LinksObenX = mitteX - Breite / 2.0f;
    float LinksObenY = mitteY + Hoehe / 2.0f;

    float LinksUntenX = mitteX - Breite / 2.0f;
    float LinksUntenY = mitteY - Hoehe / 2.0f;

    float RechtsObenX = mitteX + Breite / 2.0f;
    float RechtsObenY = mitteY + Hoehe / 2.0f;

    float RechtsUntenX = mitteX + Breite / 2.0f;
    float RechtsUntenY = mitteY - Hoehe / 2.0f;

    float c = cos(Raumschiff1.Winkel);
    float s = sin(Raumschiff1.Winkel);

    float LinksObenXNeu = LinksObenX * c - LinksObenY * s;
    float LinksObenYNeu = LinksObenX * s + LinksObenY * c;

    float LinksUntenXNeu = LinksUntenX * c - LinksUntenY * s;
    float LinksUntenYNeu = LinksUntenX * s + LinksUntenY * c;

    float RechtsObenXNeu = RechtsObenX * c - RechtsObenY * s;
    float RechtsObenYNeu = RechtsObenX * s + RechtsObenY * c;

    float RechtsUntenXNeu = RechtsUntenX * c - RechtsUntenY * s;
    float RechtsUntenYNeu = RechtsUntenX * s + RechtsUntenY * c;

    RechteckZeichnen(
        Raumschiff1.x + LinksUntenXNeu,
        Raumschiff1.y + LinksUntenYNeu,

        Raumschiff1.x + LinksObenXNeu,
        Raumschiff1.y + LinksObenYNeu,

        Raumschiff1.x + RechtsUntenXNeu,
        Raumschiff1.y + RechtsUntenYNeu,

        Raumschiff1.x + RechtsObenXNeu,
        Raumschiff1.y + RechtsObenYNeu
    );
}


void BasisDrehen()
{
    RechteckTeilDrehen(
        0,
        0,
        Raumschiff1.Breite,
        Raumschiff1.Hoehe
    );
}


void DachDrehen()
{
    float halbeBreite = Raumschiff1.Breite / 2.0f;
    float oberkante = Raumschiff1.Hoehe / 2.0f;
    float dachHoehe = 15;

    DreieckTeilDrehen(
        -halbeBreite, oberkante,
        0, oberkante + dachHoehe,
        halbeBreite, oberkante
    );
}


void FluegelDrehen()
{
    float halbeBreite = Raumschiff1.Breite / 2.0f;
    float unterkante = -Raumschiff1.Hoehe / 2.0f;

    float fluegelBreite = 12;
    float fluegelAnsatzY = 2;

    // Linker Flügel
    DreieckTeilDrehen(
        -halbeBreite, fluegelAnsatzY,
        -halbeBreite - fluegelBreite, unterkante - 4,
        -halbeBreite, unterkante
    );

    // Rechter Flügel
    DreieckTeilDrehen(
        halbeBreite, fluegelAnsatzY,
        halbeBreite + fluegelBreite, unterkante - 4,
        halbeBreite, unterkante
    );
}


void FensterDrehen()
{
    // Fenster liegt 5 Einheiten oberhalb der Schiffsmitte.
    RechteckTeilDrehen(
        0,
        5,
        10,
        10
    );
}


void AntriebDrehen()
{
    float unterkante = -Raumschiff1.Hoehe / 2.0f;

    float antriebBreite = 10;
    float antriebHoehe = 6;

    // Die obere Kante des Antriebs liegt direkt
    // an der unteren Kante der Basis.
    RechteckTeilDrehen(
        0,
        unterkante - antriebHoehe / 2.0f,
        antriebBreite,
        antriebHoehe
    );
}

void SchiffZeichnen()
{
    //Spitze      (0/12)
    //Rechtsunten (8/-8)
    //Kerberechts (3/-8)
    //Kerbe links (-3/-8)
    //Linksunten  (-8/-8)
    //Kerbe       (0/-4)
    float c = cos(Raumschiff1.Winkel);
    float s = sin(Raumschiff1.Winkel);
    float spitzeX = Raumschiff1.x + 0 * c - 12 * s;
    float spitzeY = Raumschiff1.y + 0 * s + 12 * c;

    float rechtsUntenX = Raumschiff1.x + 8 * c - (-8) * s;
    float rechtsUntenY = Raumschiff1.y + 8 * s + (-8) * c;

    float kerbeRechtsX = Raumschiff1.x + 3 * c - (-8) * s;
    float kerbeRechtsY = Raumschiff1.y + 3 * s + (-8) * c;

    float kerbeLinksX = Raumschiff1.x + (-3) * c - (-8) * s;
    float kerbeLinksY = Raumschiff1.y + (-3) * s + (-8) * c;

    float linksUntenX = Raumschiff1.x + (-8) * c - (-8) * s;
    float linksUntenY = Raumschiff1.y + (-8) * s + (-8) * c;

    float kerbeX = Raumschiff1.x + 0 * c - (-4) * s;
    float kerbeY = Raumschiff1.y + 0 * s + (-4) * c;

    zeichneLinie(spitzeX, spitzeY, rechtsUntenX, rechtsUntenY);
    zeichneLinie(rechtsUntenX, rechtsUntenY, kerbeRechtsX, kerbeRechtsY);
    zeichneLinie(kerbeRechtsX, kerbeRechtsY, kerbeX, kerbeY);
    zeichneLinie(kerbeX, kerbeY, kerbeLinksX, kerbeLinksY);
    zeichneLinie(kerbeLinksX, kerbeLinksY, linksUntenX, linksUntenY);
    zeichneLinie(linksUntenX, linksUntenY, spitzeX, spitzeY);
}

void RaumschiffDrehen()
{
    int richtungX = Werte.x - 1850;
    int richtungY = 1850 - Werte.y;

    if (abs(richtungX) > 200 || abs(richtungY) > 200)
    {
        Raumschiff1.Winkel =
            atan2f(richtungX, richtungY) + PI / 2.0f;
    }
    SchiffZeichnen();
    //BasisDrehen();
    //DachDrehen();
    //FluegelDrehen();
    //FensterDrehen();
    //AntriebDrehen();
}
void SchubDrehen()
{
    // Unterkante deines Antriebs
    float antriebUnten = -8;

    // Flamme relativ zur Schiffsmitte
    float linksX = -3;
    float linksY = antriebUnten;

    float spitzeX = 0;
    float spitzeY = antriebUnten - 16;

    float rechtsX = 3;
    float rechtsY = antriebUnten;

    float c = cos(Raumschiff1.Winkel);
    float s = sin(Raumschiff1.Winkel);

    zeichneSchub(
        Raumschiff1.x + linksX * c - linksY * s,
        Raumschiff1.y + linksX * s + linksY * c,

        Raumschiff1.x + spitzeX * c - spitzeY * s,
        Raumschiff1.y + spitzeX * s + spitzeY * c,

        Raumschiff1.x + rechtsX * c - rechtsY * s,
        Raumschiff1.y + rechtsX * s + rechtsY * c
    );
}
uint8_t StellenZaehlen(int zahl)
{
    int anzahl = 0;
    int rest = zahl;     
    if(zahl == 0)    
    {
        anzahl = 1;
    }
    while (rest > 0)
    {
        rest = rest / 10;           
        anzahl++;
    }
    return anzahl;
}
void Zahlenumrandung(int x, int y, int skala)
{
    int RandAbstand = skala;
    int Abstand = StellenZaehlen(Raumschiff1.Punkte);
    int StartX = x;
    int StartY = y;
    int breite = Abstand * 4 * skala - skala - 1;
    int hoehe = 4 * skala;

    zeichneRechteck(StartX - RandAbstand, StartY - RandAbstand, breite + RandAbstand * 2, hoehe + RandAbstand * 2);
    //je nachdem wie viele stellen die Zahl hat, soll die Breite des Rechtecks größer werden. 
}
void GameOver()
{
    Raumschiff1.x = 128;
    Raumschiff1.y = 128;
    Raumschiff1.Winkel = 0;

    unsigned long jetzt = millis();
    static unsigned long letzteAnimation = 0;
    static bool textSichtbar = false;
    if (jetzt - letzteAnimation >= 500)
    {
        letzteAnimation = jetzt;
        textSichtbar = !textSichtbar;
    }

    zeichneRechteck(0, 0, 255, 255);
    arcadeTextMitte(150, "GAME OVER", 6);
    arcadeText(40, 215, "SCORE", 4);
    arcadeZahl(180, 215, Raumschiff1.Punkte, 4);
    zeichneLinie(0, 195, 255, 195);
    Zahlenumrandung(180, 215, 4);
    if (textSichtbar)
    {
        arcadeTextMitte(90, "SCHIESSEN ZUM NEUSTART", 2);
    } 

    if (digitalRead(Tasterpin) == LOW)
    {
        auswahlbereit = true;
    }
    if (digitalRead(Tasterpin) == HIGH && auswahlbereit)
    {
        auswahlbereit = false;
        ResetAsteroids();
    }
}
void RaumschiffBewegen()
{
    int JoystickrichtungX = Werte.x - 1850;
    int JoystickrichtungY = 1850 - Werte.y;
    float richtungX = -sin(Raumschiff1.Winkel);
    float richtungY = cos(Raumschiff1.Winkel);
    bool schub = (abs(JoystickrichtungX) > 1800 || abs(JoystickrichtungY) > 1800);
    if(schub)
    {
        SchubDrehen();
    }
    unsigned long jetzt = millis();
    static unsigned long letzteBewegung = 0;
    if (jetzt - letzteBewegung >= 20)
    {
        letzteBewegung = jetzt;

        if (schub)
        {
            Raumschiff1.GeschwindigkeitX += richtungX * 0.1f;
            Raumschiff1.GeschwindigkeitY += richtungY * 0.1f;
            float maxGeschwindigkeit = 3.0f;
            float speed = sqrt(Raumschiff1.GeschwindigkeitX * Raumschiff1.GeschwindigkeitX +
                               Raumschiff1.GeschwindigkeitY * Raumschiff1.GeschwindigkeitY);
            if(speed > maxGeschwindigkeit)
            {
                Raumschiff1.GeschwindigkeitX = (Raumschiff1.GeschwindigkeitX / speed) * maxGeschwindigkeit;
                Raumschiff1.GeschwindigkeitY = (Raumschiff1.GeschwindigkeitY / speed) * maxGeschwindigkeit;
            }
        } 
        
        else 
        {
            Raumschiff1.GeschwindigkeitX *= 0.993f;
            Raumschiff1.GeschwindigkeitY *= 0.993f;
        }
        Raumschiff1.x += Raumschiff1.GeschwindigkeitX;
        Raumschiff1.y += Raumschiff1.GeschwindigkeitY;
        if (Raumschiff1.x > 255)
        {
            Raumschiff1.x = 0;
        }
        if (Raumschiff1.x < 0)
        {
            Raumschiff1.x = 255;
        }
        if (Raumschiff1.y > FELD_OBEN)
        {
            Raumschiff1.y = 0;
        }
        if (Raumschiff1.y < 0)
        {
            Raumschiff1.y = FELD_OBEN;
        }
    }
}

bool RaumschiffKollisionUeberpruefen(const Asteroid &Asteroid1,
                      const Raumschiff &Raumschiff1)
{
    float AbstandX = Raumschiff1.x - Asteroid1.x;
    float AbstandY = Raumschiff1.y - Asteroid1.y;

    float radiusSchiff = 8.0f;
    float radiusAsteroid = Asteroid1.groesse;


    return AbstandX * AbstandX + AbstandY * AbstandY 
           <= (radiusSchiff + radiusAsteroid) 
            * (radiusSchiff + radiusAsteroid);
}

void AsteroidsSpawnen(Asteroid &Asteroid1)
{
    float startXLinks = 0;
    float startYLinks = random(0,FELD_OBEN + 1);
    float startXOben = random(0,256);
    float startYOben = FELD_OBEN;
    float startXRechts = 255;
    float startYRechts = random(0,FELD_OBEN + 1);
    float startXUnten = random(0,256);
    float startYUnten = 0;
    Asteroid1.groesse = GROSS;  
    int seite = random(0,4);
    if(seite == 0)
    {
            Asteroid1.x = startXLinks;
            Asteroid1.y = startYLinks;
            Asteroid1.AsteroidAktiv = true;
    }
    else if(seite == 1)
    {
        Asteroid1.x = startXOben;
        Asteroid1.y = startYOben;
        Asteroid1.AsteroidAktiv = true;
    }
    else if(seite == 2)
    {
        Asteroid1.x = startXRechts;
        Asteroid1.y = startYRechts;
        Asteroid1.AsteroidAktiv = true;
    }
    else if(seite == 3)
    {
        Asteroid1.x = startXUnten;
        Asteroid1.y = startYUnten;
        Asteroid1.AsteroidAktiv = true;
    }
    float richtungX = Raumschiff1.x - Asteroid1.x;
    float richtungY = Raumschiff1.y - Asteroid1.y;
    float laenge = sqrt(richtungX * richtungX + richtungY * richtungY);
    float Geschwindigkeit = random(30, 91) / 100.0f;
    Asteroid1.geschwindigkeitX = (richtungX / laenge) * Geschwindigkeit;
    Asteroid1.geschwindigkeitY = (richtungY / laenge) * Geschwindigkeit;
}  
 
void AsteroidsAktualisieren()
{

    for(int i = 0; i < 4; i++)
    {
        if(!Asteroid1[i].AsteroidAktiv)
        {
            AsteroidsSpawnen(Asteroid1[i]);
            break;
        }
    }
}

void RaumschiffKollisionErkannt()
{
    for(int i = 0; i < MAX_ASTEROIDEN; i++)
    {
        if(Asteroid1[i].AsteroidAktiv)
        {
            if(RaumschiffKollisionUeberpruefen(Asteroid1[i], Raumschiff1))
            {
                Raumschiff1.leben--;
                Asteroid1[i].AsteroidAktiv = false;
                if(Raumschiff1.leben <= 0)
                {
                    verloren = true;
                }
                break;
            }
        }
    }
}

void AsteroidsBewegen()
{
    static unsigned long letzteBewegung = 0;
    unsigned long jetzt = millis();

    
        if(jetzt - letzteBewegung >= 20)
        {
            letzteBewegung = jetzt;
            for(int i = 0; i < MAX_ASTEROIDEN; i++)
        {   
            if(Asteroid1[i].AsteroidAktiv)
            {
                Asteroid1[i].x += Asteroid1[i].geschwindigkeitX;
                Asteroid1[i].y += Asteroid1[i].geschwindigkeitY;
            
                if (Asteroid1[i].x > 255)
                {
                    Asteroid1[i].x = 0;
                }
                if (Asteroid1[i].x < 0)
                {
                    Asteroid1[i].x = 255;
                }
                if (Asteroid1[i].y > FELD_OBEN)
                {
                    Asteroid1[i].y = 0;
                }
                if (Asteroid1[i].y < 0)
                {
                    Asteroid1[i].y = FELD_OBEN;
                }
            }
        }
    }
}
void zeichneAsteroid()
{
    for(int i = 0; i < MAX_ASTEROIDEN; i++)
    {
        if(Asteroid1[i].AsteroidAktiv)
        {
            zeichneAsteroidZeichnen(Asteroid1[i].x, Asteroid1[i].y, Asteroid1[i].groesse);
        }
    }
}

void zeichneAsteroids()
{
    zeichneRechteck(0, 0, 255, 255);
    zeichneAsteroid();
    RaumschiffDrehen();
    zeichneLinie(0, FELD_OBEN, 255, FELD_OBEN);
    zeichneLeben(0.6, Raumschiff1.leben);
    arcadeZahl(10, 235, Raumschiff1.Punkte, 3);
}

void SchussSpawnen()
{
    float richtungX = -sin(Raumschiff1.Winkel);
    float richtungY = cos(Raumschiff1.Winkel);
    float abstandSpitze = 12;
    for(int i = 0; i < MAX_SCHUESSE; i++)
    {
        if(!Schuss[i].aktiv)
        {
            Schuss[i].x = Raumschiff1.x + richtungX * abstandSpitze;
            Schuss[i].y = Raumschiff1.y + richtungY * abstandSpitze;
            Schuss[i].geschwindigkeitX = richtungX * 3.0;
            Schuss[i].geschwindigkeitY = richtungY * 3.0;
            Schuss[i].aktiv = true;
            SchussSound();
            break;
        }
    }
    

}
void SchussBewegen()
{
    unsigned long jetzt = millis();
    static unsigned long letzteBewegung = 0;
    if(jetzt - letzteBewegung >= 20)
    {
        letzteBewegung = jetzt;
        for(int i = 0; i < MAX_SCHUESSE; i++)
        {
            if(Schuss[i].aktiv)
            {
                Schuss[i].x += Schuss[i].geschwindigkeitX;
                Schuss[i].y += Schuss[i].geschwindigkeitY;
                if(Schuss[i].x > 255)
                {
                    Schuss[i].aktiv = false;
                }
                if(Schuss[i].x < 0)
                {
                    Schuss[i].aktiv = false;
                }
                if(Schuss[i].y > FELD_OBEN)
                {
                    Schuss[i].aktiv = false;
                }
                if(Schuss[i].y < 0)
                {
                    Schuss[i].aktiv = false;
                }
            }
        }
    }  
}
void SchussZeichnen()
{
    for(int i = 0; i < MAX_SCHUESSE; i++)
    {
        if(Schuss[i].aktiv)
        {
            zeichneKreis(Schuss[i].x, Schuss[i].y, 2);
        }
    }    
}
void SchussAusloesen()
{
    if(digitalRead(Tasterpin) == HIGH && auswahlbereit)
    {
        SchussSpawnen();
        auswahlbereit = false;
    }
    if(digitalRead(Tasterpin) == LOW)
    {
        auswahlbereit = true;
    }
}

bool SchussKollisionPruefen(const Asteroid &Asteroid1,
                           const Schuesse &schuss)
{
    float AbstandX = schuss.x - Asteroid1.x;
    float AbstandY = schuss.y - Asteroid1.y;

    float RadiusSchuss = 2.0f;
    float RadiusAsteroid = Asteroid1.groesse;

    return AbstandX * AbstandX + AbstandY * AbstandY
           <= (RadiusAsteroid + RadiusSchuss)
            * (RadiusAsteroid + RadiusSchuss);
}

void KleinereAsteroidenSpawnen(Asteroid &getroffener)
{
    int kleinereGroesse = MITTEL;
    getroffener.geschwindigkeitX = random(-5,6) / 10.0;
    getroffener.geschwindigkeitY = random(-5,6) / 10.0;
    if(getroffener.groesse == GROSS)
    {
        getroffener.groesse = MITTEL;
        kleinereGroesse = MITTEL;
    }
    else if(getroffener.groesse == MITTEL)
    {
        getroffener.groesse = KLEIN;
        kleinereGroesse = KLEIN;
    }
    else if(getroffener.groesse == KLEIN)
    { 
        return;
    }
    
    float startX = getroffener.x;
    float startY = getroffener.y;
    
    for(int i = 0; i < MAX_ASTEROIDEN; i++)
    {
        if(!Asteroid1[i].AsteroidAktiv)
        {
            Asteroid1[i].x = startX;
            Asteroid1[i].y = startY;
            Asteroid1[i].groesse = kleinereGroesse;
            Asteroid1[i].geschwindigkeitX = random(-5,6) / 10.0;
            Asteroid1[i].geschwindigkeitY = random(-5,6) / 10.0;
            Asteroid1[i].AsteroidAktiv = true;
            break;
        }
    }
}
void PunkteBerechnen(Asteroid &getroffener)
{
    if(getroffener.groesse == GROSS)
    {
        Raumschiff1.Punkte += PunkteGROSS;
    }
    else if(getroffener.groesse == MITTEL)
    {
        Raumschiff1.Punkte += PunkteMITTEL;
    }
    else if(getroffener.groesse == KLEIN)
    {
        Raumschiff1.Punkte += PunkteKLEIN;
    }
}
void SchussKollisionErkannt()
{
    for (int i = 0; i < MAX_SCHUESSE; i++)
    {
        if(Schuss[i].aktiv)
        {

            for (int j = 0; j < MAX_ASTEROIDEN; j++)
            {
                if(Asteroid1[j].AsteroidAktiv)
                {
                    if (SchussKollisionPruefen(Asteroid1[j], Schuss[i]))
                    {
                        PunkteBerechnen(Asteroid1[j]);
                        Schuss[i].aktiv = false;
                        if (Asteroid1[j].groesse != KLEIN)
                        {
                            KleinereAsteroidenSpawnen(Asteroid1[j]);
                        }
                        else
                        {
                            Asteroid1[j].AsteroidAktiv = false;
                        }
                        break;
                    }
                }
            } 
        }
    }
}
void loopAsteroids()
{
    if (verloren)
    {
        GameOver();
        return;
    }

    Werte = JoysticksEinlesen();
    RaumschiffBewegen();
    AsteroidsBewegen();
    RaumschiffKollisionErkannt();
    SchussKollisionErkannt();
    zeichneAsteroids();
    SchussAusloesen();
    SchussBewegen();
    SchussZeichnen();
    AsteroidsAktualisieren();
}