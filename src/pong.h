#ifndef PONG_H
#define PONG_H

#include <Arduino.h>

void setupPong();
void loopPong();
void resetPong();
void PlayerVsKI();
void loopPongKI(int KISchwierigkeit);
void starteCountdown();
void KIBewegung(int KISchwierigkeit);
void KIBewegungLeicht();
void KIBewegungMittel();
void KIBewegungSchwer();
#endif