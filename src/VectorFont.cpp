#include "VectorFont.h"
#include "Display.h"

//Zahlen
void zeichneNull(int x, int y, int h) 
{
    int breite = h / 2;
    zeichneLinie(x, y, x, y + h);
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, y, x + breite, y);
    zeichneLinie(x + breite, y, x + breite, y + h);
}

void zeichneEins(int x, int y, int h) 
{
    int breite = h / 2;
    zeichneLinie(x + breite, y, x + breite, y + h);
    zeichneLinie(x, y + h - (h / 3), x + breite, y + h);
}

void zeichneZwei(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x + breite, mitteY, x + breite, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x, y, x, mitteY);
    zeichneLinie(x, y, x + breite, y);
}

void zeichneDrei(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x, y, x + breite, y);
    zeichneLinie(x + breite, y, x + breite, y + h);
}

void zeichneVier(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, mitteY, x, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x + breite, y, x + breite, y + h);
}

void zeichneFuenf(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, mitteY, x, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x + breite, y, x + breite, mitteY);
    zeichneLinie(x, y, x + breite, y);
}

void zeichneSechs(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y, x, y + h);
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x, y, x + breite, y);
    zeichneLinie(x + breite, y, x + breite, mitteY);
}

void zeichneSieben(int x, int y, int h) 
{
    int breite = h / 2;
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x + breite, y, x + breite, y + h);
}

void zeichneAcht(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y, x, y + h);
    zeichneLinie(x + breite, y, x + breite, y + h);
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x, y, x + breite, y);
}

void zeichneNeun(int x, int y, int h) 
{
    int breite = h / 2;
    int mitteY = y + h / 2;
    zeichneLinie(x, y + h, x + breite, y + h);
    zeichneLinie(x, mitteY, x + breite, mitteY);
    zeichneLinie(x, mitteY, x, y + h);
    zeichneLinie(x + breite, y, x + breite, y + h);
    zeichneLinie(x, y, x + breite, y);
}

void zeichneZehn(int x, int y, int h) 
{
    int breite = h / 2;
    int buchstabenAbstand = 4;
    zeichneEins(x, y, h);
    zeichneNull(x + breite + buchstabenAbstand, y, h);
}

void zeichneZiffer(int x, int y, int h, int ziffer) 
{
    switch (ziffer) 
    {
        case 0:  zeichneNull(x, y, h); break;
        case 1:  zeichneEins(x, y, h); break;
        case 2:  zeichneZwei(x, y, h); break;
        case 3:  zeichneDrei(x, y, h); break;
        case 4:  zeichneVier(x, y, h); break;
        case 5:  zeichneFuenf(x, y, h); break;
        case 6:  zeichneSechs(x, y, h); break;
        case 7:  zeichneSieben(x, y, h); break;
        case 8:  zeichneAcht(x, y, h); break;
        case 9:  zeichneNeun(x, y, h); break;
    }
}

void ZerlegeZiffer(int x, int y, int hoehe, int punkte)
{
    int hunderter = punkte / 100;
    int zehner = (punkte / 10) % 10;
    int einser = punkte % 10;

    int abstand = hoehe / 2 + 4;

    if (hunderter > 0)
    {
        zeichneZiffer(x - 2 * abstand, y, hoehe, hunderter);
    }

    // Bei vorhandenen Hundertern auch eine Zehner-Null zeichnen.
    if (punkte >= 10)
    {
        zeichneZiffer(x - abstand, y, hoehe, zehner);
    }

    zeichneZiffer(x, y, hoehe, einser);
}






//Buchstaben 
void zeichneBuchstabeA(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x + b / 2, y + h);             
    zeichneLinie(x + b / 2, y + h, x + b, y);         
    zeichneLinie(x + b * 0.25, y + h / 2, x + b * 0.75, y + h / 2); 
}

void zeichneBuchstabeC(float x, float y, float b, float h)
{
    zeichneLinie(x + b, y + h, x, y + h);
    zeichneLinie(x, y + h, x, y);
    zeichneLinie(x, y, x + b, y);
}

void zeichneBuchstabeD(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                         
    zeichneLinie(x, y + h, x + b * 0.6, y + h);            
    zeichneLinie(x + b * 0.6, y + h, x + b, y + h * 0.75); 
    zeichneLinie(x + b, y + h * 0.75, x + b, y + h * 0.25);
    zeichneLinie(x + b, y + h * 0.25, x + b * 0.6, y);     
    zeichneLinie(x + b * 0.6, y, x, y);                    
}

void zeichneBuchstabeE(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                 
    zeichneLinie(x, y + h, x + b, y + h);        
    zeichneLinie(x, y + h/2, x + b*0.8, y + h/2); 
    zeichneLinie(x, y, x + b, y);                 
}

void zeichneBuchstabeF(float x, float y, float b, float h)
{
    // Oben rechts beginnen, dann oben nach links und nach unten.
    zeichneLinie(x + b, y + h, x, y + h);
    zeichneLinie(x, y + h, x, y);

    // Auf der linken Linie zurück zur Mitte.
    zeichneLinie(x, y, x, y + h / 2);
    zeichneLinie(x, y + h / 2, x + b, y + h / 2);
}

