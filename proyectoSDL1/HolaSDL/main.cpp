#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;
using uint = unsigned int;

void firstTest()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My first test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Eventos
		SDL_Event event;

		//Tiempo
		uint32_t startTime, frameTime;
		const int FRAME_RATE = 50;
		const int TIME_PER_FRAME = 100;

		//cesped
		SDL_Surface* sf = IMG_Load("../images/background.png");
		SDL_Texture* tCesped;
		tCesped = SDL_CreateTextureFromSurface(renderer, sf);
		SDL_FreeSurface(sf);

		//perro
		SDL_Surface* sfP = IMG_Load("../images/dog.png");
		SDL_Texture* tPerro;
		tPerro = SDL_CreateTextureFromSurface(renderer, sfP);
		SDL_FreeSurface(sfP);

		SDL_Rect rect_perro;
		rect_perro.x = 0; rect_perro.y = 0;
		rect_perro.w = 768 / 6; rect_perro.h = 82;

		SDL_Rect salida_perro;
		salida_perro.x = 10; salida_perro.y = 400;
		salida_perro.w = 150; salida_perro.h = 100; //salida_perro.w debería ser 100 pero quedaba feo


		//helicoptero
		SDL_Surface* sfH = IMG_Load("../images/helicopter2.png");
		SDL_Texture* tHel;
		tHel = SDL_CreateTextureFromSurface(renderer, sfH);
		SDL_FreeSurface(sfH);

		SDL_Rect rect_hel;
		rect_hel.x = 0; rect_hel.y = 0;
		rect_hel.w = 640 / 5; rect_hel.h = 55;

		SDL_Rect salida_hel;
		salida_hel.x = 700; salida_hel.y = 50;
		salida_hel.w = 200; salida_hel.h = 75;


		//bucle
		bool exit = false;
		bool pause = false;
		while (!exit) {

			startTime = SDL_GetTicks();

			salida_perro.x += 10;
			if (salida_perro.x > int(winWidth)) salida_perro.x = -salida_perro.w;

			//// lo gestionamos en los eventos de teclado
			//salida_hel.x -= 10;
			//if (salida_hel.x < -salida_hel.w) salida_hel.x = int(winWidth);

			
			rect_perro.x = rect_perro.w * int(((SDL_GetTicks() / TIME_PER_FRAME) % 6));
			//rect_hel.x = rect_hel.w * int(((SDL_GetTicks() / TIME_PER_FRAME) % 5));

			SDL_RenderCopy(renderer, tCesped, nullptr, nullptr); //dibujar cesped
			SDL_RenderCopy(renderer, tPerro, &rect_perro, &salida_perro); //dibujar perro
			SDL_RenderCopy(renderer, tHel, &rect_hel, &salida_hel); //dibujar hel
			SDL_RenderPresent(renderer);

			// gestion de eventos 

			while (SDL_PollEvent(&event) && !exit) {
				if (event.type == SDL_QUIT) exit = true; // salir
				else if (event.type == SDL_KEYDOWN) { // evento de teclado
					if (event.key.keysym.sym == SDLK_h) { // pausa helicoptero (tecla h)
						// no está parado -> vamos a pararlo
						if (!pause) {
							pause = true;
							salida_hel.x -= 0; //No avanza
							if (salida_hel.x < -salida_hel.w) salida_hel.x = int(winWidth); //Esto creo que no hace falta, pq está parado

							rect_hel.x = rect_hel.w * int(((SDL_GetTicks()) % 5)); //Para el frame
						}
						// esta parado -> vamos a encenderlo
						else {
							pause = false;
							salida_hel.x -= 10; //Avanza
							if (salida_hel.x < -salida_hel.w) salida_hel.x = int(winWidth); //Sale y entra bien en pantalla

							rect_hel.x = rect_hel.w * int(((SDL_GetTicks() / TIME_PER_FRAME) % 5)); //Cambia el frame

						}
					}
				}
			}

			frameTime = SDL_GetTicks() - startTime;
			if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
		}
		//actualizar imagen
	}
	//SDL_FreeSurface(texture); //BORRAR MEMORIA DINÁMICA
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
