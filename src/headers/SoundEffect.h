#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
enum Effect{menu=0,ball,cleared,bricks,dragon,farquaad,powerUp,finish};
class SoundEffect{
    private:
        Effect tipo;
        ALLEGRO_SAMPLE *sound;
    public:
        SoundEffect();
        ~SoundEffect(){al_destroy_sample(sound);}
        SoundEffect(Effect tipo);
        void Init();
        void Play(Effect tipo);
};
#endif
