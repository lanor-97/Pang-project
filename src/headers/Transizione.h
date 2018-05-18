#ifndef TRANSIZIONE_H
#define TRANSIZIONE_H
#include "Animation.h"
#include <iostream>
using namespace std;

enum Tipe {menuClose=0, levelStart, stageClear, stageClearClose, victory, victoryClose};
class Transizione  {
private:
    int dimX,
        dimY;
    ALLEGRO_BITMAP* transition;
    Animation animazione;
    Tipe tipo;

public:
    Transizione();
    Transizione(Tipe);
    ~Transizione();

    int getDimX() const  { return dimX; }
    void setDimX(int n) { dimX = n; }

    int getDimY() const  { return dimY; }
    void setDimY(int n)  { dimY = n; }

    ALLEGRO_BITMAP* getTransition()  { return transition; }
    void setTransition(ALLEGRO_BITMAP* T)  { transition = T; }
    
    Tipe getTipo() const  { return tipo; }
    void setTipo(int);

    bool Draw();
};



#endif