void zeichneBuchstabeG(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                      
    zeichneLinie(x, y + h, x + b, y + h);              
    zeichneLinie(x + b, y, x + b, y + h / 2);       
    zeichneLinie(x + b, y + h / 2, x + b / 2, y + h / 2);
    zeichneLinie(x, y, x + b, y);                       
}

void zeichneBuchstabeH(float x, float y, float b, float h)
{
    zeichneLinie(x, y, x, y + h);
    zeichneLinie(x, y + h / 2, x + b, y + h / 2);
    zeichneLinie(x + b, y, x + b, y + h);
}

void zeichneBuchstabeI(float x, float y, float b, float h) 
{
    float mitteX = x + b / 2;
    zeichneLinie(x, y + h, x + b, y + h);     
    zeichneLinie(mitteX, y + h, mitteX, y);   
    zeichneLinie(x, y, x + b, y);             
}

void zeichneBuchstabeK(int x, int y, int b, int h)
{
    zeichneLinie(x, y, x, y + h);
    zeichneLinie(x + b, y + h, x, y + h / 2);
    zeichneLinie(x, y + h / 2, x + b, y);
}

void zeichneBuchstabeL(float x, float y, float b, float h)
{
    zeichneLinie(x, y + h, x, y);
    zeichneLinie(x, y, x + b, y);
}


void zeichneBuchstabeM(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                 
    zeichneLinie(x, y + h, x + b/2, y + h/2);     
    zeichneLinie(x + b/2, y + h/2, x + b, y + h); 
    zeichneLinie(x + b, y + h, x + b, y);         
}

void zeichneBuchstabeN(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);         
    zeichneLinie(x, y + h, x + b, y);     
    zeichneLinie(x + b, y, x + b, y + h); 
}
void zeichneBuchstabeO(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);            
    zeichneLinie(x, y + h, x + b, y + h);     
    zeichneLinie(x + b, y + h, x + b, y);     
    zeichneLinie(x + b, y, x, y);             
}

void zeichneBuchstabeP(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                     
    zeichneLinie(x, y + h, x + b, y + h);              
    zeichneLinie(x + b, y + h, x + b, y + h / 2);      
    zeichneLinie(x + b, y + h / 2, x, y + h / 2);      
}

void zeichneBuchstabeR(float x, float y, float b, float h) 
{
    zeichneLinie(x, y, x, y + h);                 
    zeichneLinie(x, y + h, x + b, y + h);        
    zeichneLinie(x + b, y + h, x + b, y + h / 2); 
    zeichneLinie(x + b, y + h / 2, x, y + h / 2); 
    zeichneLinie(x, y + h / 2, x + b, y);        
}

void zeichneBuchstabeS(float x, float y, float b, float h)
{
    zeichneLinie(x + b, y + h, x, y + h);
    zeichneLinie(x, y + h, x, y + h / 2);
    zeichneLinie(x, y + h / 2, x + b, y + h / 2);
    zeichneLinie(x + b, y + h / 2, x + b, y);
    zeichneLinie(x + b, y, x, y);
}

void zeichneBuchstabeT(float x, float y, float b, float h)
{
    zeichneLinie(x, y + h, x + b, y + h);
    zeichneLinie(x + b / 2, y + h, x + b / 2, y);
}

void zeichneBuchstabeU(float x, float y, float b, float h) 
{
    zeichneLinie(x, y + h, x, y);         
    zeichneLinie(x, y, x + b, y);         
    zeichneLinie(x + b, y, x + b, y + h); 
}

void zeichneBuchstabeV(int x, int y, int b, int h)
{
    zeichneLinie(x, y + h, x + b / 2, y);

    zeichneLinie(x + b / 2, y, x + b, y + h);
}

void zeichneBuchstabeW(int x, int y, int b, int h)
{
    zeichneLinie(x, y + h, x + b / 4, y);
    zeichneLinie(x + b / 4, y, x + b / 2, y + h / 2);
    zeichneLinie(x + b / 2, y + h / 2, x + 3 * b / 4, y);
    zeichneLinie(x + 3 * b / 4, y, x + b, y + h);
}

void zeichneBuchstabeY(float x, float y, float b, float h)
{
    // Linker und rechter oberer Arm.
    zeichneLinie(x, y + h, x + b / 2, y + h / 2);
    zeichneLinie(x + b / 2, y + h / 2, x + b, y + h);

    // Zum Mittelpunkt zurück, dann den Stamm nach unten.
    zeichneLinie(x + b, y + h, x + b / 2, y + h / 2);
    zeichneLinie(x + b / 2, y + h / 2, x + b / 2, y);
}

void zeichneUstrich(float x, float y, float h) 
{
    float b = h * 0.1; // Breite proportional zur Höhe
    zeichneLinie(x, y, x + b, y); // Horizontaler Strich
}





//Menü
void menueZeichnen() 
{
    zeichneRechteck(0, 0, 255, 255);    
    zeichneRechteck(64, 190, 128, 50);
    zeichneRechteck(59, 185, 138, 60);
    zeichneBuchstabeM(82, 205, 14, 20);
    zeichneBuchstabeE(106, 205, 12, 20);
    zeichneBuchstabeN(130, 205, 12, 20);
    zeichneBuchstabeU(154, 205, 12, 20);
    zeichneUstrich(157, 230, 20);
    zeichneUstrich(163, 230, 20);
}

