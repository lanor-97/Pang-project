#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Animation.h"
#include "Arma.h"

class Giocatore  {
private:
  	int 	dimX,
            dimY,
			posX,
			posY,
            frames,
			immuneTime = 0;
    bool    left, 
            right,
            drawShoot, 
            toLeft, 
            caduto, 
            climbing,
            keyUpDown,  //per la funzione draw
			bubble;
  	ALLEGRO_BITMAP *bitmap;
	ALLEGRO_BITMAP *bubble_bitmap;
    Animation animazione;
   	Arma* arma;

public:
   	Giocatore(int);
  	~Giocatore();

  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getArmaX() const  { return arma->getX(); }
  	int getArmaY() const  { return arma->getY(); }
  	int getDimX() const  { return dimX; }
   	int getDimY() const  { return dimY; }
   	int getArmaDim() const  { return arma->getDim(); }
  	
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setArmaX(int x)  { arma->setX(x); }
  	void setArmaY(int y)  { arma->setY(y); }
	void setImmuneTime(int t)  { immuneTime = t; }
  	void setFrames(int f) {frames=f;}
    void setDraw(bool, bool, bool, bool, bool, bool,bool);

   	bool Draw();
    void DrawVictory();
    void ArmaDraw(int H)  { arma->Draw(H); }

	void decreaseImmune()  { immuneTime--; }
	bool Immune() const  { return immuneTime > 0; }
	bool Bubble() const  { return bubble; }
	void activeBubble()  { bubble = true; }
	void removeBubble()  { bubble = false; }
   	void posizionaArma()  { arma->setX(posX); arma->setY(posY+dimY+2); }
	void muoviSx(bool, float);
    void muoviUp(bool, float);

};


#endif
