#include "Asteroide.h"
#include "Posicion.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

Asteroide::Asteroide() {
    puntosSDL = new SDL_Point[21];
    nuevoAsteroide();
    cout<<"Comprobando creacion..."<<endl;
    comprobar();
    cout<<"[OK]..."<<endl;
}


void Asteroide::comprobar() {
    for (int i = 0; i <numPuntos;i++){
        cout<<"V " << i << ") " << puntosVector[i]->getX() << " , " <<puntosVector[i]->getY()<<endl;
    }
}


void Asteroide::nuevoAsteroide() {
    limpiarVector();
    double angulo;
    double x, y;
    Vector2D* vec2dAux;
    cout<<"Creando Asteroide..."<<endl;
    centroAst = new Vector2D(posicionAst.getX(),posicionAst.getY());
    cout<<"CENTRO: "<<posicionAst.getX()<<" , "<<posicionAst.getY()<<endl;
    radioAst = numAleatorio(RADIO_MINIMO, RADIO_MAXIMO);
    numPuntos = numAleatorio(MIN_VERTICES, MAX_VERTICES);
    cout << "[NV]: "<<numPuntos<<endl;
    cout << "[R]: "<<radioAst<<endl;
    puntosVector.reserve(numPuntos);
    for(int i = 0; i < numPuntos; i++){
        angulo = ((i+1)*(2*M_PI/numPuntos)) + numAleatorio(0.1, (5*M_PI/numPuntos)/2.0);
        x = radioAst * sin(angulo+0.1) + numAleatorio(0.7, ((double)radioAst)/10.0);
        y = radioAst * cos(angulo) + numAleatorio(0.3, ((double)radioAst)/8.0); 
        vec2dAux = new Vector2D(x,y);
        puntosVector.push_back(vec2dAux);
        puntosSDL[i].x = puntosVector[i]->getX() + centroAst->getX();
        puntosSDL[i].y = puntosVector[i]->getY() + centroAst->getY();
    }
    puntosSDL[numPuntos].x = puntosSDL[0].x;
    puntosSDL[numPuntos].y = puntosSDL[0].y;
    sentidoGiro = ((int)numAleatorio(0,1.2));
    if(sentidoGiro>0){sentidoGiro = 1;cout<<"Giro derecha"<<endl;}
    else{sentidoGiro = -1;cout<<"Giro izquierda"<<endl;}
}


void Asteroide::updatePos() {
    //cout<<"Actualizando posiciones...";
    posicionAst.mueve(radioAst + 0.0); // actualizar vaores de X y Y en centro
    centroAst->setX(posicionAst.getX());
    centroAst->setY(posicionAst.getY());
        for(int i = 0; i < numPuntos; i++){
            puntosSDL[i].x = puntosVector[i]->getX() + centroAst->getX();
            puntosSDL[i].y = puntosVector[i]->getY() + centroAst->getY();
        }
        puntosSDL[numPuntos].x = puntosSDL[0].x;
        puntosSDL[numPuntos].y = puntosSDL[0].y;
    girarAsteroide(( (2*M_PI)/(radioAst*10) ) * sentidoGiro);
}


void Asteroide::girarAsteroide(double anguloR) {
    double x, y;
    for(int i = 0; i < numPuntos; i++){
        x = puntosVector[i]->getX();
        y = puntosVector[i]->getY();
        puntosVector[i]->setX(x * cos(anguloR) - y * sin(anguloR));
        puntosVector[i]->setY(x * sin(anguloR) + y * cos(anguloR));
    }
}


void Asteroide::renderAsteroide(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 216, 17, 43, 150);
    SDL_RenderDrawLines(renderer, puntosSDL , numPuntos+1);
}


bool Asteroide::verificarPos() {
    bool lugar = posicionAst.verificarLugar();
    return lugar;
}

void Asteroide::limpiarVector() {
    Vector2D *aux;
    while(puntosVector.size()>0){
        aux = puntosVector.back();
        puntosVector.pop_back();
        if(aux != NULL){delete aux;}
    }
}

void Asteroide::setRenderer(SDL_Renderer* renderer) {
    gRenderer = renderer;
}

double Asteroide::numAleatorio(double n, double m) {
    return rand()*(1.0/RAND_MAX)*(m-n) + n;
}


SDL_Point* Asteroide::getPuntos() {
    return puntosSDL;
}

int Asteroide::getNPuntos() {
    return numPuntos;
}

