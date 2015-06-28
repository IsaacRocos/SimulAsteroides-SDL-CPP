#include "Posicion.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

Posicion::Posicion(){
	//nuevaPosicion();
}

// Para inicializar y resetear posic
void Posicion::nuevaPosicion(){
	sentido = numAleatorio(-3,3);
	iniDirecciones();
	posEnVentana = 0; // 0 entrando, 1 dentro , 2 saliendo
	cout<<"POSIC INICIALIZADA"<<endl;
}

void Posicion::iniDirecciones(){
	dirH = ((int)numAleatorio(-5, 5));
	dirV = ((int)numAleatorio(-5, 5));
	posHC = ((int)numAleatorio(-7, 7));
	posVC = ((int)numAleatorio(-7, 7));
	int variacionPosX = ((int)numAleatorio(-80, 80));
	int variacionPosY = ((int)numAleatorio(-80, 80));
	bool centroHActivo = false;
	if(dirH>0){ // mover derecha H
		if(posHC > 0){	// comenzar cerca de centro x
			x = LIMITE_H/2;
			centroHActivo = true;
			x += variacionPosX;
		}else{
			x = 0;
			x -= POSIC_FUERA;
			x += variacionPosX;
		}
	}else{
		if(posHC > 0){
			x = LIMITE_H/2;
			centroHActivo = true;
			x += variacionPosX;
		}else{
			x = LIMITE_H;
			x += POSIC_FUERA;
			x -= variacionPosX;
		}
	}
	// - Direccion Y -
	if(dirV>0 && centroHActivo){ // entrar hacia abajo con x en centro
		y = 0;
		y -= POSIC_FUERA;
		y += variacionPosY;
	}else if(dirV<=0 && centroHActivo){ // entrar hacia arriba con x en centro
		y = LIMITE_V;
		y += POSIC_FUERA;
		y -= variacionPosY;
	}else if(dirV>0){ // entrar hacia abajo desde  x en 0 , ó , x en POSIC_FUERA
		if(posVC > 0){ // hacia abajo con Y cerca de centro vertical
			y = LIMITE_V/2;
			y += variacionPosY;
		}else{			// hacia abajo desde cero
			y = 0;
			y -= POSIC_FUERA;
			y += variacionPosY;
		}
	}else if(dirV<=0){ // entrar hacia arriba desde  x en 0 , ó , x en POSIC_FUERA
		if(posVC > 0){	// hacia arriba con Y cerca de centro vertical
			y = LIMITE_V/2;
			y += variacionPosY;
		}else{			// hacia arriba desde limite_v
			y = LIMITE_V;
			y += POSIC_FUERA;
			y -= variacionPosY;
		}
	}
}


// Mover el centro del asteroiode con base en su direccion ya definida
void Posicion::mueve(double desplazamiento){
	if(dirH>0){
		x += desplazamiento; 
	}
	else{
		x -= desplazamiento;
	}
	if(dirV>0) {
		y += desplazamiento;
	}
	else {
		y -= desplazamiento;
	}
}

// true si el asteroide sale por algun lado
bool Posicion::verificarLugar(){
	bool psx = false, psy = false , res = false;
	if( (x >= (LIMITE_H + POSIC_FUERA)) ||  (x <= (0 - POSIC_FUERA)) ){ //fuera en x
		psx = true;
	}
	if( (y >= (LIMITE_V + POSIC_FUERA)) ||  (y <= (0 - POSIC_FUERA)) ){ // fuera en y
		psy = true;
	}

	res = psx && psy;
	if(res == false && posEnVentana == 0){
		posEnVentana = 1;
	}else if(res == true && posEnVentana == 1){
		posEnVentana = 2;
	}

	if(posEnVentana == 2) {nuevaPosicion(); return true; } else {return false;}
}



double Posicion::getX(){
	return x;
}

double Posicion::getY(){
	return y;
}


double Posicion::numAleatorio(double n, double m){
    return rand()*(1.0/RAND_MAX)*(m-n) + n;
}


