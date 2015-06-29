#ifndef _POSICION_H_
#define _POSICION_H_
#define LIMITE_H  800.0
#define LIMITE_V  600.0	
#define POSIC_FUERA 200.0  // el asteroide puede generarse hasta POSIC_FUERA px fuera de la ventana

class Posicion{
	public:
		Posicion(void);
		double getX(void);
		double getY(void);
		double numAleatorio(double n, double m);
		void   nuevaPosicion(void);
		void   iniDirecciones(void);
		void   mueve(double);
		bool   dentroVentana(void);
		bool   verificarLugar(void);
		int    getDirH(void);
		int    getDirV(void);
		int    setDirH(int);
		int    setDirV(int);
		int    getPosicionEnVentana(void);
	private:
		int    dirH;  // Movimiento derecha izquierda
		int    dirV;  // Movimiento Arriba o abajo
		int    posHC; // para determinar posicion centrada en x o y
		int    posVC; // para determinar posicion centrada en x o y
		int	   modificadorDirX;
		int    modificadorDirY;
		double sentido;
		double x;     // posicion  x centro
		double y;	  // posicion  y centro
		short  posEnVentana; // 0 generado, 1 entrando , 2 dentro, 3 fuera
};

#endif
