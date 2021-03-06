#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "game.h"

int main(int argc, char **argv){

	Game* game = (Game*) malloc(sizeof(Game));

	//----------------------- rotinas de inicializacao ---------------------------------------

	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}

	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    game->timer = al_create_timer(1.0 / FPS);
    if(!game->timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	al_set_new_window_position(1, 25);
	game->display = al_create_display(SCREEN_W, SCREEN_H);
	if(!game->display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(game->timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}

	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    game->regular_font = al_load_font("rsc/spaceage.ttf", 32, 1);
	if(game->regular_font == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	game->event_queue = al_create_event_queue();
	if(!game->event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(game->display);
		return -1;
	}

	//inicializa audio
	if (!al_install_audio() || !al_init_acodec_addon()) {
		fprintf(stderr, "failed to install audio subsystem\n");
		return -1;
	}
	ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (!voice) {
		fprintf(stderr, "Could not create ALLEGRO_VOICE.\n");
		return -1;
	}
	ALLEGRO_MIXER* mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if (!mixer) {
		fprintf(stderr, "al_create_mixer failed.\n");
		return -1;
	}
	if (!al_attach_mixer_to_voice(mixer, voice) || !al_set_default_mixer(mixer) || !al_reserve_samples(30)) {
		fprintf(stderr, "al_attach_mixer_to_voice or al_set_default_mixer failed.\n");
		return -1;
	}



	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(game->event_queue, al_get_display_event_source(game->display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(game->event_queue, al_get_timer_event_source(game->timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(game->event_queue, al_get_keyboard_event_source());


	//inicializações do jogo
	on_game_init(game);

	//inicia o temporizador
	al_start_timer(game->timer);

	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(game->event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {

			game->delta_time = al_get_time() - game->time;
			game->time += game->delta_time;
			if (game->delta_time > .15) game->delta_time = .15;
///////////////////////////////////////////////////////////////////////////////////////////////
			on_update(game); //   GAME UPDATE   ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
				if (game->keyboard[i] == KEY_STATE_DOWN)
					game->keyboard[i] = KEY_STATE_HOLD;
				if (game->keyboard[i] == KEY_STATE_UP)
					game->keyboard[i] = KEY_STATE_NULL;
			}

			al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			game->keyboard[ev.keyboard.keycode] = KEY_STATE_UP;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			game->keyboard[ev.keyboard.keycode] = KEY_STATE_DOWN;
		}

	}

	on_game_exit(game);

	al_destroy_mixer(mixer);
	al_destroy_voice(voice);
	al_destroy_timer(game->timer);
	al_destroy_display(game->display);
	al_destroy_event_queue(game->event_queue);


	return 0;
}
