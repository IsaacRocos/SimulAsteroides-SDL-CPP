#include "Game.h"
#include "Asteroide.h"
#include <SDL2/SDL.h>
#include <cstdlib>

using namespace std;

Game::Game(const char* nombre, int xpos, int ypos, int win_w, int win_h, int numeroAst){
    win_width = win_w;
    win_height = win_h;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(nombre, xpos, ypos, win_width, win_height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // antes 0
    SDL_Event event;
    frames = 60;
    running = 1;
    numeroAsteroides = numeroAst;
    generaAsteroides();
}

int Game::getRunning(){
    return running;
}

void Game::manejaEventos(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                running = 0;
            }
        }
    }
}

void Game::generaAsteroides(){
    cout<<"Generando "<<numeroAsteroides<<" asteroides...";
    Asteroide* nuevoAst;
    for(int i = 0; i< numeroAsteroides; i++){
        nuevoAst = new Asteroide();
        nuevoAst->setRenderer(renderer);
        asteroides.push_back(nuevoAst);
    }
    cout<<"[OK]"<<endl;
}

void Game::update(){
    bool asteroideFuera;
    int tamanio = asteroides.size();
    for (int i = 0; i < tamanio; i++) {
        asteroides[i]-> updatePos();
        asteroideFuera = asteroides[i]-> verificarPos();
        if(asteroideFuera == true){
            asteroides[i]-> nuevoAsteroide();
        }
    }
}

void Game::render(){
    //cout << "|Dibujando Asteroides|...";
    start_time = SDL_GetTicks(); // milisegundos
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
    int tamanio = asteroides.size();
    for (int i = 0; i < tamanio; i++) {
        asteroides[i]->renderAsteroide(renderer);
    }
    SDL_RenderPresent(renderer);
    end_time = SDL_GetTicks() - start_time; 
    if(end_time< (1000.0f/frames)){  
        SDL_Delay((int)((1000.0f/frames) - end_time)); 
    }
    //cout<<"[OK]"<<endl;
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

