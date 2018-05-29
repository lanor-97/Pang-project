#ifndef POWERUP_H
#define POWERUP_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "stdlib.h"
#include "time.h"

enum powerUpTipo  { BOLLA = 0, ALTRO };

class PowerUp  {
public:
    PowerUp()  { srand(time(0)); }
    ~PowerUp()  { if(bitmap) al_destroy_bitmap(bitmap); }
    int getX() const  { return posX; }
    int getY() const  { return posY; }
    int getDimX() const  { return dimX; }
    int getDimY() const  { return dimY; }

    void Spawn(int, int);
    void Draw()  { if(bitmap) al_draw_bitmap(bitmap, posX, posY, 0); }
private:
    int posX=0, posY=0;
    int dimX=0, dimY=0;
    int numTotale = 2;
    powerUpTipo tipo = BOLLA;
    ALLEGRO_BITMAP* bitmap=NULL;
};


#endif