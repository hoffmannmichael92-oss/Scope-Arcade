#include "Display.h"
#include <math.h>
#include "soc/soc.h"
#include "soc/gpio_reg.h"

const int pinsX[8] = {1, 13, 3, 15, 16, 17, 18, 19};
const int pinsY[8] = {21, 22, 23, 25, 26, 27, 32, 33};

// Vorberechnete GPIO-Bitmuster für die Werte 0 bis 255
static uint32_t musterX[256];
static uint32_t musterY[256];
static uint32_t musterYOben[256];

// Masken: Welche GPIOs gehören zu unserer Anzeige?
static uint32_t maskeX = 0;
static uint32_t maskeY = 0;
static uint32_t maskeYOben = 0;

void initDisplay()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(pinsX[i], OUTPUT);
        pinMode(pinsY[i], OUTPUT);

        maskeX |= 1 << pinsX[i];

        if (pinsY[i] < 32)
        {
            maskeY |= 1 << pinsY[i];
        }
        else
        {
            maskeYOben |= 1 << (pinsY[i] - 32);
        }
    }

    // Für jeden möglichen Koordinatenwert die Muster berechnen
    for (int wert = 0; wert < 256; wert++)
    {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t yOben = 0;

        for (int bit = 0; bit < 8; bit++)
        {
            if ((wert >> bit) & 1)
            {
                x |= 1UL << pinsX[bit];

                if (pinsY[bit] < 32)
                {
                    y |= 1UL << pinsY[bit];
                }
                else
                {
                    yOben |= 1UL << (pinsY[bit] - 32);
                }
            }
        }

        musterX[wert] = x;
        musterY[wert] = y;
        musterYOben[wert] = yOben;
    }
}

 void zeigeKoordinate(const int pins[8], int wert)
{
    // Tabellenindex auf den gültigen Bereich begrenzen
    if (wert < 0) wert = 0;
    if (wert > 255) wert = 255;

    if (pins == pinsX)
    {
        uint32_t muster = musterX[wert];

        // Nur diejenigen X-Pins auf LOW setzen,
        // die im gewünschten Muster 0 sind
        REG_WRITE(GPIO_OUT_W1TC_REG, maskeX & ~muster);

        // Gewünschte X-Pins auf HIGH setzen
        REG_WRITE(GPIO_OUT_W1TS_REG, muster);
    }
    else if (pins == pinsY)
    {
        uint32_t muster = musterY[wert];
        uint32_t musterOben = musterYOben[wert];

        // Y-Pins unter GPIO 32
        REG_WRITE(GPIO_OUT_W1TC_REG, maskeY & ~muster);
        REG_WRITE(GPIO_OUT_W1TS_REG, muster);

        // Y-Pins GPIO 32 und 33
        REG_WRITE(GPIO_OUT1_W1TC_REG, maskeYOben & ~musterOben);
        REG_WRITE(GPIO_OUT1_W1TS_REG, musterOben);
    }
}

void zeichneLinie(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        zeigeKoordinate(pinsX, x0);
        zeigeKoordinate(pinsY, y0);

        delayMicroseconds(2); // Kurze Pause, um die Linie sichtbar zu machen

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}




void zeichneKreis(int xc, int yc, int radius)
{
    const int schritte = 128;

    int vorherX = xc + radius;
    int vorherY = yc;

    for (int i = 1; i <= schritte; i++)
    {
        float winkel = 2.0f * PI * i / schritte;

        int neuX = xc + (int)roundf(radius * cosf(winkel));
        int neuY = yc + (int)roundf(radius * sinf(winkel));

        zeichneLinie(vorherX, vorherY, neuX, neuY);

        vorherX = neuX;
        vorherY = neuY;
    }
}

void zeichneRechteck(int startX, int startY, int breite, int hoehe) {
    int links  = startX;
    int rechts = startX + breite;
    int unten  = startY;
    int oben   = startY + hoehe;

    zeichneLinie(links, unten, rechts, unten);
    zeichneLinie(rechts, unten, rechts, oben);
    zeichneLinie(rechts, oben, links,  oben);
    zeichneLinie(links, oben,  links, unten);
    
}

void zeichneSchlaeger(Punkt ecke, int breite, int hoehe) 
{
    zeichneRechteck(ecke.x, ecke.y, breite, hoehe);
}

void positioniereStrahl(int x, int y)
{
    zeigeKoordinate(pinsX, x);
    zeigeKoordinate(pinsY, y);

    delayMicroseconds(15);
}