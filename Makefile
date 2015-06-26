Main : main.cpp Game.o 
	g++ -std=c++11 main.cpp Game.o   Asteroide.o Vector2D.o Posicion.o -o Proy3Asteroides  -lSDL2

Game.o: Game.cpp Asteroide.o Game.h 
	g++ -std=c++11 Game.cpp Asteroide.o Posicion.o -lSDL2  -c

Asteroide.o: Asteroide.cpp Vector2D.o Posicion.o Asteroide.h 
	g++ -std=c++11 Asteroide.cpp Vector2D.o Posicion.o -lSDL2  -c


Vector2D.o:  
	g++ Vector2D.cpp -c

Posicion.o: Posicion.cpp Posicion.h
	g++ Posicion.cpp -c
