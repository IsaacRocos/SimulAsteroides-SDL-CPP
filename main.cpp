#include "Game.h"
using namespace std;

int main(int argc, char **argv) {
	int nAsteroides = 10;
	if(argc < 2){
      cout << "Ejecutando para " << nAsteroides <<  " Asteroides\n";
	}else{
	   	nAsteroides = atoi(argv[1]);
	   	cout << "Ejecutando para " << nAsteroides <<  " Asteroides\n";
   	}

	Game g("Asteroides",0,0,800,600,nAsteroides);
	while(g.getRunning()) {
		g.manejaEventos();
	 	g.update();
	 	g.render();
	}
}//main
