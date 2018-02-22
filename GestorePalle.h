#ifndef GESTOREPALLE_H
#define GESTOREPALLE_H
#include "Palla.h"
#include "list"
#include "Esplosione.h"
class GestorePalle  {
private:
	list<Palla*> balls;
	float	SW,
			SY;
	Esplosione explosion;
public:
	~GestorePalle();
	bool aggiungiPalla(float, float, SIZE);
	//void rimuoviPalla(list<Palla>::iterator it)  { balls.erase(it); }
	//const Palla& front() const  { return balls.front(); }
	bool Draw(bool) ;
	void setSW(float sw)  { SW = sw; }
	void setSY(float sy)  { SY = sy; }
	void Bouncer();
	bool hitByHook(float, float, float, bool&);
	bool playerHit(float, float, float);
	bool Empty() const  { return balls.empty(); }
	void Clear();
};

GestorePalle::~GestorePalle()  {
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		delete (*it);
	}	
}

bool GestorePalle::aggiungiPalla(float x, float c, SIZE s)  {
	Palla* p = new Palla(x, c, s);
	if(!p->getBitmap())
		return false;
	float y = p->calculateY(SY);
	p->setY(y);
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
		if((*it)->getX() < 0 || (*it)->getX() > SW - (*it)->getDim()) {
			(*it)->setBouncer(-(*it)->getBouncer());
		}
		(*it)->setX((*it)->getX() + (*it)->getBouncer());
		(*it)->setY((*it)->calculateY(SY));
	}
}
	
bool GestorePalle::hitByHook(float x1, float y1, float d1, bool& b)  {

	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)  {
		bool	b1 = x1 <= (*it)->getX()+(*it)->getDim(),
				b2 = x1+d1 >= (*it)->getX(),
				b3 = y1 <= (*it)->getY()+(*it)->getDim();
		
		if(b1 && b2 && b3)  {
			float x = (*it)->getX(), c = (*it)->getCont();
			explosion.setTipo((*it)->getSize());
			explosion.setPosX((*it)->getX());
			explosion.setPosY((*it)->getY());
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
			Palla* p1 = new Palla(x, c, s);
			Palla* p2 = new Palla(x, c, s);

			p2->setBouncer(-(p1->getBouncer()));
			balls.push_back(p1);
			balls.push_back(p2);
			balls.erase(it);
			delete (*it);
			return true;
		}
	}
	return false;
}


bool GestorePalle::playerHit(float x, float y, float d)  {
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
	for(list<Palla*>::iterator it = balls.begin(); it != balls.end(); it++)
		(*it)->destroyBitmap();
	balls.clear();
}


#endif