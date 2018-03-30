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
	void Bouncer();
	bool hitByHook(Giocatore*);
	bool playerHit(Giocatore*);
	bool Empty() const  { return balls.empty(); }
	void Clear();
	void clearProcess();
	void bouncerPiattaforma(Piattaforma*);
	void bouncerBlocco(Blocco*);
};

GestorePalle::~GestorePalle()  {
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		cerr << "deleto palla_x";
		delete (*it);
	}
}

bool GestorePalle::aggiungiPalla(float x, float c, SIZE s, COLOR co, bool dir)  {
	Palla* p = new Palla(x, c, s, co, dir);

	p->calculateY(SY);
	balls.push_back(p);
	return true;
}

bool GestorePalle::Draw(bool drawExplosion)   {
	for(list<Palla*>::const_iterator it = balls.begin(); it != balls.end(); it++)  {
		(*it)->Draw();
	}
	
	if(drawExplosion)
		if(!explosion.Draw())
			return false;
	return true;
}

void GestorePalle::Bouncer()  {
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		if((*it)->getX() < 0 || (*it)->getX() > SW - (*it)->getDim())
			(*it)->toggleBouncerX();

		if(!(*it)->getProcessatoX())	(*it)->calculateX();
		if(!(*it)->getProcessatoY()) 	(*it)->calculateY(SY);
	}
	clearProcess();
}
	
bool GestorePalle::hitByHook(Giocatore* player)  {
	float 	x1 = player->getX_arma(), 
			y1 = player->getY_arma(),
			d1 = player->getDim_arma();

	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		bool	b1 = x1 <= (*it)->getX()+(*it)->getDim(),
				b2 = x1+d1 >= (*it)->getX(),
				b3 = y1 <= (*it)->getY()+(*it)->getDim();
		
		if(b1 && b2 && b3)  {
			float x = (*it)->getX(), c = (*it)->getCont();
			explosion.setTipo((*it)->getSize());
			explosion.setPosX((*it)->getX());
			explosion.setPosY((*it)->getY());
			COLOR co = (*it)->getColor();
			cerr << co;
			SIZE s;
			switch((*it)->getSize())  {
				case GRA:	s = MED;
				break;
				
				case MED: 	s = PIC;
				break;
				
				case PIC:	balls.erase(it);
							delete (*it);
							return true;
			}
			Palla* p1 = new Palla(x, c, s, co, true);
			Palla* p2 = new Palla(x, c, s, co, false);
			p1->setY((*it)->getY());
			p2->setY((*it)->getY());

			//p2->toggleBouncerX();
			if(p1->getCont() > 157 || p1->getCont() < -157)
				p1->setBouncerY(-p1->getBouncerY());
			if(p2->getCont() > 157 || p2->getCont() < -157)
				p2->setBouncerY(-p2->getBouncerY());
			balls.push_back(p1);
			balls.push_back(p2);
			balls.erase(it);
			cerr << "\ndeleto palla_x";
			delete (*it);
			return true;
		}
	}
	return false;
}


bool GestorePalle::playerHit(Giocatore* player)  {
	float 	x = player->getX(),
			y = player->getY(),
			d = player->getDim_x();

	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		bool	b1 = (*it)->getX()+(*it)->getDim() >= x,
				b2 = (*it)->getX() <= x+d,
				b3 = y <= (*it)->getY()+ (*it)->getDim();
		
		if(b1 && b2 && b3)
			return true;
	}
	return false;
}

void GestorePalle::Clear()  {
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		cerr << "\ndeleto palla_x";
		delete (*it);
	}
	balls.clear();
}

void GestorePalle::clearProcess()  {
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)
		(*it)->clearProcess();
}

void GestorePalle::bouncerPiattaforma(Piattaforma* p)  {
	float	piatX = p->getX(),
			piatY = p->getY(),
			piatDimX = p->getDim_x(),
			piatDimY = p->getDim_y();

	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		float	pallaX = (*it)->getX(),
				pallaY = (*it)->getY(),
				pallaDim = (*it)->getDim(),
				pallaBouncerX = (*it)->getBouncerX(),
				pallaBouncerY = (*it)->getBouncerY();

		DIREZIONE 	d = (*it)->getDirezioneY();
		bool 	altezzaOk = !(pallaY>piatY+piatDimY) && !(pallaY+pallaDim<piatY),
				lunghezzaOk = !(pallaX>piatX+piatDimX) && !(pallaX+pallaDim<piatX);

		bool 	versoDx = (pallaBouncerX > 0) && (pallaX+pallaDim >= piatX) && (pallaX+pallaDim-piatX <= 4),
				versoSx = (pallaBouncerX < 0) && (piatX+piatDimX <= pallaX) && (pallaX-piatX-piatDimX <= 4);

		if((versoDx || versoSx) && altezzaOk)
			(*it)->toggleBouncerX();

		bool 	versoUp = (d == UP) && (piatY+piatDimY >= pallaY) && (piatY+piatDimY-pallaY <= 7),
				versoDown = (d == DOWN) && (pallaY+pallaDim >= piatY) && (pallaY+pallaDim-piatY <= 7);

		if((*it)->canY > 0)  {
			(*it)->canY -= 1;
			continue;
		}
		if((versoUp || versoDown) && lunghezzaOk)  {
			(*it)->setBouncerY(-pallaBouncerY);
			(*it)->calculateY(SY);
			(*it)->canY = 2;
		}
	}
}

void GestorePalle::bouncerBlocco(Blocco* b)  {
	float	bloccoX = b->getX(),
			bloccoY = b->getY(),
			bloccoDimX = b->getDim_x(),
			bloccoDimY = b->getDim_y();

	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		float	pallaX = (*it)->getX(),
				pallaY = (*it)->getY(),
				pallaDim = (*it)->getDim(),
				pallaBouncerX = (*it)->getBouncerX(),
				pallaBouncerY = (*it)->getBouncerY();

		DIREZIONE 	d = (*it)->getDirezioneY();
		bool 	altezzaOk = !(pallaY>bloccoY+bloccoDimY) && !(pallaY+pallaDim<bloccoY),
				lunghezzaOk = !(pallaX>bloccoX+bloccoDimX) && !(pallaX+pallaDim<bloccoX);

		bool 	versoDx = (pallaBouncerX > 0) && (pallaX+pallaDim >= bloccoX) && (pallaX+pallaDim-bloccoX <= 4),
				versoSx = (pallaBouncerX < 0) && (bloccoX+bloccoDimX <= pallaX) && (pallaX-bloccoX-bloccoDimX <= 4);

		if((versoDx || versoSx) && altezzaOk)
			(*it)->toggleBouncerX();

		bool 	versoUp = (d == UP) && (bloccoY+bloccoDimY >= pallaY) && (bloccoY+bloccoDimY-pallaY <= 7),
				versoDown = (d == DOWN) && (pallaY+pallaDim >= bloccoY) && (pallaY+pallaDim-bloccoY <= 7);

		if((*it)->canY > 0)  {
			(*it)->canY -= 1;
			continue;
		}
		if((versoUp || versoDown) && lunghezzaOk)  {
			(*it)->setBouncerY(-pallaBouncerY);
			(*it)->calculateY(SY);
			(*it)->canY = 5;
		}
	}
}


#endif