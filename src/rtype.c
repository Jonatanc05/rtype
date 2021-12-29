#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "game.h"
#include "entity.h"
#include "text_component.h"

const float FPS = 100;

const int SCREEN_W = 960;
const int SCREEN_H = 540;

void on_game_init(Game* game) {
	game->numEntities = 0;
	game->entities = (Entity*) calloc(MAX_ENTITIES, sizeof(Entity));
	if (game->entities == NULL) printf("Erro ao alocar memoria para entidades\n");

	// Criando a entidade "hello world"
	Entity* e = entity_create(game);
	entity_add_position(e, 0, 0);
	entity_add_text(e, 0, 0, "Hello World!", REGULAR_FONTSIZE);
	entity_add_player(e, ALLEGRO_KEY_W, ALLEGRO_KEY_A, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_SPACE);
}

void on_update(Game* game) {
	system_draw_text(game);
}

void on_game_exit(Game* game) {
	free(game->entities);
}

int main(int argc, char **argv){

	Game* game = (Game*) malloc(sizeof(Game));

	game->display = NULL;
	game->event_queue = NULL;
	game->timer = NULL;

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
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(game->event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			on_update(game);

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();

			if(al_get_timer_count(game->timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(game->timer)/FPS));
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}

	} //fim do while

	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	on_game_exit(game);

	al_destroy_timer(game->timer);
	al_destroy_display(game->display);
	al_destroy_event_queue(game->event_queue);


	return 0;
}
