#ifndef LIVELLO3_H
#define LIVELLO3_H

#include "Livello2.h"
#include "Farquaad.h"

class Livello3: public Livello1  {
public:
	Livello3()  { Livello1(); }
	Livello3(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	Livello3(Livello1*, const int);
	virtual ~Livello3();
	virtual void regolaPalle();
	virtual CASO Esegui(int, int&, float[]);
	virtual void Draw(int, int, int, int);

protected:
	bool drawExplosion2 = false;
	GestorePalle* GP2 = NULL;
	Scala* scala1 = NULL;
	Scala* scala2 = NULL;
	Piattaforma* piat = NULL;
	const int PLAYER_ALT_PIAT = 105;
	const int PLAYER_ALT_NORM = 285;
	Farquaad* farquaad= NULL;
};


#endif