#ifndef GIOCATORE_H
#define GIOCATORE_H
#include "Animation.h"
#include "Arma.h"

class Giocatore  {
private:
  	int 	dim_x,
			dim_y,
			posX,
			posY;
  	ALLEGRO_BITMAP *bitmap;
    Animation animazione;
   	int frames;
   	Arma* arma;

public:
   	Giocatore(int, int,int);
  	~Giocatore()  { al_destroy_bitmap(bitmap); delete arma; }
  	ALLEGRO_BITMAP* getBitmap() const  { return bitmap; }
  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getX_arma() const  { return arma->getX(); }
  	int getY_arma() const  { return arma->getY(); }
  	int getDim_x() const  { return dim_x; }
   	int getDim_y() const  { return dim_y; }
   	int getDim_arma() const  { return arma->getDim(); }
   	int getFrames() const {return frames;}
  	void setBitmap(ALLEGRO_BITMAP *b_map)  { bitmap=b_map; }
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setX_arma(int x)  { arma->setX(x); }
  	void setY_arma(int y)  { arma->setY(y); }
  	void setDim_x(int d)  { dim_x=d; }
   	void setDim_y(int d)  { dim_y=d; }
   	void setFrames(int f) {frames=f;}
   	bool Draw( bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto, bool climbing);
    void DrawVictory();
   	void posizionaArma()  { arma->setX(posX); arma->setY(posY+dim_y+2); }
    void Draw_arma(int H)  { arma->Draw(H); }

};

Giocatore::Giocatore(int dx, int dy, int f)  {
	dim_x = dx;
	dim_y = dy;
  	frames=f;
	posX = 0;
	posY = 0;
	bitmap = al_load_bitmap("images/shrekFermoSinistra.png");
	arma = new Arma(12, 0, 0);
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

bool Giocatore:: Draw( bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto,bool climbing){
    if(climbing)  {
        setFrames(6);
        animazione.setFrameDelay(7);
        setBitmap(al_load_bitmap("images/shrekClimbing.png"));
    }
    if(keyLeft && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        setBitmap(al_load_bitmap("images/shrekSinistra.png"));
    }

    else if(keyRight && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        setBitmap(al_load_bitmap("images/shrekDestra.png"));
    }
    else if(drawShoot && toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        setBitmap(al_load_bitmap("images/shrekHookSinistra.png"));
    }
    else if(drawShoot && !toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        setBitmap(al_load_bitmap("images/shrekHookDestra.png"));
    }
    else if(caduto && toLeft)  {
        setFrames(11);
        animazione.setFrameDelay(7);
        setBitmap(al_load_bitmap("images/shrekColpitoSinistra.png"));
    }
    else if(caduto && !toLeft)  {
        setFrames(11);
		animazione.setFrameDelay(7);
        setBitmap(al_load_bitmap("images/shrekColpitoDestra.png"));
    }
    else if(!drawShoot && toLeft && !caduto)  {
        setBitmap(al_load_bitmap("images/shrekFermoSinistra.png"));
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
    else if(!drawShoot && !caduto)  {
        setBitmap(al_load_bitmap("images/shrekFermoDestra.png"));
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
  
    return animazione.eseguiFrame(bitmap,getDim_x(),getDim_y(),getX(),getY(), false,getFrames());
}

void Giocatore::DrawVictory()  {
  setFrames(6);
  animazione.setFrameDelay(7);
  setBitmap(al_load_bitmap("images/shrekVictory.png"));
  animazione.eseguiFrame(bitmap,getDim_x(),getDim_y(),getX(),getY(), true,getFrames());
}


#endif
