#ifndef LIVELLO2_H
#define LIVELLO2_H

#include "Livello1.h"
#include "Scala.h"
#include "Piattaforma.h"
#include "Drago.h"

class Livello2: public Livello1  {
public:
	Livello2()  { Livello1(); }
	Livello2(float, float, Giocatore*, ALLEGRO_DISPLAY*, const int);
	Livello2(Livello1*, const int);
	virtual ~Livello2();
	virtual void regolaPalle();
	virtual int Esegui(int, float[]);

protected:

	Scala *scala1, *scala2;
	Piattaforma *piat1, *piat2;
	Blocco *blocco1, *blocco2, *blocco3;
	Drago *drago;
};


Livello2::Livello2(float SW, float SH, Giocatore* p, ALLEGRO_DISPLAY* d1, const int FPS)  {
	Livello1(SW, SH, p, d1, FPS);
}

Livello2::Livello2(Livello1* L1, const int FPS)  {
	sfondo = al_load_bitmap("images/sfondo2.jpg");
	player = L1->getPlayer();
	SCREEN_W = L1->getSW();
	SCREEN_H = L1->getSH();

	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);

	font1=al_load_ttf_font("fonts/SHREK.TTF",30,0);
	font2=al_load_ttf_font("fonts/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("images/vita.png");
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = L1->getDisplay();
	pausa_play = al_load_bitmap("images/pausa1.png");
	pausa_exit = al_load_bitmap("images/pausa2.png");

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//liv 2 stuff
	scala1 = new Scala(160, 218, 0);
	scala2 = new Scala(434, 218, 0);
	piat1 = new Piattaforma(136, 204);
	piat2 = new Piattaforma(410, 204);
	blocco1 = new Blocco(150, 100, bloccoPietra);
	blocco2 = new Blocco(292, 150, bloccoPietra);
	blocco3 = new Blocco(434, 100, bloccoPietra);
	drago= new Drago(120,120,640,220); // posDrago 530,220
}

Livello2::~Livello2()  {
	if(scala1)  {
		cerr << "\ndeleto scala1";
		delete scala1;
	}
	if(scala2)  {
		cerr << "\ndeleto scala2";
		delete scala2;
	}
	if(piat1)  {
		cerr << "\ndeleto piat1";
		delete piat1;
	}
	if(piat2)  {
		cerr << "\ndeleto piat2";
		delete piat2;
	}
	if(blocco1)  {
		cerr << "\ndeleto blocco1";
		delete blocco1;
	}
	if(blocco2)  {
		cerr << "\ndeleto blocco2";
		delete blocco2;
	}
	if(blocco3)  {
		cerr << "\ndeleto blocco3";
		delete blocco3;
	}
	if(drago)  	{
		cerr << "\ndeleto drago";
		delete drago;
	}
}

void Livello2::regolaPalle()  {
	/*GP.aggiungiPalla(SCREEN_W/2, 157, GRA, RED);
	GP.aggiungiPalla(0, 157, GRA, RED);*/
}

