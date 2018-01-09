#ifndef GESTOREPALLE_H
#define GESTOREPALLE_H

#include "Palla.h"
#include "list"

class GestorePalle  {
private:
	list<Palla> balls;
	float	SW,
			SY;

public:
	~GestorePalle();
	void aggiungiPalla(float, float, SIZE);
	void rimuoviPalla(list<Palla>::iterator it)  { balls.erase(it); }
	const Palla& front() const  { return balls.front(); }
	void Draw() const;
	void setSW(float sw)  { SW = sw; }
	void setSY(float sy)  { SY = sy; }
	void Bouncer();
	bool Hit(float, float, float);
};

GestorePalle::~GestorePalle()  {
	for(list<Palla>::iterator it = balls.begin(); it != balls.end(); it++)  {
		it->destroyBitmap();
	}
}

void GestorePalle::aggiungiPalla(float x, float c, SIZE s)  {
	Palla p(x, c, s);
	balls.push_back(p);
}

void GestorePalle::Draw() const  {
	for(list<Palla>::const_iterator it = balls.begin(); it != balls.end(); it++)  {
		it->Draw();
	}
}

void GestorePalle::Bouncer()  {
	for(list<Palla>::iterator it = balls.begin(); it != balls.end(); it++)  {
		if(it->getX() < 0 || it->getX() > SW - it->getDim()) {
			it->setBouncer(-it->getBouncer());
		}
		it->setX(it->getX() + it->getBouncer());
		it->setY(it->calculateY(SY));
	}
}
	
bool GestorePalle::Hit(float x1, float y1, float d1)  {
	for(list<Palla>::iterator it = balls.begin(); it != balls.end(); it++)  {
		bool	b1 = x1 <= it->getX()+it->getDim(),
				b2 = x1+d1 >= it->getX(),
				b3 = y1 <= it->getY()+it->getDim();
		
		if(b1 && b2 && b3)  {
			float x = it->getX(), c = it->getCont();
			SIZE s;
			switch(it->getSize())  {
				case GRA:	s = MED;
				break;
				
				case MED: 	s = PIC;
				break;
				
				case PIC:	it->destroyBitmap();
								balls.erase(it);
								return true;
			}
			Palla p1(x, c, s), p2(x, c, s);
			p2.setBouncer(-p1.getBouncer());
			balls.push_back(p1);
			balls.push_back(p2);
			it->destroyBitmap();
			balls.erase(it);
			return true;
		}
	}
	return false;
}


#endif