void zeichneAuswahlPfeil(float x, float y, float groesse) 
{
    zeichneLinie(x, y + groesse, x, y);                    
    zeichneLinie(x, y, x + groesse, y + groesse / 2);       
    zeichneLinie(x + groesse, y + groesse / 2, x, y + groesse); 
}

void ZeichneVertikalerStrich(float x, float y, float breite) 
{
    zeichneLinie(x, y, breite, y);
}

void ZeichnePingPong(float y, float b, float h, float abstand) 
{
    float schritt = b + abstand; 
    float startX = 52; 
    zeichneRechteck(40, 120, 176, 50);
    zeichneBuchstabeP(startX,               y, b, h);
    zeichneBuchstabeI(startX + schritt,     y, b, h);
    zeichneBuchstabeN(startX + schritt*2,   y, b, h);
    zeichneBuchstabeG(startX + schritt*3,   y, b, h);
    zeichneBuchstabeP(startX + schritt*4,   y, b, h);
    zeichneBuchstabeO(startX + schritt*5,   y, b, h);
    zeichneBuchstabeN(startX + schritt*6,   y, b, h);
    zeichneBuchstabeG(startX + schritt*7,   y, b, h);
}

void zeichneRadar(float y, float b, float h, float abstand) 
{
    float schritt = b + abstand; // 20
    float startX = 82; // zentriert im Rechteck (40,60,176,50)

    zeichneRechteck(40, 62.5, 176, 50);
    zeichneBuchstabeR(startX,               y, b, h);
    zeichneBuchstabeA(startX + schritt,     y, b, h);
    zeichneBuchstabeD(startX + schritt*2,   y, b, h);
    zeichneBuchstabeA(startX + schritt*3,   y, b, h);
    zeichneBuchstabeR(startX + schritt*4,   y, b, h);
}

void ZeichneFlappy(float y, float b, float h, float abstand)
{
    float gesamtBreite = 6 * b + 5 * abstand;
    float startX = (255 - gesamtBreite) / 2;
    float schritt = b + abstand;
    zeichneRechteck(40, 62, 176, 50);
    zeichneBuchstabeF(startX,               y, b, h);
    zeichneBuchstabeL(startX + schritt,     y, b, h);
    zeichneBuchstabeA(startX + schritt * 2, y, b, h);
    zeichneBuchstabeP(startX + schritt * 3, y, b, h);
    zeichneBuchstabeP(startX + schritt * 4, y, b, h);
    zeichneBuchstabeY(startX + schritt * 5, y, b, h);
}

void ZeichneRunner(float y, float b, float h, float abstand) 
{
    float schritt = b + abstand;
    float startX = 72; 
    zeichneRechteck(40, 5, 176, 50);
    zeichneBuchstabeR(startX,               y, b, h);
    zeichneBuchstabeU(startX + schritt,     y, b, h);
    zeichneBuchstabeN(startX + schritt*2,   y, b, h);
    zeichneBuchstabeN(startX + schritt*3,   y, b, h);
    zeichneBuchstabeE(startX + schritt*4,   y, b, h);
    zeichneBuchstabeR(startX + schritt*5,   y, b, h);
}

void ZeichneModusPVP(int x, int y, int breite, int hoehe)
{
    zeichneRechteck(x, y, breite, hoehe);

    int b = 20;
    int h = 30;
    int abstand = 8;

    int textBreite = 3 * b + 2 * abstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeP(startX, startY, b, h);
    zeichneBuchstabeV(startX + b + abstand, startY, b, h);
    zeichneBuchstabeP(startX + 2 * (b + abstand), startY, b, h);
}

void ZeichneModusKI(int x, int y, int breite, int hoehe)
{

    zeichneRechteck(x, y, breite, hoehe);

    int b = 20;
    int h = 30;
    int abstand = 8;

    int textBreite = 2 * b + abstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeK(startX, startY, b, h);
    zeichneBuchstabeI(startX + b + abstand, startY, b, h);
}


void ZeichneModusLeicht(int x, int y, int breite, int hoehe)
{
    zeichneRechteck(x, y, breite, hoehe);

    int b = 16;
    int h = 30;
    int abstand = 8;
    int schritt = b + abstand;

    int textBreite = 6 * b + 5 * abstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeL(startX,               startY, b, h);
    zeichneBuchstabeE(startX + schritt,     startY, b, h);
    zeichneBuchstabeI(startX + schritt * 2, startY, b, h);
    zeichneBuchstabeC(startX + schritt * 3, startY, b, h);
    zeichneBuchstabeH(startX + schritt * 4, startY, b, h);
    zeichneBuchstabeT(startX + schritt * 5, startY, b, h);
}

