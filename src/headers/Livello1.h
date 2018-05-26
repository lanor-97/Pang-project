#ifndef LIVELLO1_H
#define LIVELLO1_H

#include "Animation.h"
#include "GestorePalle.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Music.h"
#include "SoundEffect.h"
#include "Transizione.h"
#include "Blocco.h"
#include "PowerUp.h"

enum CASO  { EXIT = 0, LIVELLOSUP, VITAPERSA, MENU };

class Livello1  {
public:
	Livello1();
	Livello1(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	virtual ~Livello1();
	virtual CASO Esegui(int, int&, float[]);
	void Transition(int);
	bool Pausa(bool&, float[]);
	virtual void regolaPalle();
	virtual void Draw(int, int, int, int);
	void  toggleFullscreen(bool&, float[]);

	//funzioni get
	float getSW() const  { return SCREEN_W; }
	float getSH() const  { return SCREEN_H; }
	Giocatore* getPlayer() const  { return player; }
	ALLEGRO_DISPLAY* getDisplay() const  { return display; }
protected:
	ALLEGRO_BITMAP* 		sfondo=NULL;
	ALLEGRO_EVENT_QUEUE* 	event_queue=NULL;
	ALLEGRO_TIMER*			timer=NULL;
	ALLEGRO_FONT*			font1=NULL;
	ALLEGRO_FONT*			font2=NULL;
	ALLEGRO_BITMAP*			vite_bmp=NULL;
	ALLEGRO_DISPLAY* 		display=NULL;
	ALLEGRO_BITMAP*			pausa_play=NULL;
	ALLEGRO_BITMAP*			pausa_exit=NULL;
	ALLEGRO_TRANSFORM 		redimencionamento;
	Music* musica;
	Giocatore* player = NULL;
	GestorePalle* GP = NULL;
	Transizione transizione;
	float SCREEN_W, SCREEN_H;
	bool shoot, caduto, drawShoot, drawExplosion, MatchOver;
	PowerUp* powerup;
};


#endif