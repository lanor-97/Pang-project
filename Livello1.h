#ifndef LIVELLO1_H
#define LIVELLO1_H

#include "GestorePalle.h"
#include "Sfondo.h"
#include "Giocatore.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Vita.h"

class Livello1  {
public:
	Livello1(float, float, Giocatore);
	bool Esegui();
	void Draw();

protected:
	Sfondo sfondo;
	Giocatore player;
	GestorePalle GP;
	float SCREEN_W, SCREEN_H;
};


Livello1::Livello1(float SW, float SH, Giocatore p): sfondo(0), player(p), SCREEN_W(SW), SCREEN_H(SH)  {
	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);

	GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);
}

bool Livello1::Esegui()  {
}



#endif