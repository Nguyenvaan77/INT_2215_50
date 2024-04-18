/*#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;

baseObject backGround;


void randomRec(SDL_Rect& recc)
{
	recc = { (rand() % 36) * 30,(rand() % 30) * 30,30,30 };
}

bool setBack(bool ismoving)
{
	if (ismoving)
	{
		bool ok = true;
		backGround.loadImg("anh//BACKGROUND//background.bmp", screen);
		backGround.render(screen, NULL);
		if (backGround.getObject() == NULL)
		{
			ok = false;
		}
		return ok;
	}
	else
	{
		bool ok = true;
		backGround.loadImg("anh//BACKGROUND//pause.bmp", screen);
		SDL_Rect recPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
		backGround.render(screen, &recPause);
		if (backGround.getObject() == NULL)
		{
			ok = false;
		}
		return ok;
	}
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

food cake;
food chanh;
int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();

	bool quit = false;
	SDL_Event even;
	SDL_Rect rec1 = { 60,60,30,30 };



	cake.loadImg("anh//FOOD//food.bmp", screen);

	snake ran(screen);
	ran.setIMGforIterm(screen);
	ran.dichuyen(false);

	if (!setBack(ran.dangDichuyen()))
	{
		cout << "Load BACK ERROR" << endl;
		return -1;
	}
	while (!quit)
	{
		setBack(ran.dangDichuyen());
		bool eaten = false;
		while (SDL_PollEvent(&even))
		{
			if (even.type == SDL_QUIT)
			{
				quit = true;
			}
			if (even.type == SDL_KEYDOWN)
			{
				ran.dichuyen(true);
				ran.handleInput(even);
			}

		}

		ran.xulyDichuyen(ran.dangDichuyen());// r?n d?ng n?u ísMove = false ;

		if (ran.eatFood(rec1))
		{
			cout << "EAT FOOD" << endl;
			randomRec(rec1);// random th?c ?n 
			ran.addTail();
			eaten = true;
		}

		if (ran.dangDichuyen())
		{
			ran.updateTail(screen);
		}
		SDL_RenderClear(screen);
		backGround.render(screen, NULL);
		ran.showfullbodysnake(screen, eaten);

		cake.render(screen, &rec1);

		SDL_RenderPresent(screen);
		SDL_Delay(45);

	}

	close();

	return 0;
}
*/