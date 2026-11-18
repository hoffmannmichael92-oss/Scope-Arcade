#include <Arduino.h>
#include "FlappyBird.h"
#include "VectorFont.h"
#include "Display.h"

// Wie beim Runner: Position, Hitbox, Animation und Punkte im Spieler-Struct.
struct Vogel
{
    int x;
    float y;
    int breite;
    int hoehe;
    float geschwindigkeit;
    bool fluegelOben;
    unsigned long letzteAnimation;
    int aktuellePunkteSpieler1;
};

struct Rohr
{
    float x;
    int breite;
    int lueckeY;
    int lueckeHoehe;
    float geschwindigkeit;
    bool punktGezaehlt;
};

struct Wolke
{
    float x;
    float y;
    float geschwindigkeit;
};

static Vogel vogel = {50, 120.0f, 24, 18, 0.0f, true, 0, 0};
static Rohr rohr1 = {160, 16, 50, 70, -3.5f, false};
static Rohr rohr2 = {290, 16, 80, 70, -3.5f, false};
static Wolke wolke1 = {200.0f, 200.0f, -3.5f, };
static Wolke wolke2 = {320.0f, 200.0f, -3.5f};
static Wolke wolke3 = {440.0f, 200.0f, -3.5f};

static const int spielTasterPin = 2;
static const int rohrAbstand = 120;
// Entspricht zeichneRoehren() in deiner hochgeladenen VectorFont.cpp.
static const int rohrRandBreite = 4;
static const int rohrRandHoehe = 8;

// static verhindert Namenskonflikte mit den anderen Spielen.
static bool flappyInitialisiert = false;
static bool spielGestartet = false;
static bool verloren = false;
static unsigned long letzteBewegung = 0;
static unsigned long letzteErhoehung = 0;

static bool letzterTasterMesswert = false;
static bool tasterStabilGedrueckt = false;
static unsigned long letzteTasterAenderung = 0;

static void WolkeSpawnen(Wolke &wolke, float startX)
{
    int minimaleY = 180;
    int maximaleY = 230;
    wolke.x = startX;
    wolke.y = random(minimaleY, maximaleY);
}

// Hindernisse vorbereiten
static void RohrSpawnen(Rohr &rohr, float startX)
{
    rohr.x = startX;
    rohr.breite = 16;
    rohr.punktGezaehlt = false;

    rohr.lueckeHoehe = random(57, 90);

    int maximaleUnterkante = 200 - rohr.lueckeHoehe;
    rohr.lueckeY = random(30, maximaleUnterkante + 1);
    Serial.print("RohrGeschwindigkeit: ");
    Serial.println(rohr.geschwindigkeit);
}

// Spiel zuruecksetzen
void ResetFlappy()
{
    spielGestartet = false;
    verloren = false;
    vogel.aktuellePunkteSpieler1 = 0;

    RohrSpawnen(rohr1, 160);
    RohrSpawnen(rohr2, 290);
    WolkeSpawnen(wolke1, 200.0f);
    WolkeSpawnen(wolke2, 320.0f);
    WolkeSpawnen(wolke3, 440.0f);
    vogel.y = 120.0f;
    vogel.geschwindigkeit = 0.0f;
    vogel.fluegelOben = true;
    wolke1.geschwindigkeit = -2.0f;
    wolke2.geschwindigkeit = -2.0f;
    wolke3.geschwindigkeit = -2.0f;
    rohr1.geschwindigkeit = -2.0f;
    rohr2.geschwindigkeit = -2.0f;
    unsigned long jetzt = millis();

    vogel.letzteAnimation = jetzt;
    letzteBewegung = jetzt;
    letzteTasterAenderung = jetzt;

    // Ein bereits gehaltener Taster zählt nicht als neuer Druck.
    letzterTasterMesswert =
        (digitalRead(spielTasterPin) == HIGH);

    tasterStabilGedrueckt = letzterTasterMesswert;

    flappyInitialisiert = true;
}

