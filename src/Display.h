#pragma once
#include <Arduino.h>

// Struktur für Koordinaten
struct Punkt {
    int x;
    int y;
};

// Initialisierung der Pins
void initDisplay();

// Hardware-Ausgabe
void zeigeKoordinate(const int pins[8], int wert);

// Bresenham-Zeichenfunktionen
void zeichneLinie(int x0, int y0, int x1, int y1);
void zeichneKreis(int xc, int yc, int r);
void zeichneRechteck(int startX, int startY, int breite, int hoehe);
void zeichneSchlaeger(Punkt ecke, int breite, int hoehe);
void Joysticks();
void positioniereStrahl(int x, int y);
void strahlSpringen(int x, int y);