void ZeichneModusMittel(int x, int y, int breite, int hoehe)
{
    zeichneRechteck(x, y, breite, hoehe);

    int b = 16;
    int h = 30;
    int abstand = 8;
    int schritt = b + abstand;

    int textBreite = 6 * b + 5 * abstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeM(startX,               startY, b, h);
    zeichneBuchstabeI(startX + schritt,     startY, b, h);
    zeichneBuchstabeT(startX + schritt * 2, startY, b, h);
    zeichneBuchstabeT(startX + schritt * 3, startY, b, h);
    zeichneBuchstabeE(startX + schritt * 4, startY, b, h);
    zeichneBuchstabeL(startX + schritt * 5, startY, b, h);
}

void ZeichneModusSchwer(int x, int y, int breite, int hoehe)
{
    zeichneRechteck(x, y, breite, hoehe);

    int b = 16;
    int h = 30;
    int abstand = 8;
    int schritt = b + abstand;

    int textBreite = 6 * b + 5 * abstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeS(startX,               startY, b, h);
    zeichneBuchstabeC(startX + schritt,     startY, b, h);
    zeichneBuchstabeH(startX + schritt * 2, startY, b, h);
    zeichneBuchstabeW(startX + schritt * 3, startY, b, h);
    zeichneBuchstabeE(startX + schritt * 4, startY, b, h);
    zeichneBuchstabeR(startX + schritt * 5, startY, b, h);
}

void ZeichneMario(float y, float b, float h, float abstand)
{
    float schritt = b + abstand;
    float gesamtBreite = 5 * b + 4 * abstand;
    float startX = 40 + (176 - gesamtBreite) / 2;

    zeichneRechteck(40, 120, 176, 50);

    zeichneBuchstabeM(startX,               y, b, h);
    zeichneBuchstabeA(startX + schritt,     y, b, h);
    zeichneBuchstabeR(startX + schritt * 2, y, b, h);
    zeichneBuchstabeI(startX + schritt * 3, y, b, h);
    zeichneBuchstabeO(startX + schritt * 4, y, b, h);
}

void ZeichneAsteroids(float y, float b, float h, float abstand)
{
    float schritt = b + abstand;
    float gesamtBreite = 9 * b + 8 * abstand;
    float startX = 40 + (176 - gesamtBreite) / 2;

    zeichneRechteck(40, 62, 176, 50);

    zeichneBuchstabeA(startX,               y, b, h);
    zeichneBuchstabeS(startX + schritt,     y, b, h);
    zeichneBuchstabeT(startX + schritt * 2, y, b, h);
    zeichneBuchstabeE(startX + schritt * 3, y, b, h);
    zeichneBuchstabeR(startX + schritt * 4, y, b, h);
    zeichneBuchstabeO(startX + schritt * 5, y, b, h);
    zeichneBuchstabeI(startX + schritt * 6, y, b, h);
    zeichneBuchstabeD(startX + schritt * 7, y, b, h);
    zeichneBuchstabeS(startX + schritt * 8, y, b, h);
}

//Pong Grafik
void ZeichneMittelstrich(float x, float y, float hoehe) 
{
    const int Strichlaenge = 5; 
    const int Abstand = 5;      
    
    for (int i = 0; i < hoehe; i += Strichlaenge + Abstand) 
    {  
        int ende = i + Strichlaenge;
        zeichneLinie(x, i, x, ende);
    }
}

void ZeichneGewinner(int x, int y, int breite, int hoehe, int spieler)
{
    if (spieler != 1 && spieler != 2)
    {
        return;
    }

    zeichneRechteck(x, y, breite, hoehe);

    int b = 16;
    int h = 32;
    int abstand = 5;
    int wortAbstand = 12;

    int textBreite = 5 * b + 3 * abstand + wortAbstand;
    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;

    zeichneBuchstabeP(startX, startY, b, h);

    zeichneZiffer(startX + b + abstand, startY, h, spieler);

    int wortX = startX + 2 * b + abstand + wortAbstand;

    zeichneBuchstabeW(wortX, startY, b, h);
    zeichneBuchstabeO(wortX + b + abstand, startY, b, h);
    zeichneBuchstabeN(wortX + 2 * (b + abstand), startY, b, h);
}








