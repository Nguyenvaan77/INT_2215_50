#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
#include"TIMER.h"
using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;

baseObject backGround;
baseObject nhanESC;
baseObject loss;


void randomRec(SDL_Rect& recc)
{
	recc = { (rand() % 36) * 30,(rand() % 30) * 30,30,30 };
}

bool setBack()
{
		bool ok = true;
		backGround.loadImg("anh//BACKGROUND//backxanh.bmp", screen);
		backGround.render(screen, NULL);
		if (backGround.getObject() == NULL)
		{
			ok = false;
		}
		return ok;
}

bool setPause()
{
	bool ok = true;
	nhanESC.loadImg("anh//BACKGROUND//pause.bmp", screen);
	SDL_Rect recPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	nhanESC.render(screen, &recPause);
	if (nhanESC.getObject() == NULL)
	{
		ok = false;
	}
	return ok;
}

bool setLoss()
{
	bool ok = true;
	loss.loadImg("anh//BACKGROUND//loss.bmp", screen);
	loss.render(screen, NULL);
	if (loss.getObject() == NULL)
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

 food cake;
 food chanh;
 baseObject doc;
 baseObject ngang;
int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();
	home:
	if (!setBack())
	{
		cout << "Load BACKGROUND ERROR" << endl;
	};
	doc.loadImg("anh//BODER//doc.bmp", screen);
	ngang.loadImg("anh//BODER//ngang.bmp", screen);
	SDL_Rect recdoc = { 0,0,40,960 };
	bool quit = false;
	SDL_Event even;

	snake ran(screen);
	cake.loadImg("anh//FOOD//food.bmp", screen);
	cake.setup_and_render(screen);
	TIME thoigian;
	while (!quit)
	{
		bool rePlay = false;
		thoigian.start();
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
					if (even.key.keysym.sym == SDLK_y)
					{
						rePlay = true;
					}
				}
				
				
			}
			if (!ran.isAlive())
			{
				cout << "chet" << endl;
				ran.inScore();
				setLoss();
				if (rePlay)
				{
					goto home;
				}
				goto los;
			}
			ran.xulyDichuyen(ran.dangDichuyen());
			if (ran.eatFood(cake.getRect()))
			{
				eaten = true;
				ran.addTail();
				
				cake.setupAgain(screen);
				cout << "EAT FOOD" << endl;
			}

			if (ran.dangDichuyen())
			{
				ran.updateTail(screen);
			}
			SDL_RenderClear(screen);

			backGround.render(screen, NULL);
			if (!ran.dangDichuyen())
			{
				setPause();

			}
			ran.showfullbodysnake(screen, eaten);
			cake.render(screen, &cake.rect_);
			doc.render(screen, &recdoc);
			los:
		SDL_RenderPresent(screen);

		int real_time = thoigian.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			if (delay_time >= 0)
			{
				SDL_Delay(delay_time);
				cout << "DELAY TIME " << delay_time << endl;
			}
		}

	}
	close();
	
	return 0;
}
