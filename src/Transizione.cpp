#include "headers/Transizione.h"

Transizione::Transizione() {
    dimX=640;
    dimY=480;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(0);
    animazione.setCurrFrame(0);
    transition = NULL;
}

Transizione::Transizione(Tipe tipo)  {
    dimX=640;
    dimY=480;
    animazione.setFrameCount(0);
    animazione.setFrameDelay(0);
    animazione.setCurrFrame(0);
    this->tipo=tipo;
    if(tipo==menuClose)
        transition=al_load_bitmap("../images/menuTransition.png");
    else if(tipo==levelStart)
        transition=al_load_bitmap("../images/levelStart.png");
    else if(tipo==stageClear)
        transition=al_load_bitmap("../images/stageClear.png");
    else if(tipo==stageClearClose)
        transition=al_load_bitmap("../images/stageClearClose.png");
    else if(tipo==victory)
        transition=al_load_bitmap("../images/victory.png");
    else if(tipo==victoryClose)
        transition=al_load_bitmap("../images/victoryClose.png");
    else
        transition=NULL;
}

Transizione::~Transizione()  {
    if(transition)  {  
        al_destroy_bitmap(transition);
    }
}

void Transizione::setTipo(int t)  {
    if(transition)  al_destroy_bitmap(transition);

    switch(t)  {
        case 0:        
            tipo=menuClose;
            transition=al_load_bitmap("../images/menuTransition.png");
        break;

        case 1:
            tipo=levelStart;
            transition=al_load_bitmap("../images/levelStart.png");
        break;
        
        case 2:
            tipo=stageClear;
            transition=al_load_bitmap("../images/stageClear.png");
        break;

        case 3:
            tipo=stageClearClose;
            transition=al_load_bitmap("../images/stageClearClose.png");
        break;

        case 4:
            tipo=victory;
            transition=al_load_bitmap("../images/victory.png");
        break;

        case 5:
            tipo=victoryClose;
            transition=al_load_bitmap("../images/victoryClose.png");
        break;

        default:
            transition = NULL;
    }
}

bool Transizione::Draw()  {
    if(tipo==menuClose || tipo==levelStart)  {
        if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,15))
            return true;   
    }
    else if(tipo==stageClear || tipo==victory)  {
        if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,10))
            return true;
    }
    else if(tipo==stageClearClose || tipo==victoryClose)  {
        if(animazione.eseguiFrame(transition,dimX,dimY,0,0,false,5))
            return true;
    }
                           
    return false;         
}