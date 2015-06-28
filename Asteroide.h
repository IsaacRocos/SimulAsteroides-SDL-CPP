#ifndef _ASTEROIDE_H_
#define	_ASTEROIDE_H_
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "Posicion.h"
//--CONSTANTES -----------------------
#define MAX_VERTICES	 22
#define MIN_VERTICES	 12
#define RADIO_MAXIMO	 100.0
#define RADIO_MINIMO	 10.0
#define FACTOR_VELOCIDAD 10.0
//#define VEL_ROTACION    10.0   
//#define CAMBIO_ANGULO   15.0
//------------------------------------
class Asteroide{
        public:
                Asteroide(void);
                void renderAsteroide(SDL_Renderer* renderer);
                void comprobar(void);
                void nuevoAsteroide(void);  
                double numAleatorio(double n, double m);
                void limpiarVector(void);
                void updatePos(void);
                bool verificarPos(void);
                void girarAsteroide(double variacAngular);

                void setRenderer(SDL_Renderer* renderer);
                void setVelocidad(double vel);
                void setDesplazamiento(double desp);
                void actualizarDireccion(double posCXAstGolpeador, double posCYAstGolpeador);
                
                SDL_Point* getPuntos(void);
                Vector2D* getCentro(void);
                int getNPuntos(void);
                double getRadio(void);


        private:
                int numPuntos;
                SDL_Point* puntosSDL;
                std::vector<Vector2D*> puntosVector;
                int radioAst;
                Vector2D* centroAst;
                Posicion  posicionAst;
                SDL_Renderer* gRenderer;
                short sentidoGiro; // 0 izquierda, 1 derecha
                double desplazamiento;
                double velocidad;
};

#endif	
