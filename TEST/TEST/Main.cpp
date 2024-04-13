#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;

baseObject backGround;

bool setBack()
{
	bool ok = true;
	backGround.loadImg("anh//back.bmp", screen);
	backGround.render(screen, NULL);
	if (backGround.getObject() == NULL)
	{
		ok = false;
	}
	return ok;
}


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

static food cake;
static food chanh;
int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();
	if (!setBack())
	{
		cout << "Load BACK ERROR" << endl;
		return -1;
	}
	bool quit = false;
	SDL_Event even;
	SDL_Rect rect1 = { 55,55,30,30 };//     mã giả 
	SDL_Rect rect2 = { 200,200,30,30 };//   mã giả 
	cake.loadImg("anh//cake.bmp", screen);
	
	chanh.loadImg("anh//chanh.bmp", screen);
	
	snake ran(screen);
	ran.setIMGforIterm(screen);
	while (!quit)
	{
		//backGround.render(screen, NULL);
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
				ran.addTail();
			}
			if (even.type == SDL_KEYDOWN)
			{
				ran.handleInput(even);
				ran.updateTail(screen);
				if (ran.eatFood())
				{
					rect1.x = (rand() % 20) * 30;
					rect1.y = (rand() % 30) * 30;
					rect2.x = (rand() % 20) * 30;
					rect2.y = (rand() % 30) * 30;
				}
				ran.inHEAD();
			}		
		}
		SDL_RenderClear(screen);
		backGround.render(screen, NULL);
		ran.showfullbody(screen);
		cake.render(screen,&rect1);
		chanh.render(screen, &rect2);
		SDL_RenderPresent(screen);
	}
	
	
	close();
	
	return 0;
}
