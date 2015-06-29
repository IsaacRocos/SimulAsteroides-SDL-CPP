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
	modificadorDirX = 1;
	modificadorDirY = 1;
	iniDirecciones();
	posEnVentana = 0; // 0 entrando, 1 dentro , 2 saliendo
	cout<<"POSIC INICIALIZADA"<<endl;
}

void Posicion::iniDirecciones(){
	dirH = ((int)numAleatorio(-5, 8));
	dirV = ((int)numAleatorio(-10, 9));
	posHC = ((int)numAleatorio(-7.9, 5));
	posVC = ((int)numAleatorio(-7.2, 6));
	int variacionPosX = ((int)numAleatorio(-120, 130));
	int variacionPosY = ((int)numAleatorio(-150, 104));
	bool centroHActivo = false; // si un asteroide se genera en elcentro de x, no puede hacerlo en el centro de y
	// - Direccion X -
	if(dirH>0){ // mover derecha H
		if(posHC > 0){	// comenzar cerca de centro x
			x = LIMITE_H/2;
			centroHActivo = true;
			x += numAleatorio(-380,380); // mover por el centro
			if(x>LIMITE_H-200 || (x>0 && x<200)){
				modificadorDirY = 0;
			}
			cout<<"[X]Derecha/Centro->"<<endl;
		}else{
			x = 0;
			x -= POSIC_FUERA;
			x += variacionPosX;
			cout<<"[X]<-Derecha/Limite 0->"<<endl;
		}
	}else{
		if(posHC > 0){
			x = LIMITE_H/2;
			centroHActivo = true;
			x += numAleatorio(-380,380);
			if(x>LIMITE_H-200 || (x>0 && x<200)){
				modificadorDirY = 0;
			}
			cout<<"[X]<-Izquierda/Centro"<<endl;
		}else{
			x = LIMITE_H;
			x += POSIC_FUERA;
			x -= variacionPosX;
			cout<<"[X]<-Izquierda/LimiteH"<<endl;
		}
	}
	// - Direccion Y -
	if(dirV>0 && centroHActivo){ // entrar hacia abajo con x en centro
		y = 0;
		y -= POSIC_FUERA;
		y += variacionPosY;
		cout<<"[Y]Abajo/Limite0"<<endl;
	}else if(dirV<=0 && centroHActivo){ // entrar hacia arriba con x en centro
		y = LIMITE_V;
		y += POSIC_FUERA;
		y -= variacionPosY;
		cout<<"[Y]Arriba/LimiteV"<<endl;
	}else if(dirV>0){ // entrar hacia abajo desde  x en 0 , ó , x en POSIC_FUERA
		if(posVC > 0){ // hacia abajo con Y cerca de centro vertical
			y = LIMITE_V/2;
			y += numAleatorio(-250,250);
			if(y>LIMITE_V-200 || (y>0 && y<200)){
				modificadorDirY = 0;
			}
			cout<<"[Y]Abajo/Centro"<<endl;
		}else{			// hacia abajo desde cero
			y = 0;
			y -= POSIC_FUERA;
			y += variacionPosY;
			cout<<"[Y]Abajo/Limite0"<<endl;
		}
	}else if(dirV<=0){ // entrar hacia arriba desde  x en 0 , ó , x en POSIC_FUERA
		if(posVC > 0){	// hacia arriba con Y cerca de centro vertical
			y = LIMITE_V/2;
			y += numAleatorio(-250,250);
			if(y>LIMITE_V-200 || (y>0 && y<200)){
				modificadorDirY = 0;
			}
			cout<<"[Y]Ariba/Centro"<<endl;
		}else{			// hacia arriba desde limite_v
			y = LIMITE_V;
			y += POSIC_FUERA;
			y -= variacionPosY;
			cout<<"[Y]Arriba/LimiteV"<<endl;
		}
	}
}


// Mover el centro del asteroiode con base en su direccion ya definida
void Posicion::mueve(double desplazamiento){
	if(dirH>0){
		x += desplazamiento * modificadorDirX; 
	}
	else{
		x -= desplazamiento * modificadorDirX;
	}
	if(dirV>0) {
		y += desplazamiento * modificadorDirY;
	}
	else {
		y -= desplazamiento * modificadorDirY;
	}
}

// Para verificar en qué parte se encuentra el asteroide
// 0 generado fuera, 1 entrando , 2 dentro, 3 fuera
// true si el asteroide sale por algun lado
bool Posicion::verificarLugar(){
	bool psx = false, psy = false , res = false;
	if( (x >LIMITE_H || x < 0) && (y >LIMITE_V || y < 0) ){ //fuera de ventana
		if(posEnVentana == 0){
			posEnVentana = 1; // significa que el asteroide está entrando
		}
	}else if( (x > 0) && (y < 0 || y > LIMITE_V) ){ //fuera de ventana x centro
		if(posEnVentana == 0){
			posEnVentana = 1; // significa que el asteroide está entrando
		}
	}else if( (y > 0) && (x >LIMITE_H || x < 0) ){ //fuera de ventana y Y centro 
		if(posEnVentana == 0){
			posEnVentana = 1; // significa que el asteroide está entrando
		}
	}

	if ( (x>-100 && x<=LIMITE_H-100) && ( y>-100 && y<LIMITE_V-100)){
		posEnVentana = 2; // asteroide dentro
	}

	if ( ( x<=(0-POSIC_FUERA) || x>=(LIMITE_H+POSIC_FUERA) ) || ( y<=(0-POSIC_FUERA) || y>=(LIMITE_V+POSIC_FUERA) ) ){
		if(posEnVentana == 2){
			posEnVentana = 3; // fuera
			cout<<"[AF]"<<endl;
		}
	}

	if(posEnVentana == 3) {cout<<"[AF]"<<endl; return true; } else {return false;}
}


int Posicion::getDirH(void){
	return dirH;
}

int Posicion::getDirV(void){
	return dirV;
}

int Posicion::setDirH(int ndirH){
	dirH = ndirH;
}

int Posicion::setDirV(int ndirV){
	dirV = ndirV;
}


double Posicion::getX(){
	return x;
}

double Posicion::getY(){
	return y;
}

int Posicion::getPosicionEnVentana(){
	return posEnVentana;
}

double Posicion::numAleatorio(double n, double m){
    return rand()*(1.0/RAND_MAX)*(m-n) + n;
}


