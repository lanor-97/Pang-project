#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
using namespace std;
class SoundEffect{
    private:
        ALLEGRO_SAMPLE *menu;
        ALLEGRO_SAMPLE *ball;
        ALLEGRO_SAMPLE *applause;
        ALLEGRO_SAMPLE *dragon1;
        ALLEGRO_SAMPLE *dragonloop;
        ALLEGRO_SAMPLE *excellent;
        ALLEGRO_SAMPLE *farquaad;
        ALLEGRO_SAMPLE *getReady;
        ALLEGRO_SAMPLE *hit;
        ALLEGRO_SAMPLE *hitlair;
        ALLEGRO_SAMPLE *pause;
        ALLEGRO_SAMPLE *powerUp1;
        ALLEGRO_SAMPLE *powerUp2;
        ALLEGRO_SAMPLE *showtime;
        ALLEGRO_SAMPLE *swamp;
        ALLEGRO_SAMPLE *brick;
        ALLEGRO_SAMPLE *gameOver;
        ALLEGRO_SAMPLE *gameOverMusic;
        ALLEGRO_SAMPLE *levelCleared;
    public:
        SoundEffect();
        ~SoundEffect();
        void Play(string tipo);
};
#endif
