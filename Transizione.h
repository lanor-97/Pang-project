#ifndef TRANSIZIONE_H
#define TRANSIZIONE_H
#include "Animation.h"
#include <iostream>
using namespace std;

enum Tipe {menuClose=0, levelStart, stageClear, stageClearClose, victory, victoryClose};
class Transizione
{
    private:
    int dimX;
    int dimY;
    ALLEGRO_BITMAP *transition;
    Animation animazione;
    Tipe tipo;

    public:
    Transizione()
    {
        dimX=640;
        dimY=480;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(0);
        animazione.setCurrFrame(0);
    }
    Transizione(Tipe tipo)
    {
        dimX=640;
        dimY=480;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(0);
        animazione.setCurrFrame(0);
        this->tipo=tipo;
        if(tipo==menuClose)
        transition=al_load_bitmap("images/menuTransition.png");
        if(tipo==levelStart)
        transition=al_load_bitmap("images/levelStart.png");
        if(tipo==stageClear)
        transition=al_load_bitmap("images/stageClear.png");
        if(tipo==stageClearClose)
        transition=al_load_bitmap("images/stageClearClose.png");
        if(tipo==victory)
        transition=al_load_bitmap("images/victory.png");
        if(tipo==victoryClose)
        transition=al_load_bitmap("images/victoryClose.png");

    }
    ~Transizione()  { cerr<<"\ndistruggo transizione_bitmap"; if(transition) al_destroy_bitmap(transition); }
    int getDimX(){return dimX;}
    int getDimY(){return dimY;}
    
    void setDimX(int n){dimX=n;}
    void setDimY(int n){dimY=n;}

    ALLEGRO_BITMAP* getTransition(){return transition;}
    void setTransition(ALLEGRO_BITMAP* T){transition=T;}
    
    Tipe getTipo(){return tipo;}
    void setTipo(int t)
    {
        if(t==0)
        {
            
            tipo=menuClose;
            transition=al_load_bitmap("images/menuTransition.png");
        }    
        if(t==1)
        {
            tipo=levelStart;
            transition=al_load_bitmap("images/levelStart.png");
        }    
        if(t==2)
        {
            tipo=stageClear;
            transition=al_load_bitmap("images/stageClear.png");
        }    
        if(t==3)
        {
            tipo=stageClearClose;
            transition=al_load_bitmap("images/stageClearClose.png");
        }    
        if(t==4)
        {
            tipo=victory;
            transition=al_load_bitmap("images/victory.png");
        }    
        if(t==5)
        {
            tipo=victoryClose;
            transition=al_load_bitmap("images/victoryClose.png");
        }    
    }

    bool Draw()
    {
        if(tipo==menuClose || tipo==levelStart)
            if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,15))
                return true;   

        if(tipo==stageClear || tipo==victory)
            if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,10))
                return true;

        if(tipo==stageClearClose || tipo==victoryClose)
            if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,5))
                return true;
                           
        return false;         
    }

};
#endif