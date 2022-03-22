// tutorial:
// youtube.com/watch?v=FWSR_7kZuYg

#include "raylib.h"

#include <time.h>

const int maxX = 550;
const int maxY = 550;
const int reso = 50;
const int gridX = maxX/reso;
const int gridY = maxY/reso;

int neighbors_count(int stage[gridX][gridY], int x, int y);

int main(void) {

	// {{{ init
	int stage[gridX][gridY];
	int next[gridX][gridY];

	// preenchendo com valores aleatorios
	time_t t;
	SetRandomSeed((long)&t);
	for(int i = 0; i < gridX; i++) {
		for(int j = 0; j < gridY; j++) {
			next[i][j] = GetRandomValue(0, 1);
		}
	}

	InitWindow(maxX, maxY, "game of life");
	SetTargetFPS(5);
	// }}} init

	while(!WindowShouldClose() && !IsKeyPressed(KEY_Q)) {

		// {{{ proximo estagio
		for(int i = 0; i < gridX; i++) {
			for(int j = 0; j < gridY; j++) {
				stage[i][j] = next[i][j];
			}
		}
		// }}} proximo estagio

		// {{{ draw
		BeginDrawing();

			ClearBackground(BLACK);
			// desenhando o grid
			//for(int i = 0; i < gridX; i++) {
			//	for(int j = 0; j < gridY; j++) {
			//		DrawRectangleLines(i*reso, j*reso, reso, reso, BLACK);
			//	}
			//}

			// desenhando os quadrados
			for(int i = 0; i < gridX; i++) {
				for(int j = 0; j < gridY; j++) {
					if (stage[i][j] == 1) {
						DrawRectangle(i*reso, j*reso, reso-1, reso-1, BLACK);
					} else if (stage[i][j] == 0) {
					  DrawRectangle(i*reso, j*reso, reso-1, reso-1, WHITE);
					 }
				}
			}

		EndDrawing();
		// }}} draw

		// {{{ logica

		// reproducoo -> vizinhos = 3
		// morte -> vizinhos < 2 OR vizinhos > 3
		for(int i = 0; i < gridX; i++) {
			for(int j = 0; j < gridY; j++) {
					int neighbors = neighbors_count(stage, i, j);

					//if(neighbors == 0) {
					//	printf("(%d %d)", i, j);
					//}

					// reproucao
					if(stage[i][j] == 0 && neighbors == 3) {
						next[i][j] = 1;
					// morte
					} else if(stage[i][j] == 1 && (neighbors < 2 || neighbors > 3)) {
						next[i][j] = 0;
					} else {
						next[i][j] = stage[i][j];
					}
					//stage[i][j] = next[i][j];
			}
		}
		// }}} logica

	}
	CloseWindow();
	return 0;
}

int neighbors_count(int stage[gridX][gridY], int x, int y) {
	unsigned short sum = 0, col = 0, row = 0;
	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			col = (x + i + gridX) % gridX;
			row = (y + j + gridY) % gridY;
			sum += stage[col][row];
		}
	}
	sum -= stage[x][y]; // menos eu
	return sum;
}
