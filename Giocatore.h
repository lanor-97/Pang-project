#ifndef GIOCATORE_H
#define GIOCATORE_H
#include "Animation.h"
#include "Arma.h"

class Giocatore  {
private:
  	int 	dim_x,
            dim_y,
			posX,
			posY,
            frames;
    bool    left, 
            right,
            drawShoot, 
            toLeft, 
            caduto, 
            climbing;    //per la funzione draw
  	ALLEGRO_BITMAP *bitmap;
    Animation animazione;
   	Arma* arma;

public:
   	Giocatore(int);
  	~Giocatore();

  	int getX() const  { return posX; }
  	int getY() const  { return posY; }
  	int getX_arma() const  { return arma->getX(); }
  	int getY_arma() const  { return arma->getY(); }
  	int getDim_x() const  { return dim_x; }
   	int getDim_y() const  { return dim_y; }
   	int getDim_arma() const  { return arma->getDim(); }
  	
  	void setX(int x)  { posX=x; }
  	void setY(int y)  { posY=y; }
  	void setX_arma(int x)  { arma->setX(x); }
  	void setY_arma(int y)  { arma->setY(y); }
  	void setFrames(int f) {frames=f;}
    void setDraw(bool, bool, bool, bool, bool, bool);

   	bool Draw();
    void DrawVictory();
    void Draw_arma(int H)  { arma->Draw(H); }

   	void posizionaArma()  { arma->setX(posX); arma->setY(posY+dim_y+2); }
	void muoviSx(bool, float);
    void muoviUp(bool, float);

};

Giocatore::Giocatore(int f)  {
	dim_x = 60;
	dim_y = 70;
    frames=f;
	posX = 0;
	posY = 0;
	bitmap = al_load_bitmap("images/shrekFermoSinistra.png");
	arma = new Arma(12, 0, 0);
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
}

Giocatore::~Giocatore()  {
    if(bitmap)  {
        cerr << "\ndistruggo giocatore_bitmap";
        al_destroy_bitmap(bitmap); 
    }

    cerr << "\ndeleto arma";delete arma;
}

void Giocatore::setDraw(bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto,bool climbing)  {

    left = keyLeft;
    right = keyRight;
    this->drawShoot = drawShoot;
    this->toLeft = toLeft;
    this->caduto = caduto;
    this->climbing = climbing;


}
bool Giocatore::Draw(){

    if(climbing)  {
        setFrames(5);
        animazione.setFrameDelay(7);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekClimbing.png");
        return animazione.eseguiFrame(bitmap, dim_x, dim_y,posX,posY, false,frames);
    }
    else if(left && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekSinistra.png");
    }

    else if(right && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekDestra.png");
    }
    else if(drawShoot && toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekHookSinistra.png");
    }
    else if(drawShoot && !toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekHookDestra.png");
    }
    else if(caduto && toLeft)  {
        setFrames(11);
        animazione.setFrameDelay(7);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekColpitoSinistra.png");
    }
    else if(caduto && !toLeft)  {
        setFrames(11);
		animazione.setFrameDelay(7);
		al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekColpitoDestra.png");
    }
    else if(!drawShoot && toLeft && !caduto)  {
    	al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekFermoSinistra.png");
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
    else if(!drawShoot && !caduto)  {
    	al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("images/shrekFermoDestra.png");
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
  
    return animazione.eseguiFrame(bitmap, dim_x, dim_y,posX,posY, false,frames);
}

void Giocatore::DrawVictory()  {
  setFrames(6);
  animazione.setFrameDelay(7);
  bitmap = al_load_bitmap("images/shrekVictory.png");
  animazione.eseguiFrame(bitmap, dim_x, dim_y,posX,posY, false,frames);
}

void Giocatore::muoviSx(bool sx, float max)  {
	if(sx)  {
		if(posX - 5 >= max)
			posX -= 5;
		else
			posX = max;
	}
	else  {
		if(posX + dim_x + 5 <= max)
			posX += 5;
		else
			posX = max - dim_x;
	}
}

void Giocatore::muoviUp(bool up, float max)  {
	if(up)  {
		if(posY - 3 < max)
			posY = max;
		else
			posY -= 3;
	}
	else  {
		if(posY + 3 > max)
			posY = max;
		else
			posY += 3;
	}
}


#endif
