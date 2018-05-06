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

Blocco::Blocco(int posX, int posY, Tipo t)  {
    exploded=false;
    srand(time(0));
    int a = rand()%3+1;
    tipo = t;
    this->posX=posX;
    this->posY=posY;
    esplosione.setPosX(posX);
    esplosione.setPosY(posY);
    if(tipo == bloccoPietra)  {
        dimX = 56; dimY = 24;
        if(a==1)
            blocco=al_load_bitmap("images/stoneBlock1.png");
        else if(a==2)
            blocco=al_load_bitmap("images/stoneBlock2.png");
        else if(a==3)
            blocco=al_load_bitmap("images/stoneBlock3.png");
    } 
    else if(tipo == bloccoVetro1)  {
        dimX = 29; dimY = 61;
        blocco = al_load_bitmap("images/bloccoVetro.png");
    } 
    else if(tipo == bloccoVetro2)  { 
        dimX=41; dimY=24;
        blocco=al_load_bitmap("images/bloccoVetro2.png");
    } 
    else
        blocco=NULL;

    esplosione.setTipo(tipo);
}

Blocco::~Blocco()  {
    if(blocco)  {
        al_destroy_bitmap(blocco);
    }
}

bool Blocco::Draw(){
    if(exploded){
        if(!esplosione.Draw())
                return false;
    }    
    else
        al_draw_bitmap(blocco,posX,posY,0);

    return true;        

}


bool Blocco::hitByHook(Giocatore* player)  {
    float   x = player->getArmaX(),
            y = player->getArmaY(),
            d = player->getArmaDim();

    if(x+d < posX)      return false;
    if(x > posX+dimX)   return false;
    if(y > posY+dimY)   return false;

    return true;
}


#endif