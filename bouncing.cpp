#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"
#include "ball.h"
#include "hook.h"
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;


int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   bool redraw = true;
   bool keyRight, keyLeft, keySpace=false;
   float bouncer_dx=5;
   float bouncer_dy=-5;



   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }


   Ball palla(70,SCREEN_W/2-35,SCREEN_H/2-25);
   if(!palla.getBall())
   {
     cerr<<"failed to initialize palla!\n";
     al_destroy_timer(timer);
     al_destroy_display(display);
     return -1;
   }

   al_set_target_bitmap(palla.getBall());
   al_clear_to_color(al_map_rgb(255, 0, 255));


   Player tizio(50,SCREEN_W/2-25,SCREEN_H-50);

   if(!tizio.getPlayer())
   {
     cerr<<"failed to initialize player!\n";
     al_destroy_timer(timer);
     al_destroy_display(display);
     return -1;
   }
   al_set_target_bitmap(tizio.getPlayer());
   al_clear_to_color(al_map_rgb(255, 0, 255));

   Hook rampino(SCREEN_H,SCREEN_W/2,SCREEN_H/2);
   if(!rampino.getHook())
   {
     cerr<<"failed to initialize hook!\n";
     al_destroy_timer(timer);
     al_destroy_display(display);
     tizio.Destroy();
     return -1;
   }
   al_set_target_bitmap(rampino.getHook());
   al_clear_to_color(al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      tizio.Destroy();
      rampino.Destroy();
      return -1;
   }


   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_install_keyboard();
   al_register_event_source(event_queue,al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_clear_to_color(al_map_rgb(0,0,0));

   al_flip_display();
   al_start_timer(timer);
   palla.Draw();
   tizio.Draw();
   bool shoot=false;
   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      if(shoot==false)
      {
        rampino.setX(tizio.getX());
        rampino.setY(tizio.getY());
      }
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(palla.getX() < 0 || palla.getX() > SCREEN_W - palla.getDim()) {
            bouncer_dx = -bouncer_dx;
         }

         if(palla.getY() < 0 || palla.getY() > SCREEN_H - palla.getDim()) {
            bouncer_dy = -bouncer_dy;
         }

         palla.setX(palla.getX()+ bouncer_dx);
         palla.setY(palla.getY()+bouncer_dy);

         if(keyRight)
         tizio.setX(tizio.getX()+10);
         if(keyLeft)
         tizio.setX(tizio.getX()-10);
         if(keySpace)
           {
             shoot=true;
             keySpace=false;
           }


         redraw = true;
      }


      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        break;
        al_destroy_display(display);
      }



      if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
      {
        if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)
          keySpace=true;
        if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
          keyRight=true;

        else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
          keyLeft=true;
      }
      else if(ev.type==ALLEGRO_EVENT_KEY_UP)
      {
       if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
          keyRight=false;
        else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
          keyLeft=false;
      }



      if(redraw && al_is_event_queue_empty(event_queue)) {

         al_clear_to_color(al_map_rgb(0,0,0));
         if(shoot && rampino.getY()>0)
         {
             rampino.Draw();
             rampino.setY(rampino.getY()-rampino.getDim()/100);
        }
           else
           {
             shoot=false;
           }


         tizio.Draw();
         palla.Draw();
         redraw = false;


         al_flip_display();
      }
}
  rampino.Destroy();
   tizio.Destroy();
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}
