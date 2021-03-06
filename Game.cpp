#include "Game.h"
#include "Asteroide.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <cmath>

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
    cout<<"**************[OK]**************"<<endl;
}

//
// Actualizar posiciones, verificar salida de asteroides y colisiones
//
void Game::update(){
    bool asteroideFuera;
    //int tamanio = asteroides.size();
    for (int i = 0; i < numeroAsteroides; i++) {
        asteroides[i]-> updatePos();
        asteroideFuera = asteroides[i]-> verificarPos();
        if(asteroideFuera == true){
            asteroides[i]-> nuevoAsteroide();
        }
    }
    verificarColisones();
}

void Game::render(){
    //cout << "|Dibujando Asteroides|...";
    start_time = SDL_GetTicks(); // milisegundos
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
    //int tamanio = asteroides.size();
    for (int i = 0; i < numeroAsteroides; i++) {
        asteroides[i]->renderAsteroide(renderer);
    }
    SDL_RenderPresent(renderer);
    end_time = SDL_GetTicks() - start_time; 
    if(end_time< (1000.0f/frames)){  
        SDL_Delay((int)((1000.0f/frames) - end_time)); 
    }
    //cout<<"[OK]"<<endl;
}

// Para detectar colisiones entre asteroides
// Se toma un asteroide y se verifica si hay alguna colision con cualuquer otro
void Game::verificarColisones(void){
    int cxA1, cyA1; // centro ast1
    int cxA2, cyA2; // centro ast2
    int rA1 , rA2; // radios asteroides
    int distanciaColision;
    int dX,dY;
    int dirHAux, dirVAux;
    double miA1, miA2;
 
    for (int i = 0; i < numeroAsteroides; i++) {
        for (int j = 0; j < numeroAsteroides; j++) {
            if(i==j){continue;} // Evitar comparar asteroide con él mismo
            //if(asteroides[i]-> getPosicionEnVentana() <=1 || asteroides[j]-> getPosicionEnVentana() <=1){
                //continue;
            //}            
            // Obtener centro de asteroide base
            cxA1 = asteroides[i]-> getCentro() -> getX();
            cyA1 = asteroides[i]-> getCentro() -> getY();
            // Obtener radio de asteroide base
            rA1  = asteroides[i]-> getRadio();
            // Obtener momento inercial
            miA1 = asteroides[i]-> getMomentoInercial();
            //cout<<cxA1<<" " <<cyA1 <<endl;

            cxA2 = asteroides[j]-> getCentro() -> getX();
            cyA2 = asteroides[j]-> getCentro() -> getY();
            rA2  = asteroides[j]-> getRadio();
            miA2 = asteroides[j]-> getMomentoInercial();
            // Calcular distancia de colision
            distanciaColision = rA1 + rA2;
            // Calcular distancia actual entre los asteroides
            dX = abs(cxA1 - cxA2);
            dY = abs(cyA1 - cyA2);

            if(dX<=distanciaColision && dY<=distanciaColision){
                cout<<"\n-------------------------"<<endl;
                cout<<"[COLISION: A"<<i<<" <-> A"<<j<<"]"<<endl;
                cout<<"Distancia de colision: "<<distanciaColision<<endl;
                cout<<"dX = " <<dX<<" dY = "<<dY<<endl;
                if(miA1 > miA2){
                    cout<<" -Choque MIA1>MIA2: "<<rA1<<">"<<rA2<<endl;
                    cout<<"\t"<<miA1<<" > "<<miA2<<endl;
                    asteroides[i] -> actualizarDireccion(asteroides[j] -> getDirH(), asteroides[j] -> getDirV());
                    asteroides[j] -> nuevoAsteroide();
                } else if(miA1 < miA2){
                    cout<<" -Choque MIA1<MIA2: "<<rA1<<"<"<<rA2<<endl;
                    cout<<"\t"<<miA1<<" < "<<miA2<<endl;
                    asteroides[j] -> actualizarDireccion(asteroides[i] -> getDirH(), asteroides[i] -> getDirV());
                    asteroides[i] -> nuevoAsteroide();
                    j=0; // Reanudar revision para todos los asteroides
                    break;
                }else if(miA1 == miA2){
                    cout<<" -Choque - MOMENTOS INERCIALES IGUALES... WTF!-"<<endl;
                    cout<<"\t"<<miA1<<" = "<<miA2<<endl;
                    asteroides[j] -> nuevoAsteroide();
                    asteroides[i] -> nuevoAsteroide();
                    //dirHAux = asteroides[j] -> getDirH(); // Tomar direcciones de AstJ  antes de actualizar
                    //dirVAux = asteroides[j] -> getDirV();

                    //asteroides[j] -> actualizarDireccion(asteroides[i] -> getDirH(), asteroides[i] -> getDirV());
                    //asteroides[i] -> actualizarDireccion(dirHAux, dirVAux);
                    break;
                }
                cout<<"-------------------------"<<endl;
            }
        }

    }
}


Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

