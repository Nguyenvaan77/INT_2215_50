#include"snak.h"

snake::snake(SDL_Renderer* ren)
{
	isMove = false;
	alive = true;
	HEAD.rect_= { (rand()%20)*30,(rand()%30)*30,30,30};
	SNAKE.push_back(HEAD.rect_);
	dir_of_iterm.push_back(4);
	HEAD.render(ren, &HEAD.rect_);
	for (int i = 1; i <= 3; ++i)
	{
		SDL_Rect rec_;
		rec_ = { SNAKE[0].x - i * 30, SNAKE[0].y, 30, 30, };
		SNAKE.push_back(rec_);
		dir_of_iterm.push_back(4);
		BODY.render(ren, &SNAKE[i]);
	};
	cout << "Do dai ran = " << SNAKE.size() << endl;
	
	dirHead = 4;//huong ban dau la right =4;
	score = 0;
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
		foo = { SNAKE[SNAKE.size()-2].x,SNAKE[SNAKE.size() - 2].y,30,30};
		SNAKE.push_back(foo);

		dir_of_iterm.push_back(dir_of_iterm[dir_of_iterm.size() - 1]);
	
}

void snake::updateTail(SDL_Renderer* ren)
{
	int prev_x = SNAKE[0].x;
	int prev_y = SNAKE[0].y;
	SNAKE[0].x = HEAD.rect_.x;
	SNAKE[0].y = HEAD.rect_.y;
	
	int prev_dir = dir_of_iterm[0];
	dir_of_iterm[0] = dirHead;

	for (int i = 1; i < SNAKE.size(); ++i)
	{
		int prev2_x = SNAKE[i].x;
		int prev2_y = SNAKE[i].y;
		SNAKE[i].x = prev_x;
		SNAKE[i].y = prev_y;
		prev_x = prev2_x;
		prev_y = prev2_y;

		int tempDIR = dir_of_iterm[i];
		dir_of_iterm[i] = prev_dir;
		prev_dir = tempDIR;

	}
	cout << "head :" << HEAD.rect_.x << " " << HEAD.rect_.y << endl;
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


bool snake::loadHEAD(int dir,SDL_Renderer* ren,bool eat)
{
	if (eat)
	{
		switch (dir)
		{
		case 1: HEAD.loadImg("anh//HEAD//eatup.bmp", ren); break;
		case 2: HEAD.loadImg("anh//HEAD//eatdown.bmp", ren); break;
		case 3: HEAD.loadImg("anh//HEAD//eatleft.bmp", ren); break;
		case 4: HEAD.loadImg("anh//HEAD//eatright.bmp", ren); break;
		}
	}
	else
	{ 
		switch (dir)
		{
		case 1: HEAD.loadImg("anh//HEAD//up.bmp", ren); break;
		case 2: HEAD.loadImg("anh//HEAD//down.bmp", ren); break;
		case 3: HEAD.loadImg("anh//HEAD//left.bmp", ren); break;
		case 4: HEAD.loadImg("anh//HEAD//right.bmp", ren); break;
		}
	}
	if (HEAD.getObject() == NULL)
	{
		cout << "LOAD HEAD ERROR" << endl;
		return false;
	}
	
	return true;
}

bool snake::loadBODY(int dir_trc, int dir_now, SDL_Renderer* ren)
{
	if (dir_trc == dir_now)
	{
		switch (dir_now)
		{
		case 1:BODY.loadImg("anh//BODY//body1.bmp", ren); break;
		case 2:BODY.loadImg("anh//BODY//body1.bmp", ren); break;
		case 3:BODY.loadImg("anh//BODY//body.bmp", ren); break;
		case 4:BODY.loadImg("anh//BODY//body.bmp", ren); break;
		}
	}
	else
	{
		if ((dir_trc == 1 && dir_now == 3)||(dir_trc==4&&dir_now==2))
		{
			BODY.loadImg("anh//BODY//body2.bmp", ren);
		}
		if ((dir_trc == 1 && dir_now == 4)||(dir_trc==3&&dir_now==2))
		{
			BODY.loadImg("anh//BODY//body3.bmp", ren);
		}
		if ((dir_trc == 3 && dir_now == 1)||(dir_trc==2&&dir_now==4))
		{
			BODY.loadImg("anh//BODY//body4.bmp", ren);
		}
		if ((dir_trc == 4 && dir_now == 1)||(dir_trc==2&&dir_now==3))
		{
			BODY.loadImg("anh//BODY//body5.bmp", ren);
		}
	}
	if (BODY.getObject() == NULL)
	{
		cout << "LOAD BODY ERROR" << endl;
		return false;
	}
	
	return true;
}

bool snake::loadTAIL(int dir, SDL_Renderer* ren)
{
	switch (dir)
	{
	case 1:TAIL.loadImg("anh//TAIL//up.bmp", ren); break;
	case 2:TAIL.loadImg("anh//TAIL//down.bmp", ren); break;
	case 3:TAIL.loadImg("anh//TAIL//left.bmp", ren); break;
	case 4:TAIL.loadImg("anh//TAIL//right.bmp", ren); break;
	}
	if (TAIL.getObject() == NULL)
	{
		cout << "LOAD TAIL ERROR" << endl;
		return false;
	}
	
	return true;
}

bool snake::showfullbodysnake(SDL_Renderer* ren,bool  eat)//load ảnh theo trạng thái của từng phần(rect) của snake 
{
	bool ok = true;
	if (loadHEAD(dir_of_iterm[0], ren,eat))
	{
		HEAD.render(ren, &SNAKE[0]);
		
	}
	else
	{
		ok = false;
		cout << "2. Load HEAD ERROR" << endl;
	}
	for (int i = 1; i < SNAKE.size() ; ++i)
	{
		
		if (i == SNAKE.size() - 1)
		{
			loadTAIL(dir_of_iterm[i -1], ren);
			TAIL.render(ren, &SNAKE[SNAKE.size() - 1]);
			
		}
		else
		{
			if (loadBODY(dir_of_iterm[i - 1], dir_of_iterm[i], ren))
			{
			BODY.render(ren, &SNAKE[i]);
			
			}
		else
			{
			ok = false;
			}
		}
	}
	return ok;
}





void snake::handleInput(SDL_Event& even)
{
	switch (even.key.keysym.sym) {
	case SDLK_LEFT:
		if (dirHead != 4)
		{
			dirHead = 3;
		}
		break;
	case SDLK_RIGHT:
		if (dirHead != 3)
		{
		
			dirHead = 4;
		}
		break;
	case SDLK_UP:
		if (dirHead != 2)
		{
			dirHead = 1;
		}
		break;
	case SDLK_DOWN:
		if (dirHead != 1)
		{
			dirHead = 2;
		}
		break;
	case SDLK_ESCAPE: 
		isMove = false;
		break;
	
	default:
		break;
	}
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
		alive = true;
		return alive;
	}
	alive = false;
	return alive;
}
void snake::tangScore()//Hàm này gọi trong eatFood()
{
	++score;
}

bool snake::eatFood(SDL_Rect FOOD) {
	if (HEAD.rect_.x == FOOD.x&&HEAD.rect_.y==FOOD.y)
	{
		tangScore();
		return true;
	}
	return false;
}

int snake::inScore()
{
	return score;
}
