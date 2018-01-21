#include "Giocatore.h"
#include "GestorePalle.h"
#include "Arma.h"
#include "Sfondo.h"
#include "Vita.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char **argv)  {  //int argc e char **argv li devi mettere se no non va a me
												//poi a limite li togliamo
	ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font1=NULL;
	ALLEGRO_FONT *	font2=NULL;
	ALLEGRO_TRANSFORM redimencionamento;
	ALLEGRO_MONITOR_INFO info;

	al_init_font_addon();
	al_init_ttf_addon();
   bool redraw = true;
   bool keyRight=false, keyLeft=false, keySpace=false;
	bool GameOver=false;
	bool bitmap_ = true;
	int punteggio=0;
	int tempo=3600;
	int res_monitor_x;
	int res_monitor_y;
	float res_x;
	float res_y;
	bool toLeft=false;
	int currFrame=0;
	int frameCount=0;
	int frameDelay=5;
	if(!al_init())  {
    	cerr << "failed to initialize allegro!\n";
    	return -1;
   }

   if(!al_init_image_addon())  {
     	cerr<<"failed to initialize allegro_image\n";
		return -1;
   }


	if(!al_init_ttf_addon())  {
		cerr<<"failed to initialize allegro_ttf\n";
		return -1;
	}

	if(!al_init_font_addon())  {
		cerr<<"failed to initialize allegro_font\n";
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		cerr<<"failed to create timer!\n";
		return -1;
	}

	al_get_monitor_info(0,&info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = res_monitor_x / (float) SCREEN_W;
	res_y = res_monitor_y / (float) SCREEN_H;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(res_monitor_x,res_monitor_y);
   if(!display) {
		cerr<<"failed to create display!\n";
		al_destroy_timer(timer);
     	return -1;
   }

	al_identity_transform(&redimencionamento);
	al_scale_transform(&redimencionamento,res_x,res_y);
	al_use_transform(&redimencionamento);

	font1=al_load_ttf_font("images/SHREK.TTF",40,0);
	if(!font1)  {
		cerr<<"failed to initialize font1\n";
		al_destroy_timer(timer);
		return -1;
	}

	font2=al_load_ttf_font("images/SHREK.TTF",25,0);
	if(!font2)  {
		cerr<<"failed to initialize font2\n";
		al_destroy_timer(timer);
		return -1;
	}

	GestorePalle GP;
	GP.setSW(SCREEN_W);
	GP.setSY(SCREEN_H);
	bitmap_ = GP.aggiungiPalla(SCREEN_W/2, 157, GRA) && GP.aggiungiPalla(0, 157, GRA);
	if(!bitmap_)  {
		cerr<<"failed to initialize palla.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
		return -1;
	}

   Giocatore player(60,70,6);
	if(!player.getBitmap())  {
		cerr<<"failed to initialize man.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
		return -1;
   }
   player.setX(SCREEN_W/2 - player.getDim_x());
   player.setY(SCREEN_H - player.getDim_y());

   Arma arma(24,player.getX(), player.getY());
   if(!arma.getBitmap())  {
		cerr<<"failed to initialize arpione.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
		return -1;
   }

   Vita vite(3);
	if(!vite.getBitmap())  {
		cerr<<"failed to initialize cuore.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
	}

	Sfondo sfondo;
	if(!sfondo.getBitmap())  {
		cerr<<"failed to initialize sfondo1.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
	}

   event_queue = al_create_event_queue();
   if(!event_queue) {
		cerr<<"failed to create event_queue!\n";
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_font(font1);
		al_destroy_font(font2);
		return -1;
   }

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_install_keyboard();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	bool drawShoot=false;
	bool caduto=false;
	bool shoot=false, colpito=false, sfondo2=false, presa=false;
	sfondo.Draw();
	GP.Draw();
	player.Draw(currFrame,keyLeft,keyRight,drawShoot,toLeft, caduto);
	al_flip_display();
	al_start_timer(timer);

   while(!GameOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(shoot==false)  {
			arma.setX(player.getX());
			arma.setY(player.getY()+player.getDim_y()+2);
		}

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			if(drawShoot && !caduto)
				{
				 	frameDelay=7;
				 	player.setFrames(2);
				}
			else if(caduto)
				{		
					player.setFrames(11);
					frameDelay=7;
				}	
			else	
				frameDelay=5;

			if(++frameCount>=frameDelay)
			{
						if(++currFrame>=player.getFrames())
						{
						drawShoot=false;
						caduto=false;
						currFrame=0;
					}
				frameCount=0;
			}


			GP.Bouncer();

			bool hit = GP.hitByHook(arma.getX(), arma.getY(), arma.getDim(), bitmap_);  //rampino colpisce palla

			if(!bitmap_)  {
				cerr << "failed to initialize some palla.png";
				break;
			}

			if(hit && !presa)  {
				punteggio+=200;
				presa=true;
			}
			if(!hit)
				presa=false;

			if(keyRight && !caduto && !drawShoot)  {
				player.setFrames(6);
				drawShoot=false;
				toLeft=false;
				if(player.getX()+player.getDim_x()+5 <= SCREEN_W)
					player.setX(player.getX()+5);
				else
					player.setX(SCREEN_W-player.getDim_x());
			}
			if(keyLeft && !caduto && !drawShoot)  {
				player.setFrames(6);
				drawShoot=false;
				toLeft=true;
				if(player.getX()-5 >= 0)
					player.setX(player.getX()-5);
				else
					player.setX(0);
			}
			if(keySpace && !caduto)  {
				if(!shoot)
				drawShoot=true;
				shoot=true;
				keySpace=false;
			}

			bool p_hit = GP.playerHit(player.getX(), player.getY(), player.getDim_x());

			if(p_hit && !colpito && !caduto)  {
				//palla colpisce player
				caduto=true;
				colpito=true;
				vite--;
			}
			if(!p_hit)
				colpito=false;

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
				break;
			if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)
				keySpace=true;
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=true;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=true;
		}
		else if(ev.type==ALLEGRO_EVENT_KEY_UP)  {
			if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
				keyRight=false;
			else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
				keyLeft=false;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			if(vite.getNumVite() == 2 && !sfondo2)  {
				sfondo.setBitmap(al_load_bitmap("images/sfondo1.png"));
				if(!sfondo.getBitmap())  {
					cerr<<"failed to initializate sfondo2.png";
					break;
				}
				sfondo2=true;
			}

			sfondo.Draw();
			if(shoot && arma.getY()>0 && !presa)  {
				arma.Draw();
				arma.setY(arma.getY()-arma.getDim()/4);	//il /4 è per rallentarlo
			}
			else  {
				shoot=false;
			}

			if(vite>=1)
				vite.Draw(580,50);
			if(vite>=2)
				vite.Draw(540,50);
			if(vite>=3)
				vite.Draw(500,50);
			if(vite<=0 || tempo<=0)
				GameOver=true;
			al_draw_text(font1,al_map_rgb(0,255,0),320,0,ALLEGRO_ALIGN_CENTRE,"Shrek Pang");
			al_draw_textf(font1,al_map_rgb(0,255,0),30,20,ALLEGRO_ALIGN_LEFT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),620,100,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);

			if((caduto || drawShoot) && currFrame>=player.getFrames())
			currFrame=0;

			player.Draw(currFrame,keyLeft,keyRight,drawShoot,toLeft, caduto);
			GP.Draw();
			tempo--;
			al_flip_display();
			redraw = false;
		}
	}
	al_destroy_font(font1);
	al_destroy_font(font2);
   al_destroy_timer(timer);
  	al_destroy_display(display);
  	al_destroy_event_queue(event_queue);

  	return 0;
}