//Runner Grafik
void zeichneDino(int x, int y, bool laufBild, bool DinoGeduckt)
{
    if(DinoGeduckt == true)
    {
        zeichneLinie(x + 6,  y + 8,  x,      y + 15);
        zeichneLinie(x,      y + 15, x + 8,  y + 12);
        zeichneLinie(x + 8,  y + 12, x + 15, y + 15);

    
        zeichneLinie(x + 15, y + 15, x + 15, y + 20);
        zeichneLinie(x + 15, y + 20, x + 25, y + 20);
        zeichneLinie(x + 25, y + 20, x + 25, y + 13);
        zeichneLinie(x + 25, y + 13, x + 18, y + 13);
        zeichneLinie(x + 18, y + 13, x + 18, y + 8);

        if (laufBild)
        {
            
            zeichneLinie(x + 18, y + 8, x + 15, y);
            zeichneLinie(x + 15, y,     x + 20, y);

            
            zeichneLinie(x + 20, y, x + 15, y);
            zeichneLinie(x + 15, y, x + 11, y + 6);

            
            zeichneLinie(x + 11, y + 6, x + 8, y + 3);
            zeichneLinie(x + 8,  y + 3, x + 4, y + 3);
            zeichneLinie(x + 4,  y + 3, x + 6, y + 8);
        }
        else
        {
            zeichneLinie(x + 18, y + 8, x + 20, y + 3);
            zeichneLinie(x + 20, y + 3, x + 24, y + 3);

            
            zeichneLinie(x + 24, y + 3, x + 20, y + 3);
            zeichneLinie(x + 20, y + 3, x + 11, y + 6);

            
            zeichneLinie(x + 11, y + 6, x + 8, y);
            zeichneLinie(x + 8,  y,     x + 4, y);
            zeichneLinie(x + 4,  y,     x + 6, y + 8);
        }
        zeichneLinie(x + 20, y + 17, x + 22, y + 17);

        zeichneLinie(x + 18, y + 11, x + 23, y + 11);
        zeichneLinie(x + 18, y + 9,  x + 23, y + 9);
    }
    else
    {   
        zeichneLinie(x + 6,  y + 12, x,      y + 21);
        zeichneLinie(x,      y + 21, x + 8,  y + 15);
        zeichneLinie(x + 8,  y + 15, x + 13, y + 21);
        zeichneLinie(x + 13, y + 21, x + 13, y + 36);
        zeichneLinie(x + 13, y + 36, x + 25, y + 36);
        zeichneLinie(x + 25, y + 36, x + 25, y + 26);
        zeichneLinie(x + 25, y + 26, x + 18, y + 26);
        zeichneLinie(x + 18, y + 26, x + 18, y + 12);

        if (laufBild)
        {
            zeichneLinie(x + 18, y + 12, x + 15, y);
            zeichneLinie(x + 15, y,      x + 20, y);

            zeichneLinie(x + 20, y, x + 15, y);
            zeichneLinie(x + 15, y, x + 11, y + 9);

            zeichneLinie(x + 11, y + 9, x + 8, y + 5);
            zeichneLinie(x + 8,  y + 5, x + 4, y + 5);
            zeichneLinie(x + 4,  y + 5, x + 6, y + 12);
        }
        else
        {
            
            zeichneLinie(x + 18, y + 12, x + 20, y + 6);
            zeichneLinie(x + 20, y + 6,  x + 25, y + 6);

            zeichneLinie(x + 25, y + 6, x + 20, y + 6);
            zeichneLinie(x + 20, y + 6, x + 11, y + 9);

            zeichneLinie(x + 11, y + 9, x + 8, y);
            zeichneLinie(x + 8,  y,     x + 4, y);
            zeichneLinie(x + 4,  y,     x + 6, y + 12);
        }

        zeichneLinie(x + 20, y + 32, x + 22, y + 32);
        zeichneLinie(x + 18, y + 20, x + 23, y + 20);
        zeichneLinie(x + 18, y + 18, x + 23, y + 18);
    }

}

void zeichneFledermaus(int x, int y, bool laufbild)
{
    int spitzeY;
    int aussenY;
    int innenY;

    if(laufbild)
    {
        spitzeY = y + 14;
        aussenY = y + 6;
        innenY  = y + 8;
    }
    else
    {
        spitzeY = y;
        aussenY = y + 1;
        innenY  = y + 4;
    }
 
    zeichneLinie(x,     spitzeY, x + 9, y + 7);
    zeichneLinie(x + 9, y + 7,   x + 9, y + 12);
    zeichneLinie(x + 9, y + 12,  x + 12, y + 9);

    zeichneLinie(x + 12, y + 9,  x + 15, y + 12);
    zeichneLinie(x + 15, y + 12, x + 15, y + 7);

    zeichneLinie(x + 15, y + 7,  x + 24, spitzeY);
    zeichneLinie(x + 24, spitzeY, x + 21, aussenY);
    zeichneLinie(x + 21, aussenY, x + 18, innenY);
    zeichneLinie(x + 18, innenY,  x + 15, y + 1);

    zeichneLinie(x + 15, y + 1, x + 12, y);
    zeichneLinie(x + 12, y,     x + 9, y + 1);

    zeichneLinie(x + 9, y + 1,  x + 6, innenY);
    zeichneLinie(x + 6, innenY,  x + 3, aussenY);
    zeichneLinie(x + 3, aussenY, x,     spitzeY);
}

void zeichneKaktus(int x, int y)
{
    // Vom Stammfuß aus einmal um den gesamten Umriss
    zeichneLinie(x + 7,  y,      x + 7,  y + 9);

    // Linker Arm
    zeichneLinie(x + 7,  y + 9,  x + 2,  y + 9);
    zeichneLinie(x + 2,  y + 9,  x,      y + 11);
    zeichneLinie(x,      y + 11, x,      y + 18);
    zeichneLinie(x,      y + 18, x + 2,  y + 20);
    zeichneLinie(x + 2,  y + 20, x + 4,  y + 18);
    zeichneLinie(x + 4,  y + 18, x + 4,  y + 13);
    zeichneLinie(x + 4,  y + 13, x + 7,  y + 13);

    // Stamm und Spitze
    zeichneLinie(x + 7,  y + 13, x + 7,  y + 26);
    zeichneLinie(x + 7,  y + 26, x + 9,  y + 28);
    zeichneLinie(x + 9,  y + 28, x + 11, y + 28);
    zeichneLinie(x + 11, y + 28, x + 13, y + 26);
    zeichneLinie(x + 13, y + 26, x + 13, y + 17);

    // Rechter Arm
    zeichneLinie(x + 13, y + 17, x + 17, y + 17);
    zeichneLinie(x + 17, y + 17, x + 17, y + 22);
    zeichneLinie(x + 17, y + 22, x + 19, y + 24);
    zeichneLinie(x + 19, y + 24, x + 21, y + 22);
    zeichneLinie(x + 21, y + 22, x + 21, y + 15);
    zeichneLinie(x + 21, y + 15, x + 19, y + 13);
    zeichneLinie(x + 19, y + 13, x + 13, y + 13);

    // Zurück zum Stammfuß
    zeichneLinie(x + 13, y + 13, x + 13, y);
    zeichneLinie(x + 13, y,      x + 7,  y);
}

