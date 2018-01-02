#include "Giocatore.h"
#include "Palla.h"
#include "Arma.h"
#include "Sfondo.h"
#include "Vita.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char **argv)  {   //int argc e char **argv li devi mettere se no non va a me
																			//poi a limite li togliamo
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   	ALLEGRO_TIMER *timer = NULL;
		ALLEGRO_FONT *font1=NULL;
		ALLEGRO_FONT *	font2=NULL;

		al_init_font_addon();
		al_init_ttf_addon();
   	bool redraw = true;
   	bool keyRight=false, keyLeft=false, keySpace=false;
	bool GameOver=false;
		int punteggio=0;
		int tempo=3600;

	if(!al_init()) {
    	cerr << "failed to initialize allegro!\n";
    	return -1;
   	}

   	if(!al_init_image_addon()) {
      	cerr<<"failed to initialize allegro_image\n";
		return -1;
   	}


		if(!al_init_ttf_addon())
		{
			cerr<<"failed to initialize allegro_ttf\n";
			return -1;
		}
		if(!al_init_font_addon())
		{
			cerr<<"failed to initialize allegro_font\n";

			return -1;
		}

		timer = al_create_timer(1.0 / FPS);
		if(!timer) {
			cerr<<"failed to create timer!\n";
			return -1;
		}

   	display = al_create_display(SCREEN_W, SCREEN_H);
   	if(!display) {
		cerr<<"failed to create display!\n";
		al_destroy_timer(timer);
      	return -1;
   	}


		font1=al_load_ttf_font("images/SHREK.TTF",40,0);
		if(!font1)
		{
			cerr<<"failed to initialize font1\n";
			al_destroy_timer(timer);
			return -1;
		}

		font2=al_load_ttf_font("images/SHREK.TTF",25,0);
		if(!font2)
		{
			cerr<<"failed to initialize font2\n";
			al_destroy_timer(timer);
			return -1;
		}

	Palla palla(170, GRA);
   	if(!palla.getBitmap())  {
		cerr<<"failed to initialize palla.png!\n";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_font(font1);
		al_destroy_font(font2);
		return -1;
   	}
   	palla.setX(SCREEN_W/2);
   	palla.setY(palla.calculateY(SCREEN_H));

   	Giocatore player(35,50);
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

	sfondo.Draw();
	palla.Draw();
	player.Draw();
	al_flip_display();
	al_start_timer(timer);
   	bool shoot=false, colpito=false, sfondo2=false, presa=false;

   	while(!GameOver) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(shoot==false)  {
			arma.setX(player.getX());
			arma.setY(player.getY()+player.getDim_y()+2);
		}

		if(ev.type == ALLEGRO_EVENT_TIMER)  {
			if(palla.getX() < 0 || palla.getX() > SCREEN_W - palla.getDim()) {
				palla.setBouncer(-palla.getBouncer());
			}

			palla.setX(palla.getX()+palla.getBouncer());
			palla.setY(palla.calculateY(SCREEN_H));

			bool 	ball_hook_1 = arma.getX() <= palla.getX()+palla.getDim(),
					ball_hook_2 = arma.getX()+arma.getDim() >= palla.getX(),
					ball_hook_3 = arma.getY() <= palla.getY()+palla.getDim();

			if(ball_hook_1 && ball_hook_2 && ball_hook_3 && !presa)  {
				//rampino colpisce palla
				punteggio+=200;
				presa=true;
			}
			if(!ball_hook_1 || !ball_hook_2 || !ball_hook_3)
				presa=false;

			if(keyRight)  {
				if(player.getX()+player.getDim_x()+5 <= SCREEN_W)
					player.setX(player.getX()+5);
				else
					player.setX(SCREEN_W-player.getDim_x());
			}
			if(keyLeft)  {
				if(player.getX()-5 >= 0)
					player.setX(player.getX()-5);
				else
					player.setX(0);
			}
			if(keySpace)  {
				shoot=true;
				keySpace=false;
			}

			bool	ball_player_1 = palla.getX()+palla.getDim() >= player.getX(),
					ball_player_2 = palla.getX() <= player.getX()+player.getDim_x(),
					ball_player_3 = player.getY() <= palla.getY()+palla.getDim();

			if(ball_player_1 && ball_player_2 && ball_player_3 && !colpito)  {
				//palla colpisce player
				colpito=true;
				vite--;
			}
			if(!ball_player_1 || !ball_player_2 || !ball_player_3)
				colpito=false;

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  {
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
				sfondo.setBitmap(al_load_bitmap("images/sfondo2.png"));
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

			al_draw_textf(font1,al_map_rgb(0,255,0),30,20,ALLEGRO_ALIGN_LEFT,"%d",tempo/60);
			al_draw_textf(font2,al_map_rgb(0,0,255),620,100,ALLEGRO_ALIGN_RIGHT,"%d",punteggio);
			player.Draw();
			palla.Draw();
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
