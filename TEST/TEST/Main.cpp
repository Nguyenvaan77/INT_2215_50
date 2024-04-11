#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
using namespace std;



SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;

baseObject food;

void close() { //closes everything properly
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void game_Screen() { //creates the game surface and the render as wll
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			screen = SDL_CreateRenderer(window, -1, 0);
		}
	}
}// HÀM INIT,CREATE,SET RENDERER



int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();
	bool quit = false;
	SDL_Event even;
	snake ran;
	ran.setIMGforIterm(screen);
	while (!quit)
	{
		while (SDL_PollEvent(&even))
		{
			if (even.type == SDL_QUIT)
			{
				quit = true;
			}
			if (even.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				Uint32 state = SDL_GetMouseState(&x, &y);
				cout << x << " " << y << endl;
			}
			if (even.type == SDL_KEYDOWN)
			{
				ran.handleInput(even);
				ran.updateTail(screen);
				ran.inHEAD();
			}		
		}
		SDL_RenderPresent(screen);
	}
	
	
	close();
	
	return 0;
}