void ZeichneGrashalme(int x, float y, int Breite)
{
    const float Strichlaenge = 4.5;
    const int Abstand = 3;

    for (int i = 0; i < Breite; i += Abstand)
    {
        zeichneLinie(x + i, y, x + i, y + Strichlaenge);
    }
}

void ZeichneGameOver(int x, int y, int breite, int hoehe)
{
    zeichneRechteck(x, y, breite, hoehe);

    int buchstabenAbstand = 4;
    int wortAbstand = 12;
    int b = 12;
    int h = 40;

    int textBreite = 8 * b + 6 * buchstabenAbstand + wortAbstand;

    int startX = x + (breite - textBreite) / 2;
    int startY = y + (hoehe - h) / 2;
    int schritt = b + buchstabenAbstand;

    zeichneBuchstabeG(startX,               startY, b, h);
    zeichneBuchstabeA(startX + schritt,     startY, b, h);
    zeichneBuchstabeM(startX + schritt * 2, startY, b, h);
    zeichneBuchstabeE(startX + schritt * 3, startY, b, h);

    int overX = startX + 4 * b + 3 * buchstabenAbstand + wortAbstand;

    zeichneBuchstabeO(overX,               startY, b, h);
    zeichneBuchstabeV(overX + schritt,     startY, b, h);
    zeichneBuchstabeE(overX + schritt * 2, startY, b, h);
    zeichneBuchstabeR(overX + schritt * 3, startY, b, h);
}

void zeichneVogel(int x, int y, bool fluegelOben)
{
    // Schwanz, Rücken und runder Kopf
    zeichneLinie(x + 4,  y + 5,  x,      y + 6);
    zeichneLinie(x,      y + 6,  x + 2,  y + 10);
    zeichneLinie(x + 2,  y + 10, x,      y + 13);
    zeichneLinie(x,      y + 13, x + 5,  y + 12);
    zeichneLinie(x + 5,  y + 12, x + 8,  y + 16);
    zeichneLinie(x + 8,  y + 16, x + 14, y + 18);
    zeichneLinie(x + 14, y + 18, x + 18, y + 16);
    zeichneLinie(x + 18, y + 16, x + 20, y + 12);

    // Schnabel
    zeichneLinie(x + 20, y + 12, x + 23, y + 11);
    zeichneLinie(x + 23, y + 11, x + 24, y + 9);
    zeichneLinie(x + 24, y + 9,  x + 23, y + 7);
    zeichneLinie(x + 23, y + 7,  x + 18, y + 7);

    // Bauch
    zeichneLinie(x + 18, y + 7, x + 16, y + 3);
    zeichneLinie(x + 16, y + 3, x + 9,  y + 2);
    zeichneLinie(x + 9,  y + 2, x + 4,  y + 5);

    // Flügel
    if (fluegelOben)
    {
        zeichneLinie(x + 12, y + 8,  x + 9, y + 15);
        zeichneLinie(x + 9,  y + 15, x + 5, y + 16);
        zeichneLinie(x + 5,  y + 16, x + 4, y + 12);
        zeichneLinie(x + 4,  y + 12, x + 7, y + 9);
        zeichneLinie(x + 7,  y + 9,  x + 12, y + 8);
    }
    else
    {
        zeichneLinie(x + 12, y + 8, x + 7, y + 9);
        zeichneLinie(x + 7,  y + 9, x + 4, y + 6);
        zeichneLinie(x + 4,  y + 6, x + 5, y + 2);
        zeichneLinie(x + 5,  y + 2, x + 8, y);
        zeichneLinie(x + 8,  y,     x + 12, y + 8);
    }

    // Auge
    zeichneLinie(x + 14, y + 11, x + 13, y + 14);
    zeichneLinie(x + 13, y + 14, x + 15, y + 16);
    zeichneLinie(x + 15, y + 16, x + 18, y + 15);
    zeichneLinie(x + 18, y + 15, x + 19, y + 12);
    zeichneLinie(x + 19, y + 12, x + 14, y + 11);

    // Pupille
    zeichneLinie(x + 17, y + 12, x + 17, y + 14);

    // Schnabelteilung
    zeichneLinie(x + 19, y + 9, x + 24, y + 9);
}

