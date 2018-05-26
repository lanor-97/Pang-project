#include "headers/Music.h"
Music::Music(int x){
    al_reserve_samples(8);
    al_install_audio();
    al_init_acodec_addon();
    tipo=x;
    switch(x){
        case 1:
        //carico musica 1
        break;
        case 2:
        //carico musica 2
        break;
        case 3:
        //carico musica 3
        break;
        
    }
    instance=al_create_sample_instance(song);
    al_set_sample_instance_playmode(instance,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(instance,al_get_default_mixer());

}

void Music::Play(){
    al_play_sample_instance(instance);
}