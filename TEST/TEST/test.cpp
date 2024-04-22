/*#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
#include"TIMER.h"
#include"TEXT.h"
#include"score.h"
#include"boder.h"


using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Surface* ICON = NULL;

baseObject hoa1, hoa2, hoa3;
baseObject backGround;
baseObject nhanESC;
baseObject loss;
TTF_Font* font_score = NULL;
TTF_Font* highest = NULL;
BODER hangrao;

bool setBack()
{
	bool ok = true;
	backGround.loadImg("anh//BACKGROUND//backok.bmp", screen);
	backGround.render(screen, NULL);// có thể xóa 

	hoa1.loadImg("anh//BACKGROUND//hoa.bmp", screen);
	hoa2.loadImg("anh//BACKGROUND//hoa2.bmp", screen);
	hoa3.loadImg("anh//BACKGROUND//hoa3.bmp", screen);

	if (backGround.getObject() == NULL || hoa1.getObject() == NULL || hoa2.getObject() == NULL || hoa3.getObject() == NULL)
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
	loss.loadImg("anh//BACKGROUND//gameover2.bmp", screen);
	loss.render(screen, NULL);
	if (loss.getObject() == NULL)
	{
		ok = false;
	}
	return ok;
}


void close() { //closes everything properly
	SDL_DestroyRenderer(screen);
	TTF_Quit();
	SDL_FreeSurface(ICON);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


bool game_Screen() { //creates the game surface and the render as wll

	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

		success = false;
	}
	else {
		window = SDL_CreateWindow("SNAKE FIT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

			success = false;
		}
		else {
			screen = SDL_CreateRenderer(window, -1, 0);
			ICON = SDL_LoadBMP("anh//BACKGROUND//icon.bmp");
			SDL_SetWindowIcon(window, ICON);
			font_score = TTF_OpenFont("font//xe.ttf", SIZE_FONT);
			highest = TTF_OpenFont("font//xe.ttf", SIZE_FONT);
			if (font_score == NULL || highest == NULL)
			{

				success = false;
			}
		}
	}

	return success;
}// HÀM INIT,CREATE,SET RENDERER

food cake;
food chanh;

int main(int argc, char* args[])
{
	srand(time(NULL));
	if (!game_Screen())
	{
		cout << "LOAD SCREEN ERROR" << endl;
	}

	if (!setBack())
	{
		cout << "Load BACKGROUND ERROR" << endl;
	};
	if (!setPause())
	{
		cout << "Load PAUSE ERROR" << endl;
	};
	if (!setLoss())
	{
		cout << "LOAD LOSS ERROR" << endl;
	}
	hangrao.setIMG(screen);
home:

	bool quit = false;
	SDL_Event even;
	SCORE scoreG;// class score

	scoreG.openFileScore();


	scoreG.SetColor(TextObject::WHITE_TEXT);



	snake ran(screen);
	cake.loadImg("anh//FOOD//apple.bmp", screen);
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

			loss.render(screen, NULL);
			scoreG.newHighest();
			if (rePlay)
			{
				scoreG.resetScore(rePlay);
				goto home;
			}
			goto los;
		}
		ran.xulyDichuyen(ran.dangDichuyen());
		if (ran.eatFood(cake.getRect()))
		{
			eaten = true;
			ran.addTail();
			scoreG.updateScore();
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
			SDL_Rect rPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
			nhanESC.render(screen, &rPause);
		}
		ran.showfullbodysnake(screen, eaten);
		cake.render(screen, &cake.rect_);
		hangrao.renderBoder(screen);
	los:

		if (scoreG.finalScore() >= 5)
		{
			scoreG.SetColor(TextObject::BLACK_TEXT);
		}
		scoreG.SCORE_to_STRING();


		scoreG.LoadFromRenderText(font_score, screen);
		scoreG.RenderText(screen, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 90);// 30 30 ma gia ko co y nghia trong code nay


		int real_time = thoigian.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;



		SDL_RenderPresent(screen);

		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			if (delay_time >= 0)
			{
				SDL_Delay(delay_time);

			}
		}

	}
	close();

	return 0;
}
*/