void zeichneRoehren(int x, int breite, int lueckeY, int lueckeHoehe)
{
    const int ueberstand = 4;
    const int randHoehe = 8;

    int oben = lueckeY + lueckeHoehe;
    int untenRand = lueckeY - randHoehe;
    int obenRand = oben + randHoehe;

    // UNTERE RÖHRE: Körper ohne doppelte Oberkante
    zeichneLinie(x, untenRand, x, 0);
    zeichneLinie(x, 0, x + breite, 0);
    zeichneLinie(x + breite, 0, x + breite, untenRand);

    // Breite Öffnung
    zeichneRechteck(
        x - ueberstand, untenRand,
        breite + 2 * ueberstand, randHoehe
    );

    // Zusätzliche Kante am Rand
    zeichneLinie(
        x - ueberstand, lueckeY - 3,
        x + breite + ueberstand, lueckeY - 3
    );

    // Glanzstreifen am Körper
    if (untenRand > 8)
    {
        zeichneLinie(x + 4, 4, x + 4, untenRand - 4);
    }

    // OBERE RÖHRE: Körper
    zeichneLinie(x, obenRand, x, 255);
    zeichneLinie(x, 255, x + breite, 255);
    zeichneLinie(x + breite, 255, x + breite, obenRand);

    // Breite Öffnung
    zeichneRechteck(
        x - ueberstand, oben,
        breite + 2 * ueberstand, randHoehe
    );

    // Zusätzliche Kante am Rand
    zeichneLinie(
        x - ueberstand, oben + 3,
        x + breite + ueberstand, oben + 3
    );

    // Glanzstreifen am Körper
    if (obenRand < 247)
    {
        zeichneLinie(x + 4, obenRand + 4, x + 4, 251);
    }
}

void zeichneWolke(int x, int y)
{
    zeichneLinie(x + 6,  y,      x + 34, y);
    zeichneLinie(x + 34, y,      x + 40, y + 5);
    zeichneLinie(x + 40, y + 5,  x + 40, y + 10);
    zeichneLinie(x + 40, y + 10, x + 35, y + 14);
    zeichneLinie(x + 35, y + 14, x + 29, y + 14);
    zeichneLinie(x + 29, y + 14, x + 26, y + 20);
    zeichneLinie(x + 26, y + 20, x + 17, y + 20);
    zeichneLinie(x + 17, y + 20, x + 12, y + 14);
    zeichneLinie(x + 12, y + 14, x + 6,  y + 14);
    zeichneLinie(x + 6,  y + 14, x,      y + 9);
    zeichneLinie(x,      y + 9,  x,      y + 5);
    zeichneLinie(x,      y + 5,  x + 6,  y);
}


//Asteroids Grafiken
void zeichneDreieck(float linksX, float linksY, float obenx, float obeny, float rechtsX, float rechtsY)
{
    zeichneLinie(linksX, linksY, rechtsX, rechtsY);
    zeichneLinie(rechtsX, rechtsY, obenx, obeny);
    zeichneLinie(obenx, obeny, linksX, linksY);
}

void RechteckZeichnen(float linksUntenX, float linksUntenY, float linksObenX, float linksObenY, float rechtsUntenX, float rechtsUntenY, float rechtsObenX, float rechtsObenY)
{
    zeichneLinie(linksUntenX, linksUntenY, rechtsUntenX, rechtsUntenY);
    zeichneLinie(rechtsUntenX, rechtsUntenY, rechtsObenX, rechtsObenY);
    zeichneLinie(rechtsObenX, rechtsObenY, linksObenX, linksObenY);
    zeichneLinie(linksObenX, linksObenY, linksUntenX, linksUntenY);
}

