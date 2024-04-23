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

#endif // !MENU_H_

