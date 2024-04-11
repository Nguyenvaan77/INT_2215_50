#include"snak.h"
#include"commonFunc.h"
#include"baseobject.h"

snake::snake()
{
	isMove = false;
	alive = true;
	HEAD.rect_= { (rand()%20)*30,(rand()%30)*30,30,30};
	SNAKE.push_back(HEAD.rect_);
	for (int i = 1; i <= 3; ++i)
	{
		SDL_Rect rec_;
		rec_ = { SNAKE[0].x - i * 30, SNAKE[0].y, 30, 30, };
		SNAKE.push_back(rec_);
	};
	cout << "Do dai ran = " << SNAKE.size() << endl;
	for (int i = 0; i < SNAKE.size(); ++i)
	{
		cout << i << "  " << SNAKE[i].x << " " << SNAKE[i].y << endl;
	}
};

bool snake::setIMGforIterm(SDL_Renderer* ren)
{
	bool ok = true;
	HEAD.loadImg("anh//khong.bmp", ren);
	BODY.loadImg("anh//cake.bmp", ren);
	TAIL.loadImg("anh//chanh.bmp", ren);
	if (HEAD.object_ == NULL)
	{
		cout << "Load khong.bmp ERROR" << endl;
		ok = false;
	}
	if (BODY.object_ == NULL)
	{
		cout << "Load cake.bmp ERROR" << endl;
		ok = false;
	}
	if (TAIL.object_ == NULL)
	{
		cout << "Load chanh.bmp ERROR" << endl;
		ok = false;
	}
	return ok;
}

/*void snake::addTail()
{
	if (eatFood())
	{
		SDL_Rect foo;
		foo = { 0,0,30,30 };
		SNAKE.push_back(foo);
	}
}*/

void snake::updateTail(SDL_Renderer* ren)
{
	SDL_RenderClear(ren);
	int prev_x = SNAKE[0].x;
	int prev_y = SNAKE[0].y;
	SNAKE[0].x = HEAD.rect_.x;
	SNAKE[0].y = HEAD.rect_.y;
	HEAD.render(ren, &SNAKE[0]);
	cout << 0 << SNAKE[0].x << " " << SNAKE[0].y << endl;
	for (int i = 1; i < SNAKE.size(); ++i)
	{
		int prev2_x = SNAKE[i].x;
		int prev2_y = SNAKE[i].y;
		SNAKE[i].x = prev_x;
		SNAKE[i].y = prev_y;
		prev_x = prev2_x;
		prev_y = prev2_y;
		BODY.render(ren, &SNAKE[i]);
		cout << i << SNAKE[i].x << " " << SNAKE[i].y << endl;
	}
}

void snake::handleInput(SDL_Event& even)
{
	switch (even.key.keysym.sym)
	{
	case SDLK_UP:
		HEAD.rect_.y -= 30; 
		dir = UP;
		break;
	case SDLK_DOWN:
		HEAD.rect_.y += 30; 
		dir = DOWN;
		break;
	case SDLK_RIGHT:HEAD.rect_.x += 30; 
		dir = RIGHT;
		break;
	case SDLK_LEFT:HEAD.rect_.x -= 30; 
		dir = LEFT;
		break;
	};
}
