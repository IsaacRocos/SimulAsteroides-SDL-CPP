#ifndef _POSICION_H_
#define _POSICION_H_
#define LIMITE_H  800.0
#define LIMITE_V  600.0	
#define POSIC_FUERA 50.0  // el asteroide puede generarse hasta 150px fuera de la ventana

class Posicion{
	public:
		Posicion();
		double getX();
		double getY();
		bool dentroVentana();
		void nuevaPosicion();
		void iniDirecciones();
		double numAleatorio(double n, double m);
		void mueve(double);
		bool verificarLugar();
	private:
		double sentido;
		int    dirH;
		int    dirV;
		int    posHC; // para determinar posicion centrada en x o y
		int    posVC; // para determinar posicion centrada en x o y
		double x;
		double y;
		short  posEnVentana; // 0 entrando, 1 dentro , 2 saliendo
};

#endif
