#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
#include"TIMER.h"
#include"TEXT.h"
#include"score.h"
#include"boder.h"
#include"MENU.h"

using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Surface* ICON = NULL;

baseObject hoa1, hoa2, hoa3;
baseObject backGround;
baseObject nhanESC;
baseObject loss;
baseObject howplay;//huong dan choi
baseObject reDo;//quay tro lai

TTF_Font* font_score = NULL;
TTF_Font* highest = NULL;

bool setBack()
{
	bool ok = true;
	backGround.loadImg("anh//BACKGROUND//backclone.bmp", screen);
	

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
	nhanESC.loadImg("anh//BACKGROUND//pauseok.bmp", screen);
	SDL_Rect recPause = { SCREEN_WIDTH / 6 ,SCREEN_HEIGHT / 6,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	
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
			font_score = TTF_OpenFont(FONT_.c_str(), SIZE_FONT);
			highest = TTF_OpenFont(FONT_.c_str(), SIZE_FONT);
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
	

	MENUGAME menu;
	
	home:

	int click = menu.setupMenu(screen);

	if (click ==0|| click == 3)
	{
		close();
		return 0;
	}
	else
	{
		if (click == 2)
		{
			howplay.loadImg("anh//button//indirectionGame.bmp", screen);
			howplay.render(screen, NULL);
			SDL_Event evenForbackButton;
			bool quit = false;
			bool control_in_back = false;
			while (!quit)
			{
				while(SDL_PollEvent(&evenForbackButton))
				{
					if (evenForbackButton.type == SDL_QUIT)
					{
						goto out;
					}
					if (evenForbackButton.type == SDL_MOUSEMOTION)
					{
						if (evenForbackButton.motion.x <=150 && evenForbackButton.motion.x >= 0 && evenForbackButton.motion.y >= 0 && evenForbackButton.motion.y <= 150)//tự chọn vị trí cho nút PLAY 
						{
							control_in_back = true;
						}
						else
						{
							control_in_back = false;
						}
					}
					if (evenForbackButton.type == SDL_MOUSEBUTTONDOWN)
					{
						if (evenForbackButton.button.button == SDL_BUTTON_LMASK)
						{
							int x, y;
							Uint32 h = SDL_GetMouseState(&x, &y);
							if (x <= 150 && x >= 0 && y >= 0 && y <= 150)
							{
								goto home;
							}
						}
					}
				}
				SDL_Rect rect_for_backbut = { 0,0,150,150 };
				if (control_in_back)
				{
					reDo.loadImg("anh//button//back1.bmp", screen);
				}
				else
				{
					reDo.loadImg("anh//button//back2.bmp", screen);
				}
				reDo.render(screen, &rect_for_backbut);
				SDL_RenderPresent(screen);
				SDL_Delay(90);
			}
		}
		else//khi menu.setupMenu(screen) ==  1
		{

		CHOILAI:



			bool quit = false;
			SDL_Event even;
			SCORE scoreG;// class score

			scoreG.openFileScore();
			scoreG.SetColor(SCORE::WHITE_TEXT);

			snake ran(screen);
			

			cake.loadImg("anh//FOOD//apple.bmp", screen);
			cake.setup_and_render(screen);

			bool pausingGame = false;

			TIME thoigian;
			while (!quit)
			{
				bool gohome = false;
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

						ran.handleInput(even);
						if (even.key.keysym.sym == SDLK_ESCAPE)
						{
							ran.dichuyen(false) ;
							pausingGame = true;
						}
						if (even.key.keysym.sym == SDLK_y)
						{
							rePlay = true;
						}
						if (even.key.keysym.sym == SDLK_h)
						{
							gohome = true;
						}
					}


				}



				if (!ran.isAlive())
				{
					cout << "chet" << endl;

					scoreG.newHighest();
					if (rePlay)
					{
						scoreG.resetScore(rePlay);
						goto CHOILAI;
					}
					if (gohome)
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
					cake.setupAgain1P(screen, ran);
					cout << "EAT FOOD" << endl;
				}

				if (ran.dangDichuyen())
				{
					ran.updateTail(screen);
				}
			los:


				SDL_RenderClear(screen);


				backGround.render(screen, NULL);
				ran.renderShit(screen);
				ran.showfullbodysnake(screen, cake.getRect());
				cake.render(screen, &cake.rect_);

				if (!ran.dangDichuyen())
				{
					SDL_Rect rPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
					nhanESC.render(screen, &rPause);
				}



				scoreG.SCORE_to_STRING();
				scoreG.LoadFromRenderText(font_score, screen);
				scoreG.RenderText(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2);// Căn chỉnh ô điểm vào chính giữa phần đen , kích cỡ ô đen là 5* tile_mat 


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
		}
	}
    out:
	close();
	return 0;
}
