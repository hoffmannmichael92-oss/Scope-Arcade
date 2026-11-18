#include "Radar.h"
#include "Display.h"
#include <Arduino.h>

#define LD2450_BAUD 256000
struct LD2450Target {
    int16_t x;
    int16_t y;
    int16_t speed;
};

LD2450Target ziele[3];

// Sichtfeld des Sensors in mm -> wird auf 0-255 (Displaygröße) umgerechnet
const int mmMinX = -1500;
const int mmMaxX = 1500;
const int mmMinY = 0;
const int mmMaxY = 3000;

void setupRadar() {
    Serial2.begin(LD2450_BAUD, SERIAL_8N1, 35, 2);
}
int16_t decodeLD2450(uint8_t low, uint8_t high) {
    uint16_t raw = low | (high << 8);
    if (raw & 0x8000) {
        return (int16_t)(raw & 0x7FFF);  // Bit gesetzt = positiv, restliche 15 Bit = Betrag
    } else {
        return -(int16_t)raw;             // Bit nicht gesetzt = negativ, raw selbst ist der Betrag
    }
}
unsigned long letztesRadarPaket = 0;
unsigned long radarPaketZaehler = 0;
bool radarDatenVorhanden = false;

void leseLD2450() {
    static uint8_t paket[30];
    static int anzahl = 0;

    // Pro Aufruf begrenzen, damit die Anzeige auch bei
    // dauerhaft gestörtem Datenverkehr weiterlaufen kann.
    int geleseneBytes = 0;

    while (Serial2.available() > 0 && geleseneBytes < 256) {
        int empfangen = Serial2.read();
        if (empfangen < 0) break;

        paket[anzahl++] = (uint8_t)empfangen;
        geleseneBytes++;

        if (anzahl < 30) continue;

        bool anfangPasst =
            paket[0] == 0xAA &&
            paket[1] == 0xFF &&
            paket[2] == 0x03 &&
            paket[3] == 0x00;

        bool endePasst =
            paket[28] == 0x55 &&
            paket[29] == 0xCC;

        if (anfangPasst && endePasst) {
            // Erst ein vollständig eingerahmtes Paket übernehmen.
            for (int i = 0; i < 3; i++) {
                int start = 4 + i * 8;

                ziele[i].x = decodeLD2450(
                    paket[start], paket[start + 1]
                );

                ziele[i].y = decodeLD2450(
                    paket[start + 2], paket[start + 3]
                );

                ziele[i].speed = decodeLD2450(
                    paket[start + 4], paket[start + 5]
                );
            }

            letztesRadarPaket = millis();
            radarDatenVorhanden = true;
            radarPaketZaehler++;

            anzahl = 0;
        } else {
            // Um ein Byte weiterschieben.
            // Dadurch kann auch ein Paketanfang innerhalb
            // der bereits gelesenen Bytes gefunden werden.
            for (int i = 0; i < 29; i++) {
                paket[i] = paket[i + 1];
            }

            anzahl = 29;
        }
    }

    // Nach einer Sekunde ohne gültiges Paket:
    // alte Ziele nicht weiter anzeigen.
    if (radarDatenVorhanden &&
        millis() - letztesRadarPaket >= 1000) {

        for (int i = 0; i < 3; i++) {
            ziele[i].x = 0;
            ziele[i].y = 0;
            ziele[i].speed = 0;
        }

        radarDatenVorhanden = false;
        anzahl = 0;
    }
}

const int kreisRadius = 8; // muss zum Radius in loopRadar() passen

int mapX(int16_t mmX) {
    mmX = -mmX; // NEU: X-Achse spiegeln
    long wert = (long)(mmX - mmMinX) * (255 - 2*kreisRadius) / (mmMaxX - mmMinX);
    wert += kreisRadius;
    if (wert < kreisRadius) wert = kreisRadius;
    if (wert > 255 - kreisRadius) wert = 255 - kreisRadius;
    return (int)wert;
}

int mapY(int16_t mmY) {
    long wert = (long)(mmY - mmMinY) * (255 - 2*kreisRadius) / (mmMaxY - mmMinY);
    wert += kreisRadius;
    if (wert < kreisRadius) wert = kreisRadius;
    if (wert > 255 - kreisRadius) wert = 255 - kreisRadius;
    return (int)wert;
}

void loopRadar() {
    leseLD2450();

    zeichneRechteck(0, 0, 255, 255);

    for (int i = 0; i < 3; i++) {
    int x = ziele[i].x;
    int y = ziele[i].y;

    // Kein Ziel vorhanden.
    if (x == 0 && y == 0) continue;

    // Nur Ziele innerhalb unseres dargestellten Ausschnitts zeichnen.
    // mapX() spiegelt die X-Achse, deshalb hier ebenfalls spiegeln.
    int gespiegeltesX = -x;

    if (gespiegeltesX < mmMinX || gespiegeltesX > mmMaxX ||
        y < mmMinY || y > mmMaxY) {
        continue;
    }

    zeichneKreis(mapX(x), mapY(y), kreisRadius);
}

    // Vorübergehende Diagnose: zweimal pro Sekunde.
    static unsigned long letzteDiagnose = 0;

    if (millis() - letzteDiagnose >= 500) {
        letzteDiagnose = millis();

        Serial.print("Pakete=");
        Serial.print(radarPaketZaehler);

        Serial.print(" Empfang=");
        Serial.print(radarDatenVorhanden ? "OK" : "FEHLT");

        for (int i = 0; i < 3; i++) {
            Serial.print(" | Z");
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(ziele[i].x);
            Serial.print(",");
            Serial.print(ziele[i].y);
        }

        Serial.println();
    }
}