void zeichneAsteroidZeichnen(int x, int y, int groesse)
{
    float r = groesse;

    // Felsiger Umriss
    zeichneLinie(x - r * 0.94, y + r * 0.08,
                 x - r * 0.83, y + r * 0.47);

    zeichneLinie(x - r * 0.83, y + r * 0.47,
                 x - r * 0.55, y + r * 0.62);

    zeichneLinie(x - r * 0.55, y + r * 0.62,
                 x - r * 0.40, y + r * 0.88);

    zeichneLinie(x - r * 0.40, y + r * 0.88,
                 x + r * 0.05, y + r * 0.96);

    zeichneLinie(x + r * 0.05, y + r * 0.96,
                 x + r * 0.27, y + r * 0.78);

    zeichneLinie(x + r * 0.27, y + r * 0.78,
                 x + r * 0.58, y + r * 0.78);

    zeichneLinie(x + r * 0.58, y + r * 0.78,
                 x + r * 0.87, y + r * 0.39);

    zeichneLinie(x + r * 0.87, y + r * 0.39,
                 x + r * 0.82, y + r * 0.10);

    zeichneLinie(x + r * 0.82, y + r * 0.10,
                 x + r * 0.97, y - r * 0.13);

    zeichneLinie(x + r * 0.97, y - r * 0.13,
                 x + r * 0.79, y - r * 0.54);

    zeichneLinie(x + r * 0.79, y - r * 0.54,
                 x + r * 0.44, y - r * 0.62);

    zeichneLinie(x + r * 0.44, y - r * 0.62,
                 x + r * 0.23, y - r * 0.92);

    zeichneLinie(x + r * 0.23, y - r * 0.92,
                 x - r * 0.23, y - r * 0.95);

    zeichneLinie(x - r * 0.23, y - r * 0.95,
                 x - r * 0.61, y - r * 0.73);

    zeichneLinie(x - r * 0.61, y - r * 0.73,
                 x - r * 0.64, y - r * 0.46);

    zeichneLinie(x - r * 0.64, y - r * 0.46,
                 x - r * 0.91, y - r * 0.31);

    zeichneLinie(x - r * 0.91, y - r * 0.31,
                 x - r * 0.94, y + r * 0.08);

    // Bei kleinen Asteroiden bleibt nur der Umriss
    if (groesse < 12)
    {
        return;
    }

    // Große, unregelmäßige Vertiefung links oben
    zeichneLinie(x - r * 0.59, y + r * 0.28,
                 x - r * 0.38, y + r * 0.55);

    zeichneLinie(x - r * 0.38, y + r * 0.55,
                 x - r * 0.06, y + r * 0.48);

    zeichneLinie(x - r * 0.06, y + r * 0.48,
                 x + r * 0.02, y + r * 0.22);

    zeichneLinie(x + r * 0.02, y + r * 0.22,
                 x - r * 0.25, y + r * 0.05);

    zeichneLinie(x - r * 0.25, y + r * 0.05,
                 x - r * 0.53, y + r * 0.10);

    zeichneLinie(x - r * 0.53, y + r * 0.10,
                 x - r * 0.59, y + r * 0.28);

    // Zweite Vertiefung rechts unten, bewusst offen
    zeichneLinie(x + r * 0.50, y - r * 0.08,
                 x + r * 0.25, y - r * 0.16);

    zeichneLinie(x + r * 0.25, y - r * 0.16,
                 x + r * 0.18, y - r * 0.40);

    zeichneLinie(x + r * 0.18, y - r * 0.40,
                 x + r * 0.43, y - r * 0.48);
}

void zeichneSchub(
    float linksX, float linksY,
    float spitzeX, float spitzeY,
    float rechtsX, float rechtsY)
{
    // Äußere Flamme
    zeichneLinie(linksX, linksY, spitzeX, spitzeY);
    zeichneLinie(spitzeX, spitzeY, rechtsX, rechtsY);

    // Mitte der Antriebsöffnung
    float mitteX = (linksX + rechtsX) / 2.0f;
    float mitteY = (linksY + rechtsY) / 2.0f;

    // Kürzere Spitze innerhalb der äußeren Flamme
    float innenX = mitteX + (spitzeX - mitteX) * 0.55f;
    float innenY = mitteY + (spitzeY - mitteY) * 0.55f;

    // Innere Flamme beginnt etwas näher an der Mitte
    float innenLinksX = mitteX + (linksX - mitteX) * 0.5f;
    float innenLinksY = mitteY + (linksY - mitteY) * 0.5f;
    float innenRechtsX = mitteX + (rechtsX - mitteX) * 0.5f;
    float innenRechtsY = mitteY + (rechtsY - mitteY) * 0.5f;

    zeichneLinie(innenLinksX, innenLinksY, innenX, innenY);
    zeichneLinie(innenX, innenY, innenRechtsX, innenRechtsY);
}


void zeichneLeben(float g, int leben)
{
    //Spitze      (0/12)
    //Rechtsunten (8/-8)
    //Kerberechts (3/-8)
    //Kerbe links (-3/-8)
    //Linksunten  (-8/-8)
    //Kerbe       (0/-4)     
    int startX = 215;
    int startY = 240;
    int abstand = 14;  

    float spitzeX      =  0 * g;
    float spitzeY      = 12 * g;
    float rechtsUntenX =  8 * g;
    float rechtsUntenY = -8 * g;
    float kerbeRechtsX =  3 * g;
    float kerbeRechtsY = -8 * g;
    float kerbeX       =  0 * g;
    float kerbeY       = -4 * g;
    float kerbeLinksX  = -3 * g;
    float kerbeLinksY  = -8 * g;
    float linksUntenX  = -8 * g;
    float linksUntenY  = -8 * g;


    for (int i = 0; i < leben; i++)
    {
        int x = startX + i * abstand;

        zeichneLinie(roundf(x + spitzeX),      roundf(startY + spitzeY),      roundf(x + rechtsUntenX), roundf(startY + rechtsUntenY));
        zeichneLinie(roundf(x + rechtsUntenX), roundf(startY + rechtsUntenY), roundf(x + kerbeRechtsX), roundf(startY + kerbeRechtsY));
        zeichneLinie(roundf(x + kerbeRechtsX), roundf(startY + kerbeRechtsY), roundf(x + kerbeX),       roundf(startY + kerbeY));
        zeichneLinie(roundf(x + kerbeX),       roundf(startY + kerbeY),       roundf(x + kerbeLinksX),  roundf(startY + kerbeLinksY));
        zeichneLinie(roundf(x + kerbeLinksX),  roundf(startY + kerbeLinksY),  roundf(x + linksUntenX),  roundf(startY + linksUntenY));
        zeichneLinie(roundf(x + linksUntenX),  roundf(startY + linksUntenY),  roundf(x + spitzeX),      roundf(startY + spitzeY));
    }
}

 










