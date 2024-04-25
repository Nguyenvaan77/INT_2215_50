/*#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
#include"TIMER.h"
#include"TEXT.h"
#include"score.h"
#include"boder.h"
#include"MENU.h"

using namespace std;

int index_wingame;

SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Surface* ICON = NULL;


baseObject backGround;
baseObject nhanESC;

TTF_Font* font_score = NULL;


bool setBack()
{
	bool ok = true;
	backGround.loadImg("anh//BACKGROUND//backclone.bmp", screen);

	if (backGround.getObject() == NULL)
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

			if (font_score == NULL)
			{

				success = false;
			}
		}
	}

	return success;
}// HÀM INIT,CREATE,SET RENDERER

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

	{

	home:
		MENUGAME menu;
		int click = menu.setupMenu(screen);

		switch (click)
		{
		case 0: goto OUTGAME;       break;
		case 1: goto gameMode;      break;
		case 2: goto directionGame; break;
		case 3: goto OUTGAME;       break;
		default:
			break;
		}
	}



	{

	gameMode:

		MODECHOISEGAME modechoise;
		int clickMode = modechoise.setupMODECHOISE(screen);
		switch (clickMode)
		{
		case 0: goto OUTGAME;  break;
		case 1: goto PlayGame; break;
		case 2: goto PlayGame2player; break;
		case 3: goto home;     break;
		default:
			break;
		}
	}

	//khi menu.setupMenu(screen) ==  1
	{

	PlayGame:

		bool quit = false;
		SDL_Event even;
		SCORE scoreG;// class score

		scoreG.openFileScore();
		scoreG.SetColor(SCORE::WHITE_TEXT);

		snake ran(1);

		food cake;
		cake.loadImg("anh//FOOD//apple.bmp", screen);
		cake.setup_and_render(screen);

		bool pausingGame = false;

		TIME thoigian;
		while (!quit)
		{


			thoigian.start();


			bool eaten = false;
			while (SDL_PollEvent(&even))
			{
				if (even.type == SDL_QUIT)
				{
					quit = true;// KHÔNG QUAN TRỌNG						
					goto OUTGAME;
				}
				if (even.type == SDL_KEYDOWN)
				{

					ran.handleInput(even);
					if (ran.dangDichuyen()) { pausingGame = false; };
					if (even.key.keysym.sym == SDLK_ESCAPE)
					{
						ran.dichuyen(false);
						pausingGame = true;
					}

				}


			}



			if (!ran.isAlive())
			{
				cout << "chet" << endl;

				scoreG.newHighest();



				goto losPlayer1;
			}


			if (ran.dangDichuyen())
			{
				ran.xulyDichuyen(ran.dangDichuyen());

				if (ran.eatFood(cake.getRect()))
				{
					eaten = true;
					ran.addTail();
					scoreG.updateScore();

					cake.setupAgain1P(screen, ran);
					cout << "EAT FOOD" << endl;
				}


				ran.updateTail(screen);

			}



			SDL_RenderClear(screen);


			backGround.render(screen, NULL);
			ran.renderShit(screen);
			ran.showfullbodysnake(screen, cake.getRect());
			cake.render(screen, &cake.rect_);

			if (pausingGame)
			{
				SDL_Rect rPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
				nhanESC.render(screen, &rPause);
			}



			scoreG.SCORE_to_STRING();
			scoreG.LoadFromRenderText(font_score, screen);
			scoreG.RenderText(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2, true);// Căn chỉnh ô điểm vào chính giữa phần đen , kích cỡ ô đen là 5* tile_mat 

			if (scoreG.checkWIN())
			{
				if (scoreG.checkWIN())
				{
					goto winPlayer1;
				}
			}

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

		{
		losPlayer1://khi thua se den day

			SCREEN_WIN_GAME wingame;
			wingame.setDiem(scoreG.finalScore(), font_score);
			cout << scoreG.finalScore() << endl;
			cout << "losPlayer1" << endl;
			int click_win_game = wingame.setupGAMEOK(screen, 0, font_score);//0 la thua khi choi 1player
			scoreG.resetScore();
			switch (click_win_game)
			{
			case 0: goto OUTGAME; break;

			case 1: goto PlayGame; break;//nut replay-> playgame

			case 2: goto home;     break;// nut home-> manhinhchinh home

			case 3: goto gameMode; break;//nut back -> gamemode

			default: break;
			}
		}

		{
		winPlayer1://khi thua se den day

			SCREEN_WIN_GAME wingame;

			int click_win_game = wingame.setupGAMEOK(screen, 4, font_score);//0 la thua khi choi 1player

			switch (click_win_game)
			{
			case 0: goto OUTGAME; break;

			case 1: goto PlayGame; break;//nut replay-> playgame

			case 2: goto home;     break;// nut home-> manhinhchinh home

			case 3: goto gameMode; break;//nut back -> gamemode

			default: break;
			}
		}

	}


	{
	PlayGame2player:

		bool quit = false;
		SDL_Event even;
		snake ran1(1);
		snake ran2(2);



		baseObject loadOk;
		loadOk.loadImg("anh//button//ready.bmp", screen);

		food cake;
		cake.loadImg("anh//FOOD//apple.bmp", screen);
		cake.setup_and_render(screen);

		TIME thoigian;
		bool pausing = false;



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
					goto OUTGAME;
				}
				if (even.type == SDL_KEYDOWN)
				{


					ran1.handleInput(even);
					ran2.handleInput(even);



					if (even.key.keysym.sym == SDLK_ESCAPE)
					{
						ran1.dichuyen(false);
						ran2.dichuyen(false);
						pausing = true;
					}
				}

			}

			if (ran1.dangDichuyen() && ran2.dangDichuyen()) { cout << 1 << endl; pausing = false; };





			if (!ran1.isAlive() || !ran2.isAlive())
			{

				if (!ran1.isAlive() && !ran2.isAlive())
				{
					index_wingame = 3;//tie thi 3
				}
				else
				{
					if (!ran1.isAlive())
					{
						index_wingame = 2;// p2 win thi 2
					}
					if (!ran2.isAlive())
					{
						index_wingame = 1;//p1 win thi 1
					}
				}
				goto win;
			}


			if (ran1.dangDichuyen() && ran2.dangDichuyen())
			{
				ran1.xulyDichuyen(ran1.dangDichuyen());
				ran2.xulyDichuyen(ran2.dangDichuyen());

				if (ran1.eatFood(cake.getRect()))
				{
					eaten = true;
					ran1.addTail();

					cake.setupAgain1P(screen, ran1);

				}
				if (ran2.eatFood(cake.getRect()))
				{
					eaten = true;
					ran2.addTail();

					cake.setupAgain1P(screen, ran2);

				}


				ran1.updateTail(screen);
				ran2.updateTail(screen);

			}


			SDL_RenderClear(screen);

			backGround.render(screen, NULL);
			ran1.renderShit(screen);
			ran2.renderShit(screen);
			ran1.showfullbodysnake(screen, cake.getRect());
			ran2.showfullbodysnake(screen, cake.getRect());
			cake.render(screen, &cake.rect_);

			if ((ran1.dangDichuyen() && !ran2.dangDichuyen()) || (!ran1.dangDichuyen() && ran2.dangDichuyen()))
			{
				if (ran1.dangDichuyen())
				{
					loadOk.setRect(ran1.getRectHEAD().x, ran1.getRectHEAD().y - loadOk.getRect().h);
					SDL_Rect imgOK = loadOk.getRect();
					loadOk.render(screen, &imgOK);
				}
				if (ran2.dangDichuyen())
				{
					loadOk.setRect(ran2.getRectHEAD().x, ran2.getRectHEAD().y - loadOk.getRect().h);
					SDL_Rect imgOK = loadOk.getRect();
					loadOk.render(screen, &imgOK);
				}
			}

			if (pausing)
			{

				SDL_Rect rPause = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
				nhanESC.render(screen, &rPause);
			}




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

	{
	win:
		SCREEN_WIN_GAME wingame;
		int click_win_game = wingame.setupGAMEOK(screen, index_wingame, font_score);//1 : p1 win, 2: p2 win, 3: tie
		switch (click_win_game)
		{
		case 0: goto OUTGAME; break;

		case 1: goto PlayGame2player; break;

		case 2: goto home;     break;

		case 3: goto gameMode; break;

		default: break;
		}
	}

	{//hientai chua dung den
	los://khi thua se den day
		SCREEN_WIN_GAME wingame;
		int click_win_game = wingame.setupGAMEOK(screen, 0, font_score);//0 la thua khi choi 1player
		switch (click_win_game)
		{
		case 0: goto OUTGAME; break;

		case 1: goto PlayGame; break;//nut replay-> playgame

		case 2: goto home;     break;// nut home-> manhinhchinh home

		case 3: goto gameMode; break;//nut back -> gamemode

		default: break;
		}
	}


	{

	directionGame:// Huong dan choi game 

		INDIRECTIONGAME inforG;
		int clickIndirect = inforG.setupINDIRECTION(screen);
		if (clickIndirect)
		{
			goto home;
		}
		else
		{
			goto OUTGAME;
		}

	}

OUTGAME:
	close();
	return 0;
}
*/