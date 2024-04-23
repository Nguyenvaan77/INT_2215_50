#include"snak.h"

snake::snake(SDL_Renderer* ren)
{
	isMove = false;
	alive = true;
	HEAD.rect_ = { 7 * tile_frame,(rand() % 15+3) * tile_frame,tile_frame,tile_frame };
	SNAKE.push_back(HEAD.rect_);
	dir_of_iterm.push_back(4);
	HEAD.render(ren, &HEAD.rect_);
	for (int i = 1; i <= 3; ++i)
	{
		SDL_Rect rec_;
		rec_ = { SNAKE[0].x - i * tile_frame, SNAKE[0].y, tile_frame, tile_frame, };
		SNAKE.push_back(rec_);
		dir_of_iterm.push_back(4);
		BODY.render(ren, &SNAKE[i]);
	};
	cout << "Do dai ran = " << SNAKE.size() << endl;

	dirHead = 4;//huong ban dau la right =4;
	diem = 0;

	
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
	foo = { SNAKE[SNAKE.size() - 2].x,SNAKE[SNAKE.size() - 2].y,tile_frame,tile_frame };
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


bool snake::loadHEAD(int dir, SDL_Renderer* ren, bool nearEat)
{
	if (nearEat)
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
		if (alive)
		{
			switch (dir)
			{
			case 1: HEAD.loadImg("anh//HEAD//up.bmp", ren); cout << "LOAD HEAD UP" << endl;  break;
			case 2: HEAD.loadImg("anh//HEAD//down.bmp", ren); break;
			case 3: HEAD.loadImg("anh//HEAD//left.bmp", ren); break;
			case 4: HEAD.loadImg("anh//HEAD//right.bmp", ren); break;
			}
		}
		else
		{
			switch (dir)
			{
			case 1: HEAD.loadImg("anh//HEAD//headdieup.bmp", ren); cout << "Load HEAD DIE " << endl; break;
			case 2: HEAD.loadImg("anh//HEAD//headdiedown.bmp", ren); break;
			case 3: HEAD.loadImg("anh//HEAD//headdieleft.bmp", ren); break;
			case 4: HEAD.loadImg("anh//HEAD//headdieright.bmp", ren); break;
			}
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
	if (alive)
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
			if ((dir_trc == 1 && dir_now == 3) || (dir_trc == 4 && dir_now == 2))
			{
				BODY.loadImg("anh//BODY//body2.bmp", ren);
			}
			if ((dir_trc == 1 && dir_now == 4) || (dir_trc == 3 && dir_now == 2))
			{
				BODY.loadImg("anh//BODY//body3.bmp", ren);
			}
			if ((dir_trc == 3 && dir_now == 1) || (dir_trc == 2 && dir_now == 4))
			{
				BODY.loadImg("anh//BODY//body4.bmp", ren);
			}
			if ((dir_trc == 4 && dir_now == 1) || (dir_trc == 2 && dir_now == 3))
			{
				BODY.loadImg("anh//BODY//body5.bmp", ren);
			}
		}
	}
	else
	{
		if (dir_now == 1 || dir_now == 2)
		{
			BODY.loadImg("anh//BODY//bodydie2.bmp", ren);
		}
		else
		{
			BODY.loadImg("anh//BODY//bodydie1.bmp", ren);
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
	if (alive)
	{
		switch (dir)
		{
		case 1:TAIL.loadImg("anh//TAIL//up.bmp", ren); break;
		case 2:TAIL.loadImg("anh//TAIL//down.bmp", ren); break;
		case 3:TAIL.loadImg("anh//TAIL//left.bmp", ren); break;
		case 4:TAIL.loadImg("anh//TAIL//right.bmp", ren); break;
		}
	}
	else
	{
		if (dir == 1 || dir == 2)
		{
			TAIL.loadImg("anh//TAIL//diedoc.bmp", ren);
		}
		else {
			TAIL.loadImg("anh//TAIL//diengang.bmp", ren);
		}
	}
	if (TAIL.getObject() == NULL)
	{
		cout << "LOAD TAIL ERROR" << endl;
		return false;
	}

	return true;
}

bool snake::showfullbodysnake(SDL_Renderer* ren,SDL_Rect Food)//load ảnh theo trạng thái của từng phần(rect) của snake 
{
	
	bool ok = true;
	if (loadHEAD(dir_of_iterm[0], ren, nearlyFood(Food)))
	{
		HEAD.render(ren, &SNAKE[0]);

	}
	else
	{
		ok = false;
		cout << "2. Load HEAD ERROR" << endl;
	}
	for (int i = 1; i < SNAKE.size(); ++i)
	{

		if (i == SNAKE.size() - 1)
		{
			loadTAIL(dir_of_iterm[i - 1], ren);
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
			isMove = true;
		}
		break;
	case SDLK_RIGHT:
		if (dirHead != 3)
		{
			dirHead = 4;
			isMove = true;
		}
		break;
	case SDLK_UP:
		if (dirHead != 2)
		{
			dirHead = 1;
			isMove = true;
		}
		break;
	case SDLK_DOWN:
		if (dirHead != 1)
		{
			dirHead = 2;
			isMove = true;
		}
		break;
	

		break;
	default:
		break;
	}
}


bool snake::bitWall()
{
	if (HEAD.rect_.x > SCREEN_WIDTH - tile_frame*2 || HEAD.rect_.y > SCREEN_HEIGHT - 150 || HEAD.rect_.x < tile_frame || HEAD.rect_.y < tile_frame)
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
		if (comp_x<SNAKE[i].x + tile_frame && comp_x>SNAKE[i].x && comp_y<SNAKE[i].y + tile_frame && comp_y>SNAKE[i].y)
		{
			return true;
		}
	}
	return false;
}

bool snake::eatSHIT()
{
	for (int i = 0; i < shit_on_map.size(); ++i)
	{
		if (HEAD.rect_.x == shit_on_map[i].x && HEAD.rect_.y == shit_on_map[i].y)
		{
			return true;
		}
	}
	return false;
}

bool snake::isAlive()
{
	if (!bitWall() && !bitHimSelf()&&!eatSHIT())
	{
		alive = true;
		return alive;
	}
	else
	{
		alive = false;
	}
	return alive;
}

void snake::peeShit()//goi trong ham eatfoood
{
	if (diem > 0 && diem % 5 == 0)
	{
		shit_on_map.push_back(SNAKE[SNAKE.size() - 2]);
	}
}

bool snake::eatFood(SDL_Rect FOOD) {
	if (HEAD.rect_.x == FOOD.x && HEAD.rect_.y == FOOD.y)
	{
		++diem;
		peeShit();
		return true;
	}
	return false;
}

void snake::renderShit(SDL_Renderer* ren)
{
	int ramd = rand() % 12 + 1;
	switch (ramd)
	{
	case 1:
	case 2:
		shit.loadImg("anh//FOOD//shit1.bmp", ren); break;
	case 3:
	case 4:
		shit.loadImg("anh//FOOD//shit2.bmp", ren); break;
	case 5:
	case 6:
		shit.loadImg("anh//FOOD//shit3.bmp", ren); break;
	case 7:
	case 8:
		shit.loadImg("anh//FOOD//shit4.bmp", ren); break;
	case 9:
	case 10:
		shit.loadImg("anh//FOOD//shit5.bmp", ren); break;
	case 11:
	case 12:
		shit.loadImg("anh//FOOD//shit6.bmp", ren); break;
	}
	for (int i = 0; i < shit_on_map.size(); ++i)
	{
		shit.render(ren, &shit_on_map[i]);
	}
}

bool snake::nearlyFood(SDL_Rect FOOD)//hàm tính này được tích hợp trong hàm showfullbodysnake
{
	// sử dụng thư viện cmath dùng các biểu thức toán học để tính khoảng cách đỉnh rect thứ ăn với đầu rắn để kéo dài và thực tế hơn trạng thái há miệng ăn thức ăn của rắn 
	int x_food = FOOD.x;
	int y_food = FOOD.y;
	float KhoangCachDinhRect = (float)sqrt(pow(HEAD.getRect().x - x_food, 2) + pow(HEAD.getRect().y - y_food, 2));
	if (KhoangCachDinhRect <= 25 * sqrt(2))
	{
		return true;
	}
	return false;
}

