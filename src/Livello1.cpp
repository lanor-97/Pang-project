#include "headers/Livello1.h"

Livello1::Livello1()  {
	SCREEN_W = 0; 
	SCREEN_H = 0;
}
Livello1::Livello1(float SW, float SH, Giocatore* p, ALLEGRO_DISPLAY* display1, const int FPS): player(p), SCREEN_W(SW), SCREEN_H(SH)  {
	sfondo = al_load_bitmap("../images/sfondo1.jpg");
	GP = new GestorePalle(SW, SH);
	powerup = new PowerUp;
	
	font1=al_load_ttf_font("../fonts/SHREK.TTF",30,0);
	font2=al_load_ttf_font("../fonts/SHREK.TTF",25,0);
	vite_bmp = al_load_bitmap("../images/vita.png");
	pausa_play = al_load_bitmap("../images/pausa1.png");
	pausa_exit = al_load_bitmap("../images/pausa2.png");
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = display1;

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void Livello1::regolaPalle()  {
	GP->aggiungiPalla(SCREEN_W/2, 157, GRA, GREEN, true);
	GP->aggiungiPalla(50, 157, MED, GREEN, false);
}

Livello1::~Livello1()  {
	if(sfondo)  {
		al_destroy_bitmap(sfondo);
	}
	if(GP)  {
		delete GP;
	}
	if(font1)  {
		al_destroy_font(font1);
	}
	if(font2)  {
		al_destroy_font(font2);
	}
	if(vite_bmp)  {
		al_destroy_bitmap(vite_bmp);
	}
	if(timer)  {
		al_destroy_timer(timer);
	}
	if(event_queue)  {
		al_destroy_event_queue(event_queue);
	}
	if(pausa_play)  {
		al_destroy_bitmap(pausa_play);
	}
	if(pausa_exit)  {
		al_destroy_bitmap(pausa_exit);
	}
	if(powerup)  {
		delete powerup;
	}/*
	if(musica)  {
		delete musica;
	}
	if(sound)  {
		delete sound;
	}
	*/
}

bool Livello1::Pausa(bool& fullscreen, float res_info[])  {
	
	bool play = true, pausa=true, inGame=true;
	al_flush_event_queue(event_queue);
	//sound->Play("pause");
	while(pausa)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				pausa = false;
				break;
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER || ev.keyboard.keycode==ALLEGRO_KEY_SPACE)  {
				if(play)  {
					pausa=false;
					break;
				}
				else  {
					pausa=false;
					inGame=false;
				}	
			}
			else if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN && play){
				//sound->Play("menu");
				play = false;
			}	
			else if(ev.keyboard.keycode==ALLEGRO_KEY_UP && !play){ 
				play = true;
				//sound->Play("menu");
			}	
			else if(ev.keyboard.keycode==ALLEGRO_KEY_F)
				toggleFullscreen(fullscreen, res_info);
		}

		al_draw_bitmap(sfondo,0,0,0);
		player->Draw();
		GP->Draw(false);
		if(!play)
			al_draw_bitmap(pausa_exit,0,0,0);
		else
			al_draw_bitmap(pausa_play,0,0,0);

		al_flip_display();
	}
	//sound->Play("pause");
	al_flush_event_queue(event_queue);
	return inGame;
}

