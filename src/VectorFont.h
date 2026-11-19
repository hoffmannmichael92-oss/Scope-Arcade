#pragma once

//Ziffern
void zeichneNull(int x, int y, int h);
void zeichneEins(int x, int y, int h);
void zeichneZwei(int x, int y, int h);
void zeichneDrei(int x, int y, int h);
void zeichneVier(int x, int y, int h);
void zeichneFuenf(int x, int y, int h);
void zeichneSechs(int x, int y, int h);
void zeichneSieben(int x, int y, int h);
void zeichneAcht(int x, int y, int h);
void zeichneNeun(int x, int y, int h);

void zeichneZehn(int x, int y, int h);
void zeichneZiffer(int x, int y, int h, int ziffer);
void ZerlegeZiffer(int x, int y, int hoehe, int punkte);



//Buchstaben
void zeichneBuchstabeA(float x, float y, float b, float h);
void zeichneBuchstabeC(float x, float y, float b, float h);
void zeichneBuchstabeD(float x, float y, float b, float h);
void zeichneBuchstabeE(float x, float y, float b, float h);
void zeichneBuchstabeF(float x, float y, float b, float h);
void zeichneBuchstabeG(float x, float y, float b, float h);
void zeichneBuchstabeH(float x, float y, float b, float h);
void zeichneBuchstabeI(float x, float y, float b, float h);
void zeichneBuchstabeK(int x, int y, int b, int h);
void zeichneBuchstabeL(float x, float y, float b, float h);
void zeichneBuchstabeM(float x, float y, float b, float h);
void zeichneBuchstabeN(float x, float y, float b, float h);
void zeichneBuchstabeO(float x, float y, float b, float h);
void zeichneBuchstabeP(float x, float y, float b, float h);
void zeichneBuchstabeS(float x, float y, float b, float h);
void zeichneBuchstabeT(float x, float y, float b, float h);
void zeichneBuchstabeR(float x, float y, float b, float h);
void zeichneBuchstabeU(float x, float y, float b, float h);
void zeichneBuchstabeV(int x, int y, int b, int h);
void zeichneBuchstabeW(int x, int y, int b, int h);
void zeichneBuchstabeY(float x, float y, float b, float h);

void zeichneUstrich(float x, float y, float h);



//Menü
void menueZeichnen();
void zeichneAuswahlPfeil(float x, float y, float groesse);
void ZeichneVertikalerStrich(float x, float y, float breite);

void ZeichnePingPong(float y, float b, float h, float abstand);
void zeichneRadar(float y, float b, float h, float abstand);
void ZeichneRunner(float y, float b, float h, float abstand);
void ZeichneFlappy(float y, float b, float h, float abstand);
void ZeichneModusPVP(int x, int y, int breite, int hoehe);
void ZeichneModusKI(int x, int y, int breite, int hoehe);

void ZeichneModusLeicht(int x, int y, int breite, int hoehe);
void ZeichneModusMittel(int x, int y, int breite, int hoehe);
void ZeichneModusSchwer(int x, int y, int breite, int hoehe);

void ZeichneMario(float x, float y, float h, float abstand);
void ZeichneAsteroids(float x, float y, float h, float abstand);

//Pong Grafik
void ZeichneMittelstrich(float x, float y, float hoehe);
void ZeichneGewinner(int x, int y, int breite, int hoehe, int spieler);



//Runner Grafik
void zeichneDino(int x, int y, bool laufBild, bool DinoGeduckt);
void zeichneFledermaus(int x, int y, bool laufbild);
void zeichneKaktus(int x, int y);
void ZeichneGrashalme(int x, float y, int Breite);
void ZeichneGameOver(int x, int y, int breite, int hoehe);

//Flappy Grafik
void zeichneVogel(int x, int y, bool fluegelOben);
void zeichneRoehren(int x, int y, int breite, int hoehe);
void zeichneWolke(int x, int y);


//Asteroids Grafik
void zeichneDreieck(
    float linksX, float linksY,
    float obenX, float obenY,
    float rechtsX, float rechtsY);

void RechteckZeichnen(
    float linksUntenX, float linksUntenY,
    float linksObenX, float linksObenY,
    float rechtsUntenX, float rechtsUntenY,
    float rechtsObenX, float rechtsObenY);

void zeichneAsteroidZeichnen(int x, int y, int groesse);

void zeichneSchub(
    float linksX, float linksY,
    float spitzeX, float spitzeY,
    float rechtsX, float rechtsY);

void zeichneLeben(float g, int leben);