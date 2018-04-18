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
    int     dim_x,
            dim_y,
            posX,
            posY;
    bool exploded;        
    ALLEGRO_BITMAP *blocco;
    Esplosione esplosione;
    Tipo tipo; //tipi possibili: bloccoPietra, bloccoVetro1 (verticale), bloccoVetro2 (orizzontale)

public:
    Blocco(): posX(0), posY(0), dim_x(0), dim_y(0), tipo(bloccoPietra), blocco(NULL)  {}
    Blocco(int,int, Tipo);
    ~Blocco();

    //ALLEGRO_BITMAP* getBitmap() const  { return blocco; }
    int getX() const  { return posX; }
    int getY() const  { return posY; }
    int getDim_x() const  { return dim_x; }
    int getDim_y() const  { return dim_y; }
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
        dim_x = 56; dim_y = 24;
        if(a==1)
            blocco=al_load_bitmap("images/stoneBlock1.png");
        else if(a==2)
            blocco=al_load_bitmap("images/stoneBlock2.png");
        else if(a==3)
            blocco=al_load_bitmap("images/stoneBlock3.png");
    } 
    else if(tipo == bloccoVetro1)  {
        dim_x = 29; dim_y = 61;
        blocco = al_load_bitmap("images/bloccoVetro.png");
    } 
    else if(tipo == bloccoVetro2)  { 
        dim_x=41; dim_y=24;
        blocco=al_load_bitmap("images/bloccoVetro2.png");
    } 
    else
        blocco=NULL;

    esplosione.setTipo(tipo);
}

Blocco::~Blocco()  {
    if(blocco)  {
        cerr << "\ndistruggo blocco_bitmap";
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
    float   x = player->getX_arma(),
            y = player->getY_arma(),
            d = player->getDim_arma();

    if(x+d < posX)      return false;
    if(x > posX+dim_x)  return false;
    if(y > posY+dim_y)  return false;

    return true;
}


#endif