#ifndef GESTOREPALLE_H
#define GESTOREPALLE_H

#include "Palla.h"
#include "list"
#include "Esplosione.h"
#include "Giocatore.h"
#include "Piattaforma.h"
#include "Blocco.h"

class GestorePalle  {
private:
	list<Palla*> balls;
	float	SW,
			SY;

	Esplosione explosion;
public:
	GestorePalle()  {}
	GestorePalle(float x, float y)  { SW = x; SY = y; }
	~GestorePalle();

	bool aggiungiPalla(float, float, SIZE, COLOR, bool);
	bool Draw(bool) ;
	void setSW(float sw)  { SW = sw; }
	void setSY(float sy)  { SY = sy; }
	
	bool hitByHook(Giocatore*, int&);
	bool playerHit(Giocatore*, bool);
	bool Empty() const  { return balls.empty(); }

	void Clear();
	void clearProcess();

	void Bouncer();
	void bouncerPiattaforma(Piattaforma*);
	void bouncerBlocco(Blocco*);
};


#endif