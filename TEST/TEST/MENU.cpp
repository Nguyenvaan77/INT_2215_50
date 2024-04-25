#include"MENU.h"

int  MENUGAME::setupMenu(SDL_Renderer* ren)
{
	bool control_in_playgame = false;
	
	BackStr.loadImg("anh//BACKGROUND//234.bmp", ren);

	bool control_in_PLAY = false;
	bool control_in_INFOR = false;
	bool control_in_EXIT = false;

	SDL_Event ev;

	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				return 0;//tat game
			}
			if (ev.type == SDL_MOUSEMOTION)
			{
				if (ev.motion.x <= 585 && ev.motion.x >= 315 && ev.motion.y >= 300 && ev.motion.y <= 360)//tự chọn vị trí cho nút PLAY 
				{
					control_in_PLAY = true;
				}
				else
				{
					control_in_PLAY = false;
				}
				if (ev.motion.x <= 885 && ev.motion.x >= 685 && ev.motion.y >= 300 && ev.motion.y <= 500)//tự chọn vị trí cho nút INFOR 
				{
					control_in_INFOR = true;
				}
				else
				{
					control_in_INFOR = false;
				}
				if (ev.motion.x <= 497 && ev.motion.x >= 403 && ev.motion.y >= 360 && ev.motion.y <= 420)//tự chọn vị trí cho nút EXIT 
				{
					control_in_EXIT = true;
				}
				else
				{
					control_in_EXIT = false;
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LMASK)
				{
					int x, y;
					Uint32 h = SDL_GetMouseState(&x, &y);
					if (x < 585 && x>315 && y >= 300 && y <= 360)
					{
						return 1;//plpay
					}
					if (x <= 885 && x >= 685 && y >= 300 && y <= 500)
					{
						return 2;//infor
					}
					if (x <= 497 && x >= 403 && y >= 360 && y <= 420)
					{
						return 3;//exit
					}
				}
			}
		}
		
		
		

		if (control_in_PLAY)
		{
			playGameBut.loadImg("anh//button//play1.bmp", ren);
		}
		else
		{
			playGameBut.loadImg("anh//button//play2.bmp", ren);
		};

		if (control_in_INFOR)
		{
			HowToPlayBut.loadImg("anh//button//infor1.bmp", ren);
		}
		else
		{
			HowToPlayBut.loadImg("anh//button//infor2.bmp", ren);
		}

		if (control_in_EXIT)
		{
			EXITBut.loadImg("anh//button//exit1.bmp", ren);
		}
		else
		{
			EXITBut.loadImg("anh//button//exit2.bmp", ren);
		}

		playGameBut.setRect(315, 300);
		HowToPlayBut.setRect(685, 300);
		EXITBut.setRect(404, 360);

		SDL_RenderClear(ren);

		BackStr.render(ren, NULL);
		playGameBut.render(ren, &playGameBut.rect_);
		EXITBut.render(ren, &EXITBut.rect_);
		HowToPlayBut.render(ren, &HowToPlayBut.rect_);

		SDL_RenderPresent(ren);
		SDL_Delay(90);
	}
}

int MODECHOISEGAME::setupMODECHOISE(SDL_Renderer* ren)
{
	bool control_in_ONE = false;
	bool control_in_TWO = false;
	bool control_in_REDOT = false;

	SDL_Event ev;

	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				return 0;//tat game
			}
			if (ev.type == SDL_MOUSEMOTION)
			{
				if (ev.motion.x <= 600 && ev.motion.x >= 300 && ev.motion.y >= 270 && ev.motion.y <= 400)//tự chọn vị trí cho nút PLAY 
				{
					control_in_ONE = true;
				}
				else
				{
					control_in_ONE = false;
				}

				if (ev.motion.x <= 600 && ev.motion.x >= 300 && ev.motion.y >= 450 && ev.motion.y <= 580)//tự chọn vị trí cho nút INFOR 
				{
					control_in_TWO = true;
				}
				else
				{
					control_in_TWO = false;
				}
				if (ev.motion.x <= 64 && ev.motion.x >= 0 && ev.motion.y >= 0 && ev.motion.y <= 64)//tự chọn vị trí cho nút PLAY 
				{
					control_in_REDOT = true;
				}
				else
				{
					control_in_REDOT = false;
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LMASK)
				{
					int x, y;
					Uint32 h = SDL_GetMouseState(&x, &y);
					if (x <= 600 && x>=300 && y >= 270 && y <= 400)
					{
						return 1;//1player
					}
					if (x <= 600 && x >= 300 && y >= 450 && y <= 580)
					{
						return 2;//2player
					}
					if (x <= 64 && x >= 0 && y >= 0 && y <= 64)
					{
						return 3;//gohome
					}
				}
			}
		}

		
		if (control_in_ONE)
		{
			ONEplayerBut.loadImg("anh//button//1player1.bmp", ren);
		}
		else
		{
			ONEplayerBut.loadImg("anh//button//1player2.bmp", ren);
		};

		if (control_in_TWO)
		{
			TWOplayerBut.loadImg("anh//button//2player1.bmp", ren);
		}
		else
		{
			TWOplayerBut.loadImg("anh//button//2player2.bmp", ren);
		}





		if (control_in_REDOT)
		{
			reDot.loadImg("anh//button//back1.bmp", ren);
		}
		else
		{
			reDot.loadImg("anh//button//back2.bmp", ren);
		}
		BackMode.loadImg("anh//BACKGROUND//backmode1.bmp", ren);

		ONEplayerBut.setRect(300, 270);
		TWOplayerBut.setRect(300, 450);
		reDot.setRect(0, 0);

		SDL_RenderClear(ren);

		BackMode.render(ren, NULL);
		ONEplayerBut.render(ren, &ONEplayerBut.rect_);
		TWOplayerBut.render(ren, &TWOplayerBut.rect_);
		reDot.render(ren, &reDot.rect_);

		SDL_RenderPresent(ren);
		SDL_Delay(90);
	}
}

