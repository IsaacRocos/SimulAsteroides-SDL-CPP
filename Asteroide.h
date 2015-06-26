#ifndef _ASTEROIDE_H_
#define	_ASTEROIDE_H_
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "Posicion.h"
//--CONSTANTES -----------------------
#define MAX_VERTICES	20
#define MIN_VERTICES	10
#define RADIO_MAXIMO	100.0
#define RADIO_MINIMO	10.0
//#define VEL_ROTACION    10.0   
//#define CAMBIO_ANGULO   15.0
//------------------------------------
class Asteroide{
        public:
                Asteroide();
                void renderAsteroide(SDL_Renderer* renderer);
                SDL_Point* getPuntos();
                void comprobar();
                int getNPuntos();
                void nuevoAsteroide();  
                double numAleatorio(double n, double m);
                void limpiarVector();
                void updatePos();
                bool verificarPos();
                void girarAsteroide(double);
                void setRenderer(SDL_Renderer* renderer);
        private:
                int numPuntos;
                SDL_Point* puntosSDL;
                std::vector<Vector2D*> puntosVector;
                int radioAst;
                Vector2D* centroAst;
                Posicion  posicionAst;
                SDL_Renderer* gRenderer;
                short sentidoGiro; // 0 izquierda, 1 derecha
};

#endif	
