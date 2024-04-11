#ifndef SNAKE_H_
#define SNAKE_H_

#include"commonFunc.h"
#include"baseobject.h"

using namespace std;

class snake
{
public:
	snake();
	~snake() { ; };

	void setpos(int a, int b) { HEAD.rect_.x = a;HEAD.rect_.y = b; HEAD.rect_.w = 30; HEAD.rect_.h = 30; };//set HEAD snake
	bool isAlive();
	bool bitWall();
	bool eatFood();
	bool bitHimSelf();
	void addTail();
	void updateTail(SDL_Renderer* ren);
	bool setIMGforIterm(SDL_Renderer* ren);

	void handleInput(SDL_Event &even);

	void inHEAD() { cout << "HEAD.rect "<<HEAD.rect_.x << " " << HEAD.rect_.y << endl; };
	void fullbody()
	{
		for (int i = 0; i < SNAKE.size(); ++i)
		{
			cout << i << " " << SNAKE[i].x << " " << SNAKE[i].y << endl;
		}
	}

protected:

	vector<SDL_Rect> SNAKE;
	baseObject HEAD;
	baseObject BODY;
	baseObject TAIL;
	bool alive = true;
	bool isMove = false;
	enum Direction {UP,DOWN,LEFT,RIGHT};
	Direction dir;// UP = 0
	              // DOWN = 1
	              // LEFT = 2
	              // RIGHT = 3

};



#endif 