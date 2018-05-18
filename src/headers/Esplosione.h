#ifndef ESPLOSIONE_H
#define ESPLOSIONE_H

#include "Animation.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <iostream>
using namespace std;
enum Tipo{pallaPic=0, pallaMed, pallaGra, bloccoPietra, bloccoVetro1, bloccoVetro2};

class Esplosione{
private:
    ALLEGRO_BITMAP *explosion;
    Animation animazione;
    int posX;
    int posY;
    int dimX;
    int dimY;
    Tipo tipo;

public:
    Esplosione();
    Esplosione(int x,int y,Tipo tipo);
	~Esplosione()  { if(explosion)  al_destroy_bitmap(explosion); }

    int getPosX() const  {return posX;}
    int getPosY() const  {return posY;}
    int getDimX() const  {return dimX;}
    int getDimY() const  {return dimY;}
    Tipo getTipo() const  {return tipo;}
    ALLEGRO_BITMAP *getExplosion() const{return explosion;}

    void setPosX(int x){posX=x;}
    void setPosY(int y){posY=y;}
    void setExplosion(ALLEGRO_BITMAP *bitmap){explosion=bitmap;}
    void setDimX(int size){this->dimX=size;}
    void setDimY(int size){this->dimY=size;}
    void setTipo(int t);
    
    bool Draw();

};


#endif