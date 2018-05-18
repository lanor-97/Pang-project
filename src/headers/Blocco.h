#ifndef BLOCCO_H
#define BLOCCO_H

#include "Esplosione.h"
#include "Giocatore.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
using namespace std;

class Blocco  {   
private:
    int     dimX,
            dimY,
            posX,
            posY;
    bool exploded;        
    ALLEGRO_BITMAP *blocco;
    Esplosione esplosione;
    Tipo tipo; //tipi possibili: bloccoPietra, bloccoVetro1 (verticale), bloccoVetro2 (orizzontale)

public:
    Blocco(): posX(0), posY(0), dimX(0), dimY(0), tipo(bloccoPietra), blocco(NULL)  {}
    Blocco(int,int, Tipo);
    ~Blocco();

    //ALLEGRO_BITMAP* getBitmap() const  { return blocco; }
    int getX() const  { return posX; }
    int getY() const  { return posY; }
    int getDimX() const  { return dimX; }
    int getDimY() const  { return dimY; }
    Tipo getTipo() const  { return tipo; }
    //ALLEGRO_BITMAP* getBlocco() const  { return blocco; }
    void setExploded(bool x)  { exploded=x; }
    void setPosX(int x)  { posX = x; esplosione.setPosX(posX); }
    void setPosY(int y)  { posY = y; esplosione.setPosY(posY); }

    bool Draw();
    bool hitByHook(Giocatore*);
};


#endif