// Spielfeld und Punkte zeichnen
static void FlappyZeichnen()
{
    zeichneRechteck(0, 0, 255, 255);

    zeichneRoehren(
        rohr1.x,
        rohr1.breite,
        rohr1.lueckeY,
        rohr1.lueckeHoehe
    );

    zeichneRoehren(
        rohr2.x,
        rohr2.breite,
        rohr2.lueckeY,
        rohr2.lueckeHoehe
    );
    zeichneWolke(
        wolke1.x,
        wolke1.y
    );
    zeichneWolke(
        wolke2.x,
        wolke2.y
    );
    zeichneWolke(
        wolke3.x,
        wolke3.y
    );

    zeichneVogel(
        vogel.x,
        vogel.y,
        vogel.fluegelOben
    );

    // Dieselbe Punkteanzeige wie beim Endless Runner (0 bis 99).
    ZerlegeZiffer(128, 220, 24, vogel.aktuellePunkteSpieler1);

    if (verloren)
    {
        ZeichneGameOver(40, 100, 176, 50);
    }

    
}

// Animation
static void AnimationenAktualisieren()
{
    if (!spielGestartet)
    {
        return;
    }
    if(tasterStabilGedrueckt)
    {
        vogel.fluegelOben = true;
    }
    else
    {
        vogel.fluegelOben = false;
    }
}

// Taster entprellen
static bool FlappyTasterKlick()
{
    bool gedrueckt = (digitalRead(spielTasterPin) == HIGH);
    unsigned long jetzt = millis();

    if (gedrueckt != letzterTasterMesswert)
    {
        letzterTasterMesswert = gedrueckt;
        letzteTasterAenderung = jetzt;
    }

    if (jetzt - letzteTasterAenderung >= 25 &&
        gedrueckt != tasterStabilGedrueckt)
    {
        tasterStabilGedrueckt = gedrueckt;

        if (tasterStabilGedrueckt)
        {
            return true;
        }
    }

    return false;
}

// Rechteckige Hitboxen
static bool VogelTrifftRechteck(
    float x,
    float y,
    float breite,
    float hoehe)
{
    return
        vogel.x < x + breite &&
        vogel.x + vogel.breite > x &&
        vogel.y < y + hoehe &&
        vogel.y + vogel.hoehe > y;
}

static bool VogelTrifftRohr(const Rohr &rohr)
{
    int lueckeOben = rohr.lueckeY + rohr.lueckeHoehe;

    bool untenKoerper = VogelTrifftRechteck(
        rohr.x,
        0,
        rohr.breite,
        rohr.lueckeY - rohrRandHoehe
    );

    bool untenRand = VogelTrifftRechteck(
        rohr.x - rohrRandBreite,
        rohr.lueckeY - rohrRandHoehe,
        rohr.breite + 2 * rohrRandBreite,
        rohrRandHoehe
    );

    bool obenRand = VogelTrifftRechteck(
        rohr.x - rohrRandBreite,
        lueckeOben,
        rohr.breite + 2 * rohrRandBreite,
        rohrRandHoehe
    );

    bool obenKoerper = VogelTrifftRechteck(
        rohr.x,
        lueckeOben + rohrRandHoehe,
        rohr.breite,
        255 - lueckeOben - rohrRandHoehe
    );

    return untenKoerper || untenRand || obenRand || obenKoerper;
}

