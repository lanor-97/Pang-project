#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
enum Tipo{menu=0,ball,stageClear,bricks,dragon,farquaad,powerUp,victory};
class SoundEffect{
    private:
        Tipo tipo;
        ALLEGRO_SAMPLE *sound;
    public:
        SoundEffect();
        ~SoundEffect(){al_destroy_sample(sound);}
        SoundEffect(Tipo tipo);
        void Init();
        void Play(Tipo tipo);
};
#endif
