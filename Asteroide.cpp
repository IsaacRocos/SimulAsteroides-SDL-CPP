#include "Asteroide.h"
#include "Posicion.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

Asteroide::Asteroide() {
    puntosSDL = new SDL_Point[MAX_VERTICES+1];
    nuevoAsteroide();
    //cout<<"Comprobando creacion..."<<endl;
    //comprobar();
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
    cout<<"\n-------------------"<<endl;
    cout<<" Creando Asteroide "<<endl;
    cout<<"-------------------"<<endl;
    posicionAst.nuevaPosicion();
    centroAst = new Vector2D(posicionAst.getX(),posicionAst.getY());
    cout<<"CENTRO: "<<posicionAst.getX()<<" , "<<posicionAst.getY()<<endl;
    radioAst = numAleatorio(RADIO_MINIMO, RADIO_MAXIMO);
    numPuntos = numAleatorio(MIN_VERTICES, MAX_VERTICES);
    cout << "[NPuntos]: "<<numPuntos<<endl;
    cout << "[Radio]: "<<radioAst<<endl;
    puntosVector.reserve(numPuntos);
    double variacionX = 0;
    double variacionY = 0;
    double variacionTotal = 0;
    for(int i = 0; i < numPuntos; i++){
        angulo = ((i+1)*(2*M_PI/numPuntos)) + numAleatorio(0.1, (5*M_PI/numPuntos)/2.0);
        variacionX = numAleatorio(0.7, ((double)radioAst)/10.0);
        variacionY = numAleatorio(0.3, ((double)radioAst)/8.0);
        x = radioAst * sin(angulo+0.1) + variacionX;
        y = radioAst * cos(angulo) + variacionY; 
        vec2dAux = new Vector2D(x,y);
        puntosVector.push_back(vec2dAux);
        puntosSDL[i].x = puntosVector[i]->getX() + centroAst->getX();
        puntosSDL[i].y = puntosVector[i]->getY() + centroAst->getY();
        variacionTotal =  variacionTotal + variacionX + variacionY;
    }
    puntosSDL[numPuntos].x = puntosSDL[0].x;
    puntosSDL[numPuntos].y = puntosSDL[0].y;

    setMasa(radioAst+0.0, variacionTotal);
    sentidoGiro = ((int)numAleatorio(0,2));
    if(sentidoGiro>0){sentidoGiro = 1;cout<<"*Giro derecha"<<endl;}
    else{sentidoGiro = -1;cout<<"*Giro izquierda"<<endl;}
    setVelocidad(radioAst);
    cout<<"Masa: "<<masa<<endl;
    cout<<"Velocidad: "<<velocidad<<endl;
    cout<<"Momento Inercial: "<<getMomentoInercial()<<endl;
}


void Asteroide::updatePos() {
    //cout<<"Actualizando posiciones...";
    posicionAst.mueve(velocidad); // actualizar vaores de X y Y en centro
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

Vector2D* Asteroide::getCentro(void){
    return centroAst;
}

void Asteroide::setMasa(double radioAst, double variacionTotal){
    masa = M_PI * ((radioAst+0.0) * (radioAst+0.0)) + variacionTotal;
}

void Asteroide::setVelocidad(double radioAst){
    velocidad = FACTOR_VELOCIDAD / radioAst;//(masa+0.0);
}


void Asteroide::actualizarDireccion(double dirHAstGolpeador, double dirVYAstGolpeador){
    posicionAst.setDirH(dirHAstGolpeador);
    posicionAst.setDirV(dirVYAstGolpeador);
}

int Asteroide::getDirH(void){
    return posicionAst.getDirH();
}


double Asteroide::getMomentoInercial(void){
    return velocidad * masa;
}

int Asteroide::getDirV(void){
    return posicionAst.getDirV();
}

int Asteroide::getPosicionEnVentana(){
    return posicionAst.getPosicionEnVentana();
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


double Asteroide::getRadio(void){
    return radioAst;
}

