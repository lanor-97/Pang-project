#include "headers/Giocatore.h"

Giocatore::Giocatore(int f)  {
	dimX = 60;
	dimY = 70;
    frames=f;
	posX = 0;
	posY = 0;
	bitmap = al_load_bitmap("../images/shrekFermoSinistra.png");
	arma = new Arma(15, 0, 0);
    animazione.setFrameCount(0);
    animazione.setFrameDelay(5);
    animazione.setCurrFrame(0);
    bubble = false;
    bubble_bitmap = al_load_bitmap("../images/bolla.png");
}

Giocatore::~Giocatore()  {
    if(bitmap)  {
        al_destroy_bitmap(bitmap); 
    }
    if(bubble_bitmap)  {
        al_destroy_bitmap(bubble_bitmap);
    }
    delete arma;
}

void Giocatore::setDraw(bool keyLeft, bool keyRight, bool drawShoot, bool toLeft, bool caduto,bool climbing, bool keyUpDown)  {
    left = keyLeft;
    right = keyRight;
    this->drawShoot = drawShoot;
    this->toLeft = toLeft;
    this->caduto = caduto;
    this->climbing = climbing;
    this->keyUpDown= keyUpDown;
}

bool Giocatore::Draw(){
    if(bubble)
        al_draw_bitmap(bubble_bitmap,posX,posY,0);
        
    if(climbing)  {
        if(!keyUpDown)
            setFrames(1);
        else
            setFrames(5);
        animazione.setFrameDelay(7);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekClimbing.png");
        return animazione.eseguiFrame(bitmap, dimX, dimY,posX,posY, false,frames);
    }
    else if(left && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekSinistra.png");
    }

    else if(right && !drawShoot && !caduto)  {
        setFrames(6);
        animazione.setFrameDelay(5);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekDestra.png");
    }
    else if(drawShoot && toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekHookSinistra.png");
    }
    else if(drawShoot && !toLeft && !caduto)  {
        animazione.setFrameDelay(7);
        setFrames(3);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekHookDestra.png");
    }
    else if(caduto && toLeft)  {
        setFrames(11);
        animazione.setFrameDelay(7);
        al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekColpitoSinistra.png");
    }
    else if(caduto && !toLeft)  {
        setFrames(11);
		animazione.setFrameDelay(7);
		al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekColpitoDestra.png");
    }
    else if(!drawShoot && toLeft && !caduto)  {
    	al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekFermoSinistra.png");
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
    else if(!drawShoot && !caduto)  {
    	al_destroy_bitmap(bitmap);
        bitmap = al_load_bitmap("../images/shrekFermoDestra.png");
        al_draw_bitmap(bitmap,posX,posY,0);
        return true;
    }
    return animazione.eseguiFrame(bitmap, dimX, dimY,posX,posY, false,frames);
}

void Giocatore::DrawVictory()  {
  setFrames(6);
  animazione.setFrameDelay(7);
  bitmap = al_load_bitmap("../images/shrekVictory.png");
  animazione.eseguiFrame(bitmap, dimX, dimY,posX,posY, false,frames);
}

void Giocatore::muoviSx(bool sx, float max)  {
	if(sx)  {
		if(posX - 5 >= max)
			posX -= 5;
		else
			posX = max;
	}
	else  {
		if(posX + dimX + 5 <= max)
			posX += 5;
		else
			posX = max - dimX;
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