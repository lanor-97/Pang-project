#ifndef POWERUP_H
#define POWERUP_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "stdlib.h"
#include "time.h"
#include "Giocatore.h"

enum powerUpTipo  { BOLLA = 0, FREEZE = 1 };

class PowerUp  {
public:
    PowerUp()  { srand(time(0)); }
    ~PowerUp()  {}

    int getX() const  { return posX; }
    int getY() const  { return posY; }
    int getDimX() const  { return dimX; }
    int getDimY() const  { return dimY; }

    void Destroy()  { spawned = false; }
    bool Spawned()  const  { return spawned; }
    void Fall()  { posY += 3; }
    bool notArrivedTerrain(int y)  { return posY+dimY <= y; }
    void playerTookIt(Giocatore*);
    bool canSpawn()  { int x = rand()%100; return !spawned && x < 50; }
    void Spawn(int, int);
    void Draw()  { if(bitmap) al_draw_bitmap(bitmap, posX, posY, 0); }

private:
    int posX=0, posY=0;
    int dimX=30, dimY=30;
    int numTotale = 2;
    bool spawned = false;
    powerUpTipo tipo = BOLLA;
    ALLEGRO_BITMAP* bitmap=NULL;
};


#endif