CASO Livello1::Esegui(int vite, int& punteggio, float res_info[])  {
	//DICHIARAZIONE ALTRE VARIABILI 
	bool 	colpito=false, p_hit=false, sfondo2=false, presa=false, redraw = true, 
			keyRight=false, keyLeft=false, keySpace=false, toLeft=false, 
			bitmap_ = true, fullscreen=false, trans=true, hit=false,
			next[4] = {false};

	drawShoot=false; caduto=false; shoot=false; 
	MatchOver=false; drawExplosion=false;

	int 	tempo=9000, H_arma=0, spawnY, timeEffect = 0;
	CASO 	return_value = EXIT;
	
	//sound =new SoundEffect();
	//musica=new Music(1);

	player->removeBubble();
	regolaPalle();
	al_flush_event_queue(event_queue);
	//musica->Play();
	al_start_timer(timer);
	//sound->Play("swamp");
	Transition(1);

	
	//IL GIOCO VERO E PROPRIO
	while(!MatchOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			hit = false;

			if(shoot)
				hit = GP->hitByHook(player, spawnY);
			else
				player->posizionaArma();

			//RAMPINO HA COLPITO PALLA
			if(hit && !presa)  {
				//sound->Play("ball");	
				punteggio+=200;
				presa=true;
				drawExplosion=true;
				if(powerup->canSpawn())  {
					powerup->Spawn(player->getArmaX(), spawnY);
				}
			}

			if(powerup->Spawned() && powerup->notArrivedTerrain(player->getY()+player->getDimY()))
				powerup->Fall();
			
			if(powerup->Spawned())  {
				int effect = powerup->playerTookIt(player);
				if(effect == 0)
					player->activeBubble();
				if(effect == 1)
					timeEffect = 300;
			}

			if(timeEffect <= 0)  {
				GP->Bouncer();
				
				//IF PALLA COLPISCE GIOCATORE
				p_hit = GP->playerHit(player, player->Bubble());
				if(p_hit && player->Bubble())  {
					p_hit = false;
					player->removeBubble();
					player->setImmuneTime(60);
				}
			}
			
			if(!hit)
				presa=false;

			if(player->Immune())
				player->decreaseImmune();

			//CONTROLLO MOVIMENTI DX/SX GIOCATORE
			if(keyRight && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=false;
				player->muoviSx(false, SCREEN_W);
			}
			if(keyLeft && !caduto && !drawShoot)  {
				player->setFrames(6);
				drawShoot=false;
				toLeft=true;
				player->muoviSx(true, 0);
			}
			if(keySpace && !caduto)  {
				if(!shoot)
					drawShoot=true;
				shoot=true;
				keySpace=false;
			}

			if(p_hit && !colpito && !caduto && !player->Immune())  {
				//sound->Play("hit");
				return_value = VITAPERSA;
				caduto=true;
				colpito=true;
			}
			if(!p_hit)
				colpito=false;

			if(shoot && player->getArmaY()>0 && !presa)  {
				player->setArmaY(player->getArmaY() - 6);
				H_arma += 6;
			}
			else  {
				H_arma = 0;
				shoot=false;
			}

			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return_value = EXIT;
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)  {
				al_stop_timer(timer);
				keyLeft = false;
				keyRight = false;
				if(!Pausa(fullscreen, res_info))  {	
					return_value = MENU;
					break;
				}
				al_start_timer(timer);
			}	
			if(ev.keyboard.keycode == ALLEGRO_KEY_N)
				next[0] = true;
			if(ev.keyboard.keycode == ALLEGRO_KEY_E)  {
				if(next[0])
					next[1] = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_X)  {
				if(next[1])
					next[2] = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_T)  {
				if(next[2])
					next[3] = true;
			}
			if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)
				keySpace=true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_F)
				toggleFullscreen(fullscreen, res_info);
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;
		}
		if(next[3])  {
			return_value = LIVELLOSUP;
			break;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			player->setDraw(keyLeft,keyRight,drawShoot,toLeft, caduto,false, false);
			Draw(vite, tempo, punteggio, H_arma);
			if(timeEffect > 0)
				timeEffect--;
			else
				tempo--;

			redraw = false;

			//CONTROLLO VITTORIA
			if(GP->Empty())  {
				//sound->Play("excellent");
				//sound->Play("applause");
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
				return_value = LIVELLOSUP;
				break;
			}

		if(vite==1 && return_value==VITAPERSA){
			al_flush_event_queue(event_queue);
			Transition(6);
				while(true)  {
					al_wait_for_event(event_queue, &ev);
					if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
						break;
					}
				}
			break;	
		}

		}			
	}
	
	//DISTRUGGO TUTTO
	player->setX(SCREEN_W/2 - player->getDimX());
   	player->setY(SCREEN_H/1.37 - player->getDimY());
	GP->Clear();
	powerup->Destroy();
	//delete sound;
	//delete musica;
	return return_value;
}


void Livello1::Transition(int x)
{
	bool trans=true;
	double speed = al_get_timer_speed(timer);

	al_flush_event_queue(event_queue);
	transizione.setTipo(x);
	player->setDraw(false,false,false,false, false,false, false);
	al_set_timer_speed(timer, 1.0 / 10);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	while(trans)  {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			if(x==1)
			{
				al_draw_bitmap(sfondo,0,0,0);
				GP->Draw(false);
				player->Draw();
			}
			if(x==2 || x==3)
			{
				player->DrawVictory();
			}	
			if(!transizione.Draw())  {
				trans = false;
				al_set_timer_speed(timer, speed);
			}
							
			al_flip_display();
		}
	}
}

void Livello1::Draw(int vite, int tempo, int punteggio, int H_arma)  {
	al_draw_bitmap(sfondo,0,0,0);

	if(vite>=1)
		al_draw_bitmap(vite_bmp, SCREEN_W/25, SCREEN_H/11, 0);
	if(vite>=2)
		al_draw_bitmap(vite_bmp, SCREEN_W/11, SCREEN_H/11, 0);
	if(vite>=3)
		al_draw_bitmap(vite_bmp, SCREEN_W/7, SCREEN_H/11, 0);
	if(vite<=0 || tempo<=0)
		caduto=true;

	//al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
	al_draw_textf(font1,al_map_rgb(255,255,0),SCREEN_W/4.7,SCREEN_H/1.16,ALLEGRO_ALIGN_RIGHT,"%d",tempo/60);
	al_draw_textf(font2,al_map_rgb(0,0,255),SCREEN_W/1.06,SCREEN_H/1.14,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

	if(shoot)
		player->ArmaDraw(H_arma);

	if(powerup->Spawned())
		powerup->Draw();

	if(!player->Draw())  {
		if(caduto)  {
			caduto=false;
			MatchOver=true;
		}	
		drawShoot=false;
	}
		
	if(!GP->Draw(drawExplosion))
		drawExplosion=false;

	al_flip_display();
}

void Livello1::toggleFullscreen(bool &fullscreen, float res_info[])  {
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