int INDIRECTIONGAME::setupINDIRECTION(SDL_Renderer* ren)
{
	bool control_in_REDOT = false;

	SDL_Event ev;

	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				return 0;//tat game
			}
			if (ev.type == SDL_MOUSEMOTION)
			{
				if (ev.motion.x <= 64 && ev.motion.x >= 0 && ev.motion.y >= 0 && ev.motion.y <= 64)//tự chọn vị trí cho nút PLAY 
				{
					control_in_REDOT = true;
				}
				else
				{
					control_in_REDOT = false;
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LMASK)
				{
					int x, y;
					Uint32 h = SDL_GetMouseState(&x, &y);
					if (x <= 64 && x >= 0 && y >= 0 && y <= 64)
					{
						return 1;//gohome
					}
				}
			}
		}


		

		if (control_in_REDOT)
		{
			reDot.loadImg("anh//button//back1.bmp", ren);
		}
		else
		{
			reDot.loadImg("anh//button//back2.bmp", ren);
		}
		BackINDIRECT.loadImg("anh//BACKGROUND//infor.bmp", ren);

		
		reDot.setRect(0, 0);

		SDL_RenderClear(ren);

		BackINDIRECT.render(ren, NULL);
		reDot.render(ren, &reDot.rect_);

		SDL_RenderPresent(ren);
		SDL_Delay(90);
	}
}

int SCREEN_WIN_GAME::setupGAMEOK(SDL_Renderer* ren,int WhoWin,TTF_Font* font)
{
	bool control_in_PLAYAGAIN = false;
	bool control_in_EXIT = false;
	bool control_in_REDOT = false;

	SDL_Event ev;

	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				return 0;//tat game
			}
			if (ev.type == SDL_MOUSEMOTION)
			{
				if (ev.motion.x <= 550 && ev.motion.x >= 350 && ev.motion.y >= 400 && ev.motion.y <= 495)//tự chọn vị trí cho nút PLAY 
				{
					control_in_PLAYAGAIN = true;
				}
				else
				{
					control_in_PLAYAGAIN = false;
				}

				if (ev.motion.x <= 550 && ev.motion.x >= 350 && ev.motion.y >= 545 && ev.motion.y <= 640)//tự chọn vị trí cho nút INFOR 
				{
					control_in_EXIT = true;
				}
				else
				{
					control_in_EXIT = false;
				}
				if (ev.motion.x <= 64 && ev.motion.x >= 0 && ev.motion.y >= 0 && ev.motion.y <= 64)//tự chọn vị trí cho nút PLAY 
				{
					control_in_REDOT = true;
				}
				else
				{
					control_in_REDOT = false;
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LMASK)
				{
					int x, y;
					Uint32 h = SDL_GetMouseState(&x, &y);
					if (x <= 600 && x >= 300 && y >= 400 && y <= 530)
					{
						return 1;//playAGAIN
					}
					if (x <= 600 && x >= 300 && y >= 580 && y <= 710)
					{
						return 2;//EXITTHOME
					}
					if (x <= 64 && x >= 0 && y >= 0 && y <= 64)
					{
						return 3;//REDOT
					}
				}
			}
		}


		if (control_in_PLAYAGAIN)
		{
			PlayAgainBut.loadImg("anh//button//playagain1.bmp", ren);
		}
		else
		{
			PlayAgainBut.loadImg("anh//button//playagain2.bmp", ren);
		};

		if (control_in_EXIT)
		{
			ExitBut.loadImg("anh//button//exithome1.bmp", ren);
		}
		else
		{
			ExitBut.loadImg("anh//button//exithome2.bmp", ren);
		}

		if (control_in_REDOT)
		{
			reDot.loadImg("anh//button//back1.bmp", ren);
		}
		else
		{
			reDot.loadImg("anh//button//back2.bmp", ren);
		}
		SCREEN_WIN_GAME::loadBack(ren, WhoWin);
		


		PlayAgainBut.setRect(350, 400);
		ExitBut.setRect(350, 545);
		reDot.setRect(0, 0);

		SDL_RenderClear(ren);

		BackWin.render(ren, NULL);

		if (WhoWin == 0)//load SCORE
		{
			DIEM.LoadFromRenderText(font, ren);
			DIEM.RenderText(ren, 150, 100,false);
		}

		PlayAgainBut.render(ren, &PlayAgainBut.rect_);
		ExitBut.render(ren, &ExitBut.rect_);
		reDot.render(ren, &reDot.rect_);

		SDL_RenderPresent(ren);
		SDL_Delay(90);
	}
}


