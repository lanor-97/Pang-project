#ifndef LIVELLO2_H
#define LIVELLO2_H

#include "Livello1.h"
#include "Scala.h"
#include "Drago.h"

class Livello2: public Livello1  {
public:
	Livello2()  { Livello1(); }
	Livello2(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	Livello2(Livello1*, const int);
	virtual ~Livello2();
	virtual void regolaPalle();
	virtual CASO Esegui(int, int&, float[]);
	virtual void Draw(int, int, int, int);

protected:
	Scala *scala1=NULL, *scala2=NULL;
	Piattaforma *piat1=NULL, *piat2=NULL;
	Blocco *blocco1=NULL, *blocco2=NULL, *blocco3=NULL;
	Drago *drago;
	const int PLAYER_ALT_PIAT = 148;
	const int PLAYER_ALT_NORM = 285;
};


#endif