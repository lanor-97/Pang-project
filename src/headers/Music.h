#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
class Music{
    private:
        int tipo;
        ALLEGRO_SAMPLE *song;
        ALLEGRO_SAMPLE_INSTANCE *instance;
    public:
        Music(): song(NULL), instance(NULL), tipo(0){};
        ~Music(){al_destroy_sample_instance(instance);  al_destroy_sample(song);}
        Music(int x);
        void Play();
};
#endif
