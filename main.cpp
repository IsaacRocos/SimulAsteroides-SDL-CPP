#include "Game.h"

int main(int argc, char **argv) {
	Game g("Asteroides",0,0,800,600,10);
	while(g.getRunning()) {
		g.manejaEventos();
	 	g.update();
	 	g.render();
	}
}//main