int Livello2::Esegui(int vite, float res_info[])  {
	//DICHIARAZIONE VARIABILI ALLEGRO
	ALLEGRO_TRANSFORM 		redimencionamento;

	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	drawShoot=false, caduto=false, shoot=false, colpito=false, sfondo2=false, 
			presa=false, redraw = true, keyRight=false, keyLeft=false, keySpace=false, 
			toLeft=false, MatchOver=false, bitmap_ = true, fullscreen=false, climbing=false,
			drawExplosion=false, trans=true, keyUp = false, keyDown = false, onlyLeftRight=false,
			dragonArrive=true, spitting=false, fire=false, colpitoFuoco=false;

	int 	punteggio=0, tempo=9000, H_arma=0, return_value, fireCount=300; //fireCount timer per spitFire 300=5 sec

	regolaPalle();
	al_flush_event_queue(event_queue);
	al_start_timer(timer);
	Transition(1);

	//IL GIOCO VERO E PROPRIO
	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			bool hit = false;
			GP.Bouncer();
			if(shoot)
				hit = GP.hitByHook(player->getX_arma(), player->getY_arma(), player->getDim_arma());

			if(shoot==false)
				player->posizionaArma();

			if(hit && !presa)  {	//rampino colpisce palla
				punteggio+=200;
				presa=true;
				drawExplosion=true;
			}

			if(!hit)
				presa=false;

			//285 = altitudine player normale
			//148 = altitudine player piattaforma (piat_pos_y+14-player_dim_y)
			onlyLeftRight =  (player->getY() == 285) || (player->getY() == 148);
			if(keyRight && !caduto && !drawShoot && onlyLeftRight)  {
				//player->setFrames(6);
				drawShoot=false;
				toLeft=false;
				if(player->getY() == 285)  {	
					if(player->getX()+player->getDim_x()+5 <= SCREEN_W)
						player->setX(player->getX()+5);
					else
						player->setX(SCREEN_W-player->getDim_x());
				}
				else  {									//sopra piattaforma
					if(player->getX() < SCREEN_W/2)  {	//piat1
						if(player->getX()+player->getDim_x()+5 <= piat1->getX()+piat1->getDim_x())
							player->setX(player->getX()+5);
						else
							player->setX(piat1->getX()+40);
					}
					else  {								//piat2
						if(player->getX()+player->getDim_x()+5 <= piat2->getX()+piat2->getDim_x())
							player->setX(player->getX()+5);
						else
							player->setX(piat2->getX()+40);
					}
				}
			}
			if(keyLeft && !caduto && !drawShoot && onlyLeftRight)  {
			//	player->setFrames(6);
				drawShoot=false;
				toLeft=true;
				if(player->getY() == 285)  {
					if(player->getX()-5 >= 0)
						player->setX(player->getX()-5);
					else
						player->setX(0);
				}
				else  {									//sopra piattaforma
					if(player->getX() < SCREEN_W/2)  {	//piat1
						if(player->getX()-5 >= piat1->getX())
							player->setX(player->getX()-5);
						else
							player->setX(piat1->getX());
					}
					else  {								//piat2
						if(player->getX()-5 >= piat2->getX())
							player->setX(player->getX()-5);
						else
							player->setX(piat2->getX());
					}
				}
			}
			if(keySpace && !caduto)  {
				if(!shoot)
					drawShoot=true;
				shoot=true;
				keySpace=false;
			}


			bool p_hit = GP.playerHit(player->getX(), player->getY(), player->getDim_x());

			if(p_hit && !colpito && !caduto)  {
				//palla colpisce player
				return_value = 0;
				caduto=true;
				colpito=true;
			}

			bool p_hitFire=drago->hitFire(player->getX(), player->getY(), player->getDim_x(), player->getDim_y());

			if(p_hitFire && !colpito && !caduto) 
			{
				caduto=true;  //fuoco colpisce player
				colpito=true;
			}
			if(!p_hitFire && !p_hit)
				colpito=false;
			

			if(keyUp && player->getY()+player->getDim_y() >= piat1->getY()+14 && (scala1->playerHere(player) || scala2->playerHere(player)))  {
				if(player->getY()+player->getDim_y()-3 < piat1->getY()+14)
					player->setY(piat1->getY()+14 - player->getDim_y());
				else
					player->setY(player->getY()-3);
				climbing = true;
			}
			else if(keyDown && player->getY() <= 285 && (scala1->playerHere(player) || scala2->playerHere(player)))  {
				if(player->getY()+3 > 285)
					player->setY(285);
				else
					player->setY(player->getY()+3);
				climbing = true;
			}
			else
				climbing = false;


			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return_value = -1;
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				al_stop_timer(timer);
				keyLeft = false;
				keyRight = false;
				if(!Pausa(res_info))  {	
					return_value = 2;
					break;
				}
				al_start_timer(timer);
			}	
			if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)
				keySpace=true;
			
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=true;

			if(ev.keyboard.keycode==ALLEGRO_KEY_UP)
				keyUp = true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)
				keyDown = true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)  {
				fullscreen = !fullscreen;

				if(fullscreen)  {
					res_info[0] = res_info[2] / res_info[4];
					res_info[1] = res_info[3] / res_info[5];
				}
				else  {
					res_info[0] = 1;
					res_info[1] = 1;
				}

				al_identity_transform(&redimencionamento);
				al_scale_transform(&redimencionamento,res_info[0], res_info[1]);
				al_use_transform(&redimencionamento);
				al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, fullscreen);
			}
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;

			if(ev.keyboard.keycode==ALLEGRO_KEY_UP)
				keyUp = false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)
				keyDown = false;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			al_draw_bitmap(sfondo,0,0,0);
			if(shoot && player->getY_arma()>0 && !presa)  {
				player->setY_arma(player->getY_arma() - 6);
				H_arma += 6;
			}
			else  {
				H_arma = 0;
				shoot=false;
			}
			if(vite>=1)
				al_draw_bitmap(vite_bmp, SCREEN_W/25, SCREEN_H/11, 0);
			if(vite>=2)
				al_draw_bitmap(vite_bmp, SCREEN_W/11, SCREEN_H/11, 0);
			if(vite>=3)
				al_draw_bitmap(vite_bmp, SCREEN_W/7, SCREEN_H/11, 0);
			if(vite<=0 || tempo<=0)
				caduto=true;

			al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

			blocco1->Draw();
			blocco2->Draw();
			blocco3->Draw();
			piat1->Draw();
			piat2->Draw();
			scala1->Draw();
			scala2->Draw();

			if(!drago->DrawFire(colpito,fire))
				fire=false;

			if(tempo/60<=145) 
			{
				if(drago->getX()<=530)
				{
					dragonArrive=false;
				}
				if(fireCount==0 || player->getX()>=470)
				{
					spitting=true;
					fireCount=300;
				}	
				if(!drago->Draw(dragonArrive,spitting))
					spitting=false;
				
				fireCount--;
			}
			if(spitting)
			fire=true;

			if(shoot)
				player->Draw_arma(H_arma);
			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto, climbing);
			if(!player->Draw())  {
				if(caduto)  {
					caduto=false;
					MatchOver=true;
				}	
				drawShoot=false;
			}
			
			if(!GP.Draw(drawExplosion))
				drawExplosion=false;

			tempo--;
			al_flip_display();
			redraw = false;
			/*if(GP.Empty())  {
				Transition(2);
				al_flush_event_queue(event_queue);
				while(true)  {
					al_wait_for_event(event_queue, &ev);
					if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
						Transition(3);
						al_rest(2);
						break;
					}
				}
				return_value = 1;
				break;
			}*/
		
		}					
	}
	
	//DISTRUGGO TUTTO
	player->setX(SCREEN_W/2 - player->getDim_x());
   	player->setY(SCREEN_H/1.37 - player->getDim_y());
	GP.Clear();

	return return_value;
}


#endif