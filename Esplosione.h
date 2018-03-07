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
    Esplosione(){
        posX=0; posY=0;
        dimX=0; dimY=0; tipo=pallaPic;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
    }

    Esplosione(int x,int y,Tipo tipo)
    {
        posX=x;
        posY=y;
        this->tipo=tipo;
        if(tipo==pallaPic)
        {
            dimX=20; dimY=20;
            setExplosion(al_load_bitmap("images/esplosionePic.png"));
        }    
        if(tipo==pallaMed)
        {
            dimX=40; dimY=40;
            setExplosion(al_load_bitmap("images/esplosioneMed.png"));
        }    
        if(tipo==pallaGra)
        {
            dimX=70; dimY=70;
            setExplosion(al_load_bitmap("images/esplosioneGra.png"));
        }    
        if(tipo==bloccoPietra)
        {
            dimX=56; dimY=24;
            setExplosion(al_load_bitmap("images/stoneAnimation.png"));
        }    
        if(tipo==bloccoVetro1)
        {
            dimX=29; dimY=61;
            setExplosion(al_load_bitmap("images/animazioneVetro2.png"));
        }    
        if(tipo==bloccoVetro2)
        {
            dimX=41; dimY=24;
            setExplosion(al_load_bitmap("images/animazioneVetro1.png"));
        }    
        animazione.setFrameCount(0);
        animazione.setFrameDelay(5);
        animazione.setCurrFrame(0);
    }
	~Esplosione()  { if(explosion) al_destroy_bitmap(explosion);}
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getDimX(){return dimX;}
    int getDimY(){return dimY;}
    Tipo getTipo(){return tipo;}
    ALLEGRO_BITMAP *getExplosion() const{return explosion;}

    void setPosX(int x){posX=x;}
    void setPosY(int y){posY=y;}
    void setExplosion(ALLEGRO_BITMAP *bitmap){explosion=bitmap;}
    void setDimX(int size){this->dimX=size;}
    void setDimY(int size){this->dimY=size;}
    void setTipo(int t){
        if(t==0)
        {   
            tipo=pallaPic;
            dimX=20; dimY=20;
            setExplosion(al_load_bitmap("images/esplosionePic.png"));
        }    
        if(t==1)
        {
            tipo=pallaMed;
            dimX=40; dimY=40;
            setExplosion(al_load_bitmap("images/esplosioneMed.png"));
        }    
        if(t==2)
        {
            tipo=pallaGra;
            dimX=70; dimY=70;
            setExplosion(al_load_bitmap("images/esplosioneGra.png"));
        }    
        if(t==3)
        {
            tipo=bloccoPietra;
            dimX=56; dimY=24;
            setExplosion(al_load_bitmap("images/stoneAnimation.png"));
        }    
        if(t==4)
        {
            tipo=bloccoVetro1;
            dimX=29; dimY=61;
            setExplosion(al_load_bitmap("images/animazioneVetro2.png"));
        }    
        if(t==5)
        {
            tipo=bloccoVetro2;
            dimX=41; dimY=24;
            setExplosion(al_load_bitmap("images/animazioneVetro1.png"));
        }    
    }
    bool Draw()
    {
       if(getTipo()==pallaPic)
        {
                if(animazione.eseguiFrame(explosion,getDimX(),getDimY(),getPosX(),getPosY(), false,5))
                    return true;
        }            
       else
            if(animazione.eseguiFrame(explosion,getDimX(),getDimY(),getPosX(),getPosY(), false,4))
                    return true;
       return false;         

    }

};


#endif