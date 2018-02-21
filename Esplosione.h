#ifndef ESPLOSIONE_H
#define ESPLOSIONE_H
#include "Animation.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <iostream>
using namespace std;

class Esplosione{
    private:
    ALLEGRO_BITMAP *explosion;
    Animation animazione;
    int posX;
    int posY;
    int size;

    public:
    Esplosione():posX(0),posY(0),size(0){}
    Esplosione(int x,int y,int size)
    {
        posX=x;
        posY=y;
        this->size=size;
        animazione.setFrameCount(0);
        animazione.setFrameDelay(8);
        animazione.setCurrFrame(0);
    }
	~Esplosione()  { al_destroy_bitmap(explosion);}
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getSize(){return size;}
    ALLEGRO_BITMAP *getExplosion() const{return explosion;}

    void setPosX(int x){posX=x;}
    void setPosY(int y){posY=y;}
    void setExplosion(ALLEGRO_BITMAP *bitmap){explosion=bitmap;}
    void setSize(int size){this->size=size;}
    bool Draw()
    {
        bool pic=false;
        if(size==2)
        {
            setSize(70);
            setExplosion(al_load_bitmap("images/esplosioneGra.png"));
        }    
        else if(size==1)
        {   
            setSize(40);
            setExplosion(al_load_bitmap("images/esplosioneMed.png"));
        }
        else if(size==0)
       {    
           setSize(20);
           pic=true;
        setExplosion(al_load_bitmap("images/esplosionePic.png"));
       }
       
       if(pic)
        {
                if(animazione.eseguiFrame(explosion,getSize(),getSize(),getPosX(),getPosY(), false,5))
                    return true;
        }            
       else
            if(animazione.eseguiFrame(explosion,getSize(),getSize(),getPosX(),getPosY(), false,4))
                    return true;
       return false;         

    }

};


#endif