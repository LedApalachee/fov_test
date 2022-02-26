#include <stdio.h>
#include <stdlib.h>
#include <handleline.h>


#define char_floor '.'
#define char_wall '#'
#define char_unseenable ' '


#define mapsizeX 11
#define mapsizeY 11
char map[mapsizeX][mapsizeY];


#define rendersizeX (mapsizeX + 3)
#define rendersizeY (mapsizeY + 2)
char render[rendersizeX * rendersizeY + 1];


int cameraX, cameraY;
int putwallX, putwallY;


void init_map();
void init_render();
void update_render();
char render_get_char(int x, int y);
void render_set_char(int x, int y, char ch);


long long int handle_tile(int x, int y)
{
	render_set_char(x+1, y+1, map[x][y]);
	if (map[x][y] == char_wall) return 1;
}


int main(int argc, char** argv)
{
	init_map();
	cameraX = putwallX = mapsizeX/2;
	cameraY = putwallY = mapsizeY/2;
	init_render();

	char quit = 0;
	while (!quit)
	{
		update_render();
		printf("%s\n", render);
		switch (getchar())
		{
			case 'q':
				quit = 1;
				break;

			case 'f':
				map[putwallX][putwallY] = char_wall;
				break;

			case 'j':
				map[putwallX][putwallY] = char_floor;
				break;

			case 's':
				if (cameraY < mapsizeY-1) ++cameraY;
				break;

			case 'w':
				if (cameraY > 0) --cameraY;
				break;

			case 'a':
				if (cameraX > 0) --cameraX;
				break;

			case 'd':
				if (cameraX < mapsizeX-1) ++cameraX;
				break;

			case '2':
				if (putwallY < mapsizeY-1) ++putwallY;
				break;

			case '8':
				if (putwallY > 0) --putwallY;
				break;

			case '4':
				if (putwallX > 0) --putwallX;
				break;

			case '6':
				if (putwallX < mapsizeX-1) ++putwallX;
				break;
		}
	}

	return 0;
}




void init_map()
{
	for (int x = 0; x < mapsizeX; ++x)
		for (int y = 0; y < mapsizeY; ++y)
			map[x][y] = char_floor;
}




void init_render()
{
	for (int y = 0; y < rendersizeY; ++y)
	{
		render_set_char(0, y, '|');
		render_set_char(rendersizeX-2, y, '|');
		render_set_char(rendersizeX-1, y, '\n');
	}

	for (int x = 0; x < rendersizeX-1; ++x)
	{
		render_set_char(x, 0, '-');
		render_set_char(x, rendersizeY-1, '-');
	}

	for (int x = 1; x < rendersizeX-2; ++x)
		for (int y = 1; y < rendersizeY-1; ++y)
			render_set_char(x,y, char_unseenable);

	render_set_char(cameraX+1, cameraY+1, '@');

	render[rendersizeX * rendersizeY] = '\0';
}


void update_render()
{
	for (int x = 1; x < rendersizeX-2; ++x)
		for (int y = 1; y < rendersizeY-1; ++y)
			render_set_char(x,y, char_unseenable);
	for (int x = 0; x < mapsizeX; ++x)
	{
		handleline(cameraX, cameraY, x, mapsizeY-1, &handle_tile);
		handleline(cameraX, cameraY, x, 0, &handle_tile);
	}
	for (int y = 0; y < mapsizeY; ++y, &handle_tile)
	{
		handleline(cameraX, cameraY, 0, y, &handle_tile);
		handleline(cameraX, cameraY, mapsizeX-1, y, &handle_tile);
	}
	render_set_char(cameraX+1, cameraY+1, '@');
	render_set_char(putwallX+1, putwallY+1, '?');
}


char render_get_char(int x, int y)
{
	if (x < 0 || x >= rendersizeX || y < 0 || y >= rendersizeY) return 0;
	return render[rendersizeX * y + x];
}


void render_set_char(int x, int y, char ch)
{
	if (x < 0 || x >= rendersizeX || y < 0 || y >= rendersizeY) return;
	render[rendersizeX * y + x] = ch;
}