#ifndef MENU_H_
#define MENU_H_

#include"commonFunc.h"
#include"TEXT.h"
#include"baseobject.h"

class MENUGAME 
{
public:
	MENUGAME() { ; };
	~MENUGAME() { ; };
	int setupMenu(SDL_Renderer* ren);


private:
	baseObject BackStr;
	baseObject playGameBut;
	baseObject EXITBut;
	baseObject HowToPlayBut;
};

class MODECHOISEGAME
{
public:
	MODECHOISEGAME() { ; };
	~MODECHOISEGAME() { ; };

	int setupMODECHOISE(SDL_Renderer* ren);


private:
	baseObject	 BackMode;
	baseObject   ONEplayerBut;
	baseObject   TWOplayerBut;
	baseObject	 reDot;
};

class INDIRECTIONGAME
{
public:
	INDIRECTIONGAME() { ; };
	~INDIRECTIONGAME() { ; };

	int setupINDIRECTION(SDL_Renderer* ren);


private:
	baseObject	 BackINDIRECT;
	baseObject	 reDot;
};

class SCREEN_WIN_GAME
{
public:
	SCREEN_WIN_GAME() { ; };
	~SCREEN_WIN_GAME() { ; };

	int setupGAMEOK(SDL_Renderer* ren,int WhoWin);
	void loadBack(SDL_Renderer* ren, int WhoWin)
	{
		switch (WhoWin)
		{
		case 0: BackWin.loadImg("anh//BACKGROUND//over.bmp", ren); break;
		case 1: BackWin.loadImg("anh//BACKGROUND//p1win.bmp", ren); break;
		case 2: BackWin.loadImg("anh//BACKGROUND//p2win.bmp", ren); break;
		case 3: BackWin.loadImg("anh//BACKGROUND//tie.bmp", ren);   break;
		default :    break;
		}
	}

private:
	baseObject   BackWin;
	baseObject	 PlayAgainBut;
	baseObject   ExitBut;
	baseObject	 reDot;
};

#endif // !MENU_H_

