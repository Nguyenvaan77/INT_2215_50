#include"snak.h"

snake::snake(SDL_Renderer* ren)
{
	isMove = false;
	alive = true;
	HEAD.rect_= { (rand()%20)*30,(rand()%30)*30,30,30};
	SNAKE.push_back(HEAD.rect_);
	HEAD.render(ren, &HEAD.rect_);
	for (int i = 1; i <= 3; ++i)
	{
		SDL_Rect rec_;
		rec_ = { SNAKE[0].x - i * 30, SNAKE[0].y, 30, 30, };
		SNAKE.push_back(rec_);
		BODY.render(ren, &SNAKE[i]);
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
	HEAD.loadImg("anh//head.bmp", ren);
	BODY.loadImg("anh//body.bmp", ren);
	TAIL.loadImg("anh//duoi.bmp", ren);
	if (HEAD.object_ == NULL)
	{
		cout << "Load head.bmp ERROR" << endl;
		ok = false;
	}
	if (BODY.object_ == NULL)
	{
		cout << "Load body.bmp ERROR" << endl;
		ok = false;
	}
	if (TAIL.object_ == NULL)
	{
		cout << "Load duoi.bmp ERROR" << endl;
		ok = false;
	}
	return ok;
}

void snake::addTail()
{
		SDL_Rect foo;
		foo = { SNAKE[SNAKE.size()-1].x,SNAKE[SNAKE.size() - 1].y,30,30};
		SNAKE.push_back(foo);
	
}

void snake::updateTail(SDL_Renderer* ren)
{
	int prev_x = SNAKE[0].x;
	int prev_y = SNAKE[0].y;
	SNAKE[0].x = HEAD.rect_.x;
	SNAKE[0].y = HEAD.rect_.y;
	cout << 0 << SNAKE[0].x << " " << SNAKE[0].y << endl;
	for (int i = 1; i < SNAKE.size(); ++i)
	{
		int prev2_x = SNAKE[i].x;
		int prev2_y = SNAKE[i].y;
		SNAKE[i].x = prev_x;
		SNAKE[i].y = prev_y;
		prev_x = prev2_x;
		prev_y = prev2_y;
	}
}

void snake::showfullbody(SDL_Renderer* ren)
{
	HEAD.render(ren, &SNAKE[0]);
	for (int i = 1; i < SNAKE.size() - 1; ++i)
	{
		BODY.render(ren, &SNAKE[i]);
	};
	TAIL.render(ren, &SNAKE[SNAKE.size() - 1]);
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
	case SDLK_RIGHT:
		HEAD.rect_.x += 30; 
		dir = RIGHT;
		break;
	case SDLK_LEFT:
		HEAD.rect_.x -= 30; 
		dir = LEFT;
		break;
	default:break;
	};
}

bool snake::bitWall()
{
	if (HEAD.rect_.x > SCREEN_WIDTH - 30 || HEAD.rect_.y > SCREEN_HEIGHT - 30 || HEAD.rect_.x < 0 || HEAD.rect_.y < 0)
	{
		return true;
	}
	return false;
}

bool snake::bitHimSelf()
{
	int comp_x = HEAD.rect_.x + 15;
	int comp_y = HEAD.rect_.y + 15;
	for (int i = 1; i < SNAKE.size(); ++i)
	{
		if (comp_x<SNAKE[i].x + 30 && comp_x>SNAKE[i].x && comp_y<SNAKE[i].y + 30 && comp_y>SNAKE[i].y)
		{
			return true;
		}
	}
	return false;
}
bool snake::isAlive()
{
	if (!bitWall() && !bitHimSelf())
	{
		return true;
		alive = true;
	}
	alive = false;
	return false;
}


bool snake::eatFood() {
	int comp_x = HEAD.rect_.x + 15;
	int comp_y = HEAD.rect_.y + 15;
	return true;
}