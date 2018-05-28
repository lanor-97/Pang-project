#include "headers/SoundEffect.h"
SoundEffect::SoundEffect(){
    menu=al_load_sample("../audio/menu.wav");
    ball=al_load_sample("../audio/ball.wav");
    applause=al_load_sample("../audio/applause.wav");
    dragon1=al_load_sample("../audio/dragon1.wav");
    dragonloop=al_load_sample("../audio/dragonloop.wav");
    excellent=al_load_sample("../audio/excellent.wav");
    farquaad=al_load_sample("../audio/farquaad.wav");
    getReady=al_load_sample("../audio/getReady.wav");
    hit=al_load_sample("../audio/hit.wav");
    hitlair=al_load_sample("../audio/hitlair.wav");
    pause=al_load_sample("../audio/pause.wav");
    powerUp1=al_load_sample("../audio/powerUp1.wav");
    powerUp2=al_load_sample("../audio/powerUp2.wav");
    showtime=al_load_sample("../audio/showtime.wav");
    swamp=al_load_sample("../audio/swamp.wav");
}
SoundEffect::~SoundEffect(){
        al_destroy_sample(menu);
        al_destroy_sample(ball);
        al_destroy_sample(applause);
        al_destroy_sample(dragon1);
        al_destroy_sample(dragonloop);
        al_destroy_sample(excellent);
        al_destroy_sample(farquaad);
        al_destroy_sample(getReady);
        al_destroy_sample(hit);
        al_destroy_sample(hitlair);
        al_destroy_sample(pause);
        al_destroy_sample(powerUp1);
        al_destroy_sample(powerUp2);
        al_destroy_sample(showtime);
        al_destroy_sample(swamp);
}
void SoundEffect::Play(string tipo){
        if(tipo== "menu")
            al_play_sample(menu,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "ball")
            al_play_sample(ball,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "applause")
            al_play_sample(applause,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "dragon1")
            al_play_sample(dragon1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "dragonloop")
            al_play_sample(dragonloop,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,0);
        if(tipo== "excellent")
            al_play_sample(excellent,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "farquaad")
            al_play_sample(farquaad,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "getReady")
            al_play_sample(getReady,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "hit")
            al_play_sample(hit,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "hitlair" )
            al_play_sample(hitlair,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "pause")
            al_play_sample(pause,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "powerUp1")
            al_play_sample(powerUp1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);        
        if(tipo== "powerUp2")
            al_play_sample(powerUp2,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "showtime")
            al_play_sample(showtime,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        if(tipo== "swamp")
            al_play_sample(swamp,4.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}