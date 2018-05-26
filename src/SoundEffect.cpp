#include "headers/SoundEffect.h"
SoundEffect::SoundEffect(){
    sound=NULL;
    tipo=menu;
  /*  this->tipo=tipo;
    switch(tipo){
        case 0:
        //carico souno 1
        break;
        case 1:
        //carico suono 2
        break;
        case 2:
        //carico suono 3
        break;
        
    }
    */
}
void SoundEffect::Init(){
    al_reserve_samples(2);
    al_install_audio();
    al_init_acodec_addon();
}
void SoundEffect::Play(Effect tipo){
    switch(tipo){
        case 0:
        //carico souno 1
        break;
        case 1:
        //carico suono 2
        break;
        case 2:
        //carico suono 3
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        break;

    }
    al_play_sample(sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}