// Kollisionen und Punkte wie beim Runner gemeinsam pruefen
static void KollisionPruefen()
{
    if (!spielGestartet)
    {
        return;
    }

    bool trifftBildschirmrand =
        vogel.y < 0 ||
        vogel.y + vogel.hoehe > 255;

    if (trifftBildschirmrand ||
        VogelTrifftRohr(rohr1) ||
        VogelTrifftRohr(rohr2))
    {
        verloren = true;
        spielGestartet = false;
        vogel.geschwindigkeit = 0.0f;

        // Vogel nach der Prüfung im sichtbaren Bereich halten.
        if (vogel.y < 0)
        {
            vogel.y = 0;
        }
        else if (vogel.y > 255 - vogel.hoehe)
        {
            vogel.y = 255 - vogel.hoehe;
        }
    }

    if (!spielGestartet)
    {
        return;
    }

    if (rohr1.x + rohr1.breite + rohrRandBreite < vogel.x &&
        !rohr1.punktGezaehlt)
    {
        vogel.aktuellePunkteSpieler1++;
        rohr1.punktGezaehlt = true;
    }

    if (rohr2.x + rohr2.breite + rohrRandBreite < vogel.x &&
        !rohr2.punktGezaehlt)
    {
        vogel.aktuellePunkteSpieler1++;
        rohr2.punktGezaehlt = true;
    }
}

// Eingabe und Bewegung
static void BewegungAktualisieren(bool tasterKlick)
{
    if (tasterKlick)
    {
        if (verloren)
        {
            ResetFlappy();
        }

        if (!spielGestartet)
        {
            spielGestartet = true;
            letzteBewegung = millis();
            vogel.letzteAnimation = letzteBewegung;
        }

        vogel.geschwindigkeit = 4.0f;
    }

    if (!spielGestartet)
    {
        return;
    }

    unsigned long jetzt = millis();

    if (jetzt - letzteBewegung < 20)
    {
        return;
    }
    if (jetzt - letzteErhoehung > 500)
    {
        rohr1.geschwindigkeit -= 0.04f;
        rohr2.geschwindigkeit -= 0.04f;
        wolke1.geschwindigkeit -= 0.04f;
        wolke2.geschwindigkeit -= 0.04f;
        wolke3.geschwindigkeit -= 0.04f;
        letzteErhoehung = jetzt;
    }
    
    if(rohr1.geschwindigkeit < -3.5f)
    {
        rohr1.geschwindigkeit = -3.5f;
        rohr2.geschwindigkeit = -3.5f;
        wolke1.geschwindigkeit = -3.5f;
        wolke2.geschwindigkeit = -3.5f;
        wolke3.geschwindigkeit = -3.5f;
    }

    letzteBewegung = jetzt;

    rohr1.x += rohr1.geschwindigkeit;
    rohr2.x += rohr2.geschwindigkeit;
    wolke1.x += wolke1.geschwindigkeit;
    wolke2.x += wolke2.geschwindigkeit;
    wolke3.x += wolke3.geschwindigkeit;
    // Verschwundenes Röhrenpaar hinter das andere setzen.
    if (rohr1.x + rohr1.breite + rohrRandBreite < 0)
    {
        RohrSpawnen(rohr1, rohr2.x + rohrAbstand);
    }

    if (rohr2.x + rohr2.breite + rohrRandBreite < 0)
    {
        RohrSpawnen(rohr2, rohr1.x + rohrAbstand);
    }
    if(wolke1.x + 40 < 0)
    {
        WolkeSpawnen(wolke1, wolke3.x + rohrAbstand);
    }
    if(wolke2.x + 40 < 0)
    {
        WolkeSpawnen(wolke2, wolke1.x + rohrAbstand);   
    }
    if(wolke3.x + 40 < 0)
    {
        WolkeSpawnen(wolke3, wolke2.x + rohrAbstand);
    }
    // Flugbewegung und Schwerkraft
    vogel.y += vogel.geschwindigkeit;
    vogel.geschwindigkeit -= 0.3f;
}

// Hauptablauf wie loopEndlessRunner()
void loopFlappy()
{
    if (!flappyInitialisiert)
    {
        ResetFlappy();
    }

    bool tasterKlick = FlappyTasterKlick();
    BewegungAktualisieren(tasterKlick);

    if (spielGestartet)
    {
        KollisionPruefen();
    }

    AnimationenAktualisieren();
    FlappyZeichnen();
    
}
