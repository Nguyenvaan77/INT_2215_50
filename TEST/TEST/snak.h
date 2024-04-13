#ifndef SNAKE_H_
#define SNAKE_H_

#include"commonFunc.h"
#include"baseobject.h"

using namespace std;

class snake
{
public:
	snake(SDL_Renderer*ren);
	~snake() { ; };

	void setpos(int a, int b) { HEAD.rect_.x = a;HEAD.rect_.y = b; HEAD.rect_.w = 30; HEAD.rect_.h = 30; };//set HEAD snake
	bool isAlive();
	bool bitWall();
	bool eatFood(SDL_Rect FOOD);
	bool bitHimSelf();
	void addTail();
	void updateTail(SDL_Renderer* ren);
	bool setIMGforIterm(SDL_Renderer* ren);

	void handleInput(SDL_Event &even);

	

	void showfullbody(SDL_Renderer* ren);
	
	

	void xulyDichuyen()
	{
		switch (dir)
		{
		case 1: HEAD.rect_.y -= 30; break;
		case 2:HEAD.rect_.y += 30; break;
		case 3:HEAD.rect_.x -= 30; break;
		case 4:HEAD.rect_.x += 30; break;
		}
	}


	int dir;
protected:

	vector<SDL_Rect> SNAKE;
	baseObject HEAD;
	baseObject BODY;
	baseObject TAIL;
	bool alive = true;
	bool isMove = false;


	

};



#endif 