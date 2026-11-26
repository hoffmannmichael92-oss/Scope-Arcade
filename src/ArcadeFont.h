#pragma once
#include <Arduino.h>

void zeichenZeichnen(int x, int y, const uint8_t muster[5], int skala);
void arcadeZiffer(int x, int y, int ziffer, int skala);
void arcadeBuchstaben(int x, int y, char buchstabe, int skala);
void arcadeText(int x, int y, const char* text, int skala);
void arcadeZahl(int x, int y, int zahl, int skala);
int arcadeTextBreite(const char* text, int skala);
void arcadeTextMitte(int y, const char* text, int skala);
void Zahlenumrandung(int x, int y, int skala, int Punkte);
uint8_t StellenZaehlen(int zahl);