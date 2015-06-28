#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include  "Asteroide.h"

class Game{
	public:
		Game(const char* nombre, int xpos, int ypos, int win_w, int win_h, int numeroAst);
		void generaAsteroides(void);
		void manejaEventos(void);
		void update(void);//actualizar posiciones
		void render(void);//dibujar todo
		void eventoCerrar(void);
		int getRunning(void);
		void verificarColisones();
		~Game();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;
		int start_time , end_time;
		int running;
		int frames;
		int win_width;
		int win_height;
		std::vector<Asteroide*> asteroides;
		int numeroAsteroides;
};
#endif
