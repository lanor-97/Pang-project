#include "headers/Music.h"
Music::Music(int x){
    al_reserve_samples(2);
    tipo=x;
    switch(tipo){
        case 1:
            song=al_load_sample("audio/allStar.ogg");
            break;
        case 2:
            song=al_load_sample("audio/megalovania.ogg");
            break;
        case 3:
            song=al_load_sample("audio/hopesAndDreams.ogg");
            break;
        
    }
    instance=al_create_sample_instance(song);
    al_set_sample_instance_playmode(instance,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(instance,al_get_default_mixer());

}

void Music::Play(){
    al_play_sample_instance(instance);
}