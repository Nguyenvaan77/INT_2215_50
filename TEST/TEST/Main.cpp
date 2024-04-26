#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
#include"Food.h"
#include"TIMER.h"
#include"TEXT.h"
#include"score.h"
#include"MENU.h"
using namespace std;

int index_wingame;

enum number_players
{
	oneplayer=1,
	twoplayer=2
};

SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Surface* ICON = NULL;


static Mix_Chunk* sound_eat=NULL;
static Mix_Chunk* sound_win = NULL;
static Mix_Chunk* sound_loss = NULL;
int volume = 100;

baseObject backGround;
baseObject nhanESC;

TTF_Font* font_score = NULL;
TTF_Font* font_time = NULL;

TextObject diemcao;

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
	Mix_FreeChunk(sound_eat); 
	Mix_FreeChunk(sound_click);
	Mix_FreeChunk(sound_bit);
	Mix_FreeChunk(sound_win);
	Mix_FreeChunk(sound_loss);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyRenderer(screen);
	TTF_Quit();
	SDL_FreeSurface(ICON);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool game_Screen() { //creates the game surface and the render as wll

	bool success = true;
	Mix_Init(MIX_INIT_MP3);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0|| Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
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
			font_time= TTF_OpenFont(FONT_.c_str(), SIZE_FONT);
			if (font_score == NULL )
			{
				success = false;
			}

			sound_eat = Mix_LoadWAV("sound//eat.wav");
			sound_click = Mix_LoadWAV("sound//click1.wav");
			sound_bit= Mix_LoadWAV("sound//bonk.wav");
			sound_win= Mix_LoadWAV("sound//win1p.wav");
			sound_loss= Mix_LoadWAV("sound//loss.wav");
			if (sound_eat == NULL || sound_click == NULL || sound_bit == NULL || sound_win == NULL || sound_loss == NULL)
			{
				success = false;
			}
			diemcao.SetColor(203, 36, 111);
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
		Mix_PlayChannel(-1, sound_click, 0);
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
		Mix_PlayChannel(-1, sound_click, 0);
		switch (clickMode)
		{
		case 0: goto OUTGAME;  break;
		case 1: goto PlayGame1player; break;
		case 2: goto PlayGame2player; break;
		case 3: goto home;     break;
		default:
			break;
		}
	}
		//khi menu.setupMenu(screen) ==  1
		{
	    PlayGame1player:
				bool quit = false;
				SDL_Event even;
				SCORE scoreG;// class score

				scoreG.openFileScore();
				scoreG.SetColor(SCORE::WHITE_TEXT);

				diemcao.SetText("Highest score : "+to_string(scoreG.getHIGHESTSCORE()));

				snake ran(oneplayer);

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
							Mix_PlayChannel(-1, sound_eat, 0);
							cake.setupAgain1P(screen, ran);
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
					diemcao.LoadFromRenderText(font_score, screen);
					diemcao.RenderText(screen, 0, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2, true);

					scoreG.SCORE_to_STRING();
					scoreG.LoadFromRenderText(font_score, screen);
					scoreG.RenderText(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2,true);// Căn chỉnh ô điểm vào chính giữa phần đen , kích cỡ ô đen là 5* tile_mat 

					SDL_RenderPresent(screen);

					if (scoreG.checkWIN(oneplayer))
					{
						goto winPlayer1;
					}
					
					int real_time = thoigian.get_ticks();
					int time_one_frame = 1000 / FRAME_PER_SECOND;
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

				    Mix_PlayChannel(-1, sound_loss, 0);

					SCREEN_WIN_GAME wingame;
					wingame.setDiem(scoreG.finalScore(),font_score);
					int click_win_game = wingame.setupGAMEOK(screen, 0,font_score);//0 la thua khi choi 1player
					scoreG.resetScore();
					Mix_PlayChannel(-1, sound_click, 0);
					switch (click_win_game)
					{
					case 0: goto OUTGAME; break;

					case 1: goto PlayGame1player; break;//nut replay-> playgame

					case 2: goto home;     break;// nut home-> manhinhchinh home

					case 3: goto gameMode; break;//nut back -> gamemode

					default: break;
					}
				}

				{
				winPlayer1://khi thua se den day

					Mix_PlayChannel(-1, sound_win, 0);
					SCREEN_WIN_GAME wingame;
		
					int click_win_game = wingame.setupGAMEOK(screen, 4, font_score);//0 la thua khi choi 1player
					Mix_PlayChannel(-1, sound_click, 0);
					switch (click_win_game)
					{
					case 0: goto OUTGAME; break;

					case 1: goto PlayGame1player; break;//nut replay-> playgame

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

		snake ran1(oneplayer);
		snake ran2(twoplayer);

		SCORE score_ran1;
		SCORE score_ran2;

		score_ran1.SetColor(203,36,111);
		score_ran2.SetColor(SCORE::WHITE_TEXT);

		TIME timeFPS;
		TIME time_of_turn_game;
		time_of_turn_game.SetColor(255, 205, 28);
		int time_run_backwards = time_to_win_2players;
		
		baseObject loadOk;
		loadOk.loadImg("anh//button//ready.bmp", screen);

		food cake;
		cake.loadImg("anh//FOOD//apple.bmp", screen);
		cake.setup_and_render(screen);

		
		bool pausing = false;

		

		while (!quit)
		{
			bool gohome = false;
			bool rePlay = false;
			timeFPS.start();
			bool eaten = false;
			time_run_backwards = time_to_win_2players - (int)(time_of_turn_game.get_ticks()) / 1000;
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
						time_of_turn_game.pause();
					}
				}

			}
			
			if (ran1.dangDichuyen() && ran2.dangDichuyen()) 
			{ 
				pausing = false;  
				if (!time_of_turn_game.isStart())
				{
					time_of_turn_game.start();
				}
				time_of_turn_game.unpause();
			};
			if (time_run_backwards >0)
			{
				if (!ran1.isAlive() || !ran2.isAlive())
				{
					Mix_PlayChannel(-1, sound_bit, 0);
					time_of_turn_game.stopGame();
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
			}
			else
			{
				if (score_ran1.finalScore() > score_ran2.finalScore())
				{
					index_wingame = 1;
				}
				else
				{
					if (score_ran1.finalScore() < score_ran2.finalScore())
					{
						index_wingame = 2;
					}
					else
					{
						index_wingame = 3;
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
					score_ran1.updateScore();
					ran1.addTail();
					Mix_PlayChannel(-1, sound_eat, 0);
					cake.setupAgain1P(screen, ran1);
					
				}
				if (ran2.eatFood(cake.getRect()))
				{
					eaten = true;
					score_ran2.updateScore();
					ran2.addTail();
					Mix_PlayChannel(-1, sound_eat, 0);
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

			if ((ran1.dangDichuyen()&&!ran2.dangDichuyen())|| (!ran1.dangDichuyen() && ran2.dangDichuyen()))
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

			score_ran1.SCORE_to_STRINGplayer1();
			score_ran1.LoadFromRenderText(font_score, screen);
			score_ran1.RenderText(screen, 300, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2, true);

			score_ran2.SCORE_to_STRINGplayer2();
			score_ran2.LoadFromRenderText(font_score, screen);
			score_ran2.RenderText(screen, 600, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2, true);

			time_of_turn_game.SetText("Time : "+ to_string(time_run_backwards));
			time_of_turn_game.LoadFromRenderText(font_time, screen);
			time_of_turn_game.RenderText(screen, 0, SCREEN_HEIGHT - tile_frame * 5 / 2 - SIZE_FONT / 2, true);

			int real_time = timeFPS.get_ticks();
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
		Mix_PlayChannel(-1, sound_win, 0);
			SCREEN_WIN_GAME wingame;
			int click_win_game = wingame.setupGAMEOK(screen, index_wingame,font_score);//1 : p1 win, 2: p2 win, 3: tie
			Mix_PlayChannel(-1, sound_click, 0);
			switch (click_win_game)
			{
			case 0: goto OUTGAME; break;

			case 1: goto PlayGame2player; break;

			case 2: goto home;     break;

			case 3: goto gameMode; break;

			default: break;
			}
		}

		{
		directionGame:// Huong dan choi game 

		INDIRECTIONGAME inforG;
		int clickIndirect = inforG.setupINDIRECTION(screen);
		Mix_PlayChannel(-1, sound_click, 0);
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
