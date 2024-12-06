#include "checkML.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Tilemap.h"
#include "Game.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

Tilemap::Tilemap(Game* g, std::istream& in, Point2D<double> p, Texture* t)
	: SceneObject(g, p, t)
{
	load(in);
}

Tilemap::~Tilemap()
{

}

void Tilemap::load(std::istream& file)
{
	std::ifstream archivo("../assets/maps/world" + to_string(game->getCurrentLevel()) + ".csv");
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo" << std::endl;
		return;
	}

	std::string linea;
	while (std::getline(archivo, linea)) {
		std::vector<int> fila;
		std::stringstream ss(linea);
		std::string valor;

		while (std::getline(ss, valor, ',')) {
			fila.push_back(std::stoi(valor));
		}

		indices.push_back(fila);
	}

	archivo.close();
}

void Tilemap::render()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = game->getMapOffset() / game->TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = int(game->getMapOffset() % game->TILE_SIDE);

	// tamaño del cuadro a pintarse
	SDL_Rect rect;
	rect.w = game->TILE_SIDE;
	rect.h = game->TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < game->WIN_WIDTH + 1; ++i)
	{
		for (int j = 0; j < game->WIN_HEIGHT; ++j)
		{
			// indice en el conjunto de patrones de la matriz de ?ndices
			int indice = indices[j][i + x0];

			// Separa numero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * game->TILE_SIDE;
			rect.y = j * game->TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			texture->renderFrame(rect, fy, fx);
		}
	}
}

void Tilemap::update() { }

Collision Tilemap::hit(SDL_Rect rect, Collision::Target t) {

	Collision c; // Inicializa una instancia de Collision

	// Calcula las celdas del nivel que contienen las esquinas del rectángulo
	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / game->TILE_SIDE;
	int col0 = rect.x / game->TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / game->TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / game->TILE_SIDE;

	//ajuste para que no pete
	row0 = max(0, row0);
	row1 = min(static_cast<int>(indices.size()) - 1, row1);
	col0 = max(0, col0);
	col1 = min(static_cast<int>(indices[0].size()) - 1, col1);

	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col)
		{
			int index = indices[row][col];

			// Verifica si hay colisión con un obstáculo 
			if (index != -1 && index % texture->getNumColumns() < game->OBSTACLE_THRESHOLD) // ESTO CONFIRMA COLISION
			{
				//cout << "col";
				SDL_Rect colRect{
					col * game->TILE_SIDE,
					row * game->TILE_SIDE,
					game->TILE_SIDE,
					game->TILE_SIDE
				};

				// Calculamos la interseccion
				if (SDL_IntersectRect(&rect, &colRect, &c.intersection))
				{
					c.result = Collision::OBSTACLE; // el resultado sera obstacle porque el tilemap no hace damage
					c.horizontal = c.intersection.w;
					c.vertical = c.intersection.h;
					return c;
				}
			}
		}
	}

	return c; // Retorna la instancia sin colisión si no encontró obstáculos
}

void Tilemap::manageCollisions(Collision c)
{
}

SceneObject* Tilemap::clone() const
{
	return new Tilemap(*this);
}