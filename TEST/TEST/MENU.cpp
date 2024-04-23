#include"MENU.h"

int  MENUGAME::setupMenu(SDL_Renderer* ren)
{
	bool control_in_playgame = false;
	
	BackStr.loadImg("anh//BACKGROUND//backstart.bmp", ren);

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
				if (ev.motion.x <= 585 && ev.motion.x >= 315 && ev.motion.y >= 360 && ev.motion.y <= 500)//tự chọn vị trí cho nút PLAY 
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
					if (x <= 585 && x >= 315 && y >= 360 && y <= 500)
					{
						return 3;//exit
					}
				}
			}
		}
		
		BackStr.render(ren, NULL);
		

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
		EXITBut.setRect(315, 360);

		playGameBut.render(ren, &playGameBut.rect_);
		EXITBut.render(ren, &EXITBut.rect_);
		HowToPlayBut.render(ren, &HowToPlayBut.rect_);

		SDL_RenderPresent(ren);
		SDL_Delay(90);
	}
}


