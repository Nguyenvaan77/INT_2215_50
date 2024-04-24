#ifndef MENU_H_
#define MENU_H_

#include"commonFunc.h"
#include"TEXT.h"
#include"baseobject.h"
#include"score.h"

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

	void setDiem(int diem,TTF_Font* font) 
	{ 
		DIEM.SetColor(SCORE::BLACK_TEXT);
		DIEM.intscore_toString(diem);
		DIEM.SCORE_to_STRING(); 
	};

	int setupGAMEOK(SDL_Renderer* ren,int WhoWin,TTF_Font* font);
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

	SCORE DIEM;
};

#endif // !MENU_H_

