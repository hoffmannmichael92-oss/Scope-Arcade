#include "ArcadeFont.h"
#include "Display.h"

// Ziffern 0-9, je 5 Zeilen von oben nach unten
static const uint8_t ZIFFERN[10][5] = {
    {7, 5, 5, 5, 7},   //0
    {2, 6, 2, 2, 7},   //1
    {7, 1, 7, 4, 7},   //2
    {7, 1, 7, 1, 7},   //3
    {5, 5, 7, 1, 1},   //4
    {7, 4, 7, 1, 7},   //5
    {7, 4, 7, 5, 7},   //6
    {7, 1, 1, 1, 1},   //7
    {7, 5, 7, 5, 7},   //8
    {7, 5, 7, 1, 7},   //9
};
static const uint8_t BUCHSTABEN[26][5] = {
    {2, 5, 7, 5, 5},   //  0 = A
    {6, 5, 6, 5, 6},   //  1 = B
    {3, 4, 4, 4, 3},   //  2 = C
    {6, 5, 5, 5, 6},   //  3 = D
    {7, 4, 6, 4, 7},   //  4 = E
    {7, 4, 6, 4, 4},   //  5 = F
    {3, 4, 5, 5, 3},   //  6 = G
    {5, 5, 7, 5, 5},   //  7 = H
    {7, 2, 2, 2, 7},   //  8 = I
    {1, 1, 1, 5, 2},   //  9 = J
    {5, 5, 6, 5, 5},   // 10 = K
    {4, 4, 4, 4, 7},   // 11 = L
    {5, 7, 7, 5, 5},   // 12 = M
    {6, 5, 5, 5, 5},   // 13 = N
    {2, 5, 5, 5, 2},   // 14 = O
    {6, 5, 6, 4, 4},   // 15 = P
    {2, 5, 5, 7, 3},   // 16 = Q
    {6, 5, 6, 5, 5},   // 17 = R
    {3, 4, 2, 1, 6},   // 18 = S
    {7, 2, 2, 2, 2},   // 19 = T
    {5, 5, 5, 5, 7},   // 20 = U
    {5, 5, 5, 5, 2},   // 21 = V
    {5, 5, 7, 7, 5},   // 22 = W
    {5, 5, 2, 5, 5},   // 23 = X
    {5, 5, 2, 2, 2},   // 24 = Y
    {7, 1, 2, 4, 7},   // 25 = Z
};

void zeichenZeichnenVerbunden(int x, int y, const uint8_t muster[5], int skala)
{
    for (int zeile = 0; zeile < 5; zeile++)
    {
        uint8_t zeilenMuster = muster[zeile];
        for (int spalte = 0; spalte < 3; spalte++)
        {
            if (zeilenMuster & (1 << (2 - spalte)))
            {
                int pixelX = x + spalte * skala;
                int pixelY = y + (4 - zeile) * skala;

    bool rechtsAn = false;
    if (spalte < 2)                                   
    {
        rechtsAn = muster[zeile] & (1 << (2 - (spalte + 1)));   
    }

    bool untenAn = false;
    if (zeile < 4)                                    
    {
        untenAn = muster[zeile + 1] & (1 << (2 - spalte));     
    }

    if (rechtsAn)
    {
        zeichneLinie(pixelX, pixelY, pixelX + skala, pixelY); 
    }
    if (untenAn)
    {
        zeichneLinie(pixelX, pixelY, pixelX, pixelY - skala);
    }
            }
        }
    }
}

void zeichenZeichnen(int x, int y, const uint8_t muster[5], int skala)
{
    positioniereStrahl(x, y + 4 * skala);
    for (int zeile = 0; zeile < 5; zeile++)
    {
        for (int spalte = 0; spalte < 3; spalte++)
        {
            // Ist dieses Pixel an?
            if (muster[zeile] & (1 << (2 - spalte)))
            {
                // Wo liegt es?
                int pixelX = x + spalte * skala;
                int pixelY = y + (4 - zeile) * skala;

                strahlSpringen(pixelX, pixelY);
                zeichneLinie(pixelX, pixelY, pixelX + skala - 1, pixelY);
                zeichneLinie(pixelX, pixelY, pixelX + skala - 1, pixelY);
            }
        }
    }
}
void arcadeZiffer(int x, int y, int ziffer, int skala)
{
    if (ziffer < 0 || ziffer > 9)
    {
        return; // Ungültige Ziffer
    }
    zeichenZeichnen(x, y, ZIFFERN[ziffer], skala);
}

void arcadeBuchstaben(int x, int y, char buchstabe, int skala)
{
    if (buchstabe < 'A' || buchstabe > 'Z')
    {
        return; // Ungültiger Buchstabe
    }
    zeichenZeichnen(x, y, BUCHSTABEN[buchstabe - 'A'], skala);
}
void arcadeText(int x, int y, const char* text, int skala)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        char zeichen = text[i];

        if (zeichen >= 'A' && zeichen <= 'Z')
        {
            arcadeBuchstaben(x, y, zeichen, skala);
        }
        else if (zeichen >= '0' && zeichen <= '9')
        {
            arcadeZiffer(x, y, zeichen - '0', skala);
        }

        x = x + 4 * skala;
    }
}

void arcadeZahl(int x, int y, int zahl, int skala)
{
    int abstand = 4 * skala;   

  
    if (zahl == 0)
    {
        arcadeZiffer(x, y, 0, skala);
        return;
    }

    int anzahl = 0;
    int rest = zahl;          
    while (rest > 0)
    {
        rest = rest / 10;           
        anzahl++;
    }

    int position = x + (anzahl - 1) * abstand;

    while (zahl > 0)
    {
        int ziffer = zahl % 10;   
        arcadeZiffer(position, y, ziffer, skala);
        zahl = zahl / 10;
        position = position - abstand;
    }
}
// Wie breit ein Text auf dem Bildschirm ist
int arcadeTextBreite(const char* text, int skala)
{
    int anzahl = 0;
    while (text[anzahl] != '\0')
    {
        anzahl++;
    }
    if (anzahl == 0)
    {
        return 0;
    }
    // jedes Zeichen 4*skala, aber nach dem letzten keine Lücke
    return anzahl * 4 * skala - skala - 1;
}

// Text waagrecht in die Bildschirmmitte setzen
void arcadeTextMitte(int y, const char* text, int skala)
{
    int x = (256 - arcadeTextBreite(text, skala)) / 2;
    arcadeText(x, y, text, skala);
}

void Zahlenumrandung(int x, int y, int skala, int Punkte)
{
    int RandAbstand = skala;
    int Abstand = StellenZaehlen(Punkte);
    int StartX = x;
    int StartY = y;
    int breite = Abstand * 4 * skala - skala - 1;
    int hoehe = 4 * skala;

    zeichneRechteck(StartX - RandAbstand, StartY - RandAbstand, breite + RandAbstand * 2, hoehe + RandAbstand * 2);
    //je nachdem wie viele stellen die Zahl hat, soll die Breite des Rechtecks größer werden. 
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