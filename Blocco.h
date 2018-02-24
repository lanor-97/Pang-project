#ifndef BLOCCO_H
#define BLOCCO_H
#include "Esplosione.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
using namespace std;

class Blocco
{   
    private:
    int posX;
    int posY;
    int dimX;
    int dimY;
    ALLEGRO_BITMAP *blocco;
    Esplosione esplosione;
    Tipo tipo; //tipi possibili: bloccoPietra, bloccoVetro1 (verticale), bloccoVetro2 (orizzontale)

    public:
    Blocco():posX(0),posY(0),dimX(0),dimY(0),tipo(bloccoPietra), blocco(NULL){}
    Blocco(Tipo t,int posX,int posY)
    {
        srand(time(0));
        int a=rand()%4;
        tipo=t;
        this->posX=posX;
        this->posY=posY;
        esplosione.setPosX(posX);
        esplosione.setPosY(posY);
        if(tipo==bloccoPietra)
           {
               dimX=56; dimY=24;
               if(a==1)
               blocco=al_load_bitmap("images/stoneBlock1.png");
               if(a==2)
               blocco=al_load_bitmap("images/stoneBlock2.png");
               if(a==3)
               blocco=al_load_bitmap("images/stoneBlock3.png");
           } 
        if(tipo==bloccoVetro1)
           {
               dimX=29; dimY=61;
               blocco=al_load_bitmap("images/bloccoVetro.png");
           } 
        if(tipo==bloccoVetro2)
           { 
               dimX=41; dimY=24;
               blocco=al_load_bitmap("images/bloccoVetro2.png");
           } 

        esplosione.setTipo(tipo);
    }
    ~Blocco(){al_destroy_bitmap(blocco);}

     int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getDimX(){return dimX;}
    int getDimY(){return dimY;}
    Tipo getTipo(){return tipo;}

    ALLEGRO_BITMAP *getBlocco() const{return blocco;}
    void setPosX(int x){posX=x;  esplosione.setPosX(posX);}
    void setPosY(int y){posY=y; esplosione.setPosY(posY);}
    void setBlocco(ALLEGRO_BITMAP *bitmap){blocco=bitmap;}
    void setDimX(int size){this->dimX=size;}
    void setDimY(int size){this->dimY=size;}
    void setTipo(int t)
    {
        srand(time(0));
        if(t==1)
            tipo=bloccoPietra;
        if(t==2)
            tipo=bloccoVetro1;
        if(t==3)
            tipo=bloccoVetro2;
        if(tipo==bloccoPietra)
           {    
               int a=rand()%4;
               dimX=56; dimY=24;
               if(a==1)
               blocco=al_load_bitmap("images/stoneBlock1.png");
               if(a==2)
               blocco=al_load_bitmap("images/stoneBlock2.png");
               if(a==3)
               blocco=al_load_bitmap("images/stoneBlock3.png");
           }
        if(tipo==bloccoVetro1)
           {
               dimX=29; dimY=61;
               blocco=al_load_bitmap("images/bloccoVetro.png");
           } 
        if(tipo==bloccoVetro2)
           { 
               dimX=41; dimY=24;
               blocco=al_load_bitmap("images/bloccoVetro2.png");
           }
        esplosione.setTipo(tipo);        
    }

    void Draw(){al_draw_bitmap(blocco,posX,posY,0);}

    bool DrawExplosion()
    {
        if(!esplosione.Draw())
        return false;
        return true;
    }
};
#endif