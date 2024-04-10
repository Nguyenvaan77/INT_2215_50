#include"commonFunc.h"
#include"baseobject.h"
#include"snak.h"
using namespace std;
//Screen dimension constants


void setIMGforitem()
{
	HEADSNAKE.loadImg("anh//kingkong.bmp", screen);
	thanSNAKE.loadImg("anh//chanh.bmp", screen);
	duoiSNAKE.loadImg("anh//cake.bmp", screen);
}

void fillFood(SDL_Renderer* ren)// fill màu cho từng rect thuc an
{
	SDL_SetRenderDrawColor(ren, 120, 30, 255, 0xFF);
	SDL_RenderFillRect(ren, &fruitPosition);
}

SDL_Rect taorec(int x,int y)
{
	SDL_Rect rec;
	rec = { x,y,30,30 };
	return rec;
}

void START_GAME()
{
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);
	SDL_RenderClear(screen);

	snakePosition.x = 90;
	snakePosition.y = 90;
	fruitPosition.x = 450;
	fruitPosition.y = 450;
	SNAKE.push_back(snakePosition);
	for (int i = 1; i <= 3; ++i)
	{
		SNAKE.push_back(taorec(snakePosition.x - i * 30, snakePosition.y));
	}
}


void close() { //closes everything properly
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

namespace VACHAM {
	//Va chạm thức ăn 
	bool food()
	{
		bool vacham = false;

		int x_rightbottom = snakePosition.x + 30;
		int y_rightbottom = snakePosition.y + 30;

		int x_leftbottom = snakePosition.x;
		int y_leftbottom = snakePosition.y + 30;

		int x_righttop = snakePosition.x + 30;
		int y_righttop = snakePosition.y;

		int x_lefttop = snakePosition.x;
		int y_lefttop = snakePosition.y;

		if (x_rightbottom<fruitPosition.x + fruitPosition.w && x_rightbottom>fruitPosition.x && y_rightbottom < fruitPosition.y + fruitPosition.h && y_rightbottom > fruitPosition.y)
		{
			vacham = true;
		}
		if (x_righttop<fruitPosition.x + fruitPosition.w && x_righttop>fruitPosition.x && y_righttop < fruitPosition.y + fruitPosition.h && y_righttop > fruitPosition.y)
		{
			vacham = true;
		}
		if (x_leftbottom<fruitPosition.x + fruitPosition.w && x_leftbottom>fruitPosition.x && y_leftbottom < fruitPosition.y + fruitPosition.h && y_leftbottom > fruitPosition.y)
		{
			vacham = true;
		}
		if (x_lefttop<fruitPosition.x + fruitPosition.w && x_lefttop>fruitPosition.x && y_lefttop < fruitPosition.y + fruitPosition.h && y_lefttop > fruitPosition.y)
		{
			vacham = true;
		}



		return vacham;
	}

	//Va chạm tường 
	void wall()
	{
		if (snakePosition.x > SCREEN_WIDTH - 30||snakePosition.x<0||snakePosition.y>SCREEN_HEIGHT-30||snakePosition.y<0)
		{
			close();
		}
	}

	bool checkTrungTail(int diem_x,int diem_y,int Left_x,int Left_y)
	{
		if (diem_x > Left_x && diem_x<Left_x + 30 && diem_y>Left_y && diem_y < Left_y + 30)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//tự xơi chính nó
	void eatedFelf()
	{
		int pointCheck_x = snakePosition.x + 15;
		int pointCheck_y = snakePosition.y + 15;
		for (int i = 1; i < SNAKE.size(); ++i)
		{
			if (checkTrungTail(pointCheck_x, pointCheck_y, SNAKE[i].x, SNAKE[i].y))
			{
				cout << "Va cham than" << endl;
			}
		}
	}
}

void tailSnake(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
	SDL_RenderClear(ren);
    int prev_x_ = SNAKE[0].x;
	int prev_y_ = SNAKE[0].y;
	SNAKE[0].x = snakePosition.x;
	SNAKE[0].y = snakePosition.y;

	SDL_SetRenderDrawColor(ren, 77, 77, 77, 0xFF);
	SDL_RenderFillRect(ren, &SNAKE[0]);SDL_SetRenderDrawColor(ren, 105, 255, 0, 0xFF);
	cout << "SNAKE [0] : " << SNAKE[0].x << " " << SNAKE[0].y << endl;
	for (int i = 1; i < SNAKE.size(); ++i)
	{
		int prev2_x_ = SNAKE[i].x;
		int prev2_y_ = SNAKE[i].y;
		SNAKE[i].x = prev_x_;
		SNAKE[i].y = prev_y_;
		prev_x_ = prev2_x_;
		prev_y_ = prev2_y_;
		
		SDL_RenderFillRect(ren, &SNAKE[i]);
		cout << "SNAKE ["<<i<<"]" <<":" << SNAKE[i].x << " " << SNAKE[i].y << endl;
	}
}

void game_Screen() { //creates the game surface and the render as wll
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			screen = SDL_CreateRenderer(window, -1, 0);
		}
	}
}// HÀM INIT,CREATE,SET RENDERER

void addTail()
{
	SDL_Rect rec = { 0,0,30,30 };

	SNAKE.push_back(rec);
}

int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();
	START_GAME();
	setIMGforitem();
	bool quit = false;
	SDL_Event even;
	while (!quit)
	{
		if (SDL_PollEvent(&even))
		{
			if (even.type == SDL_QUIT)
			{
				quit = true;
			}
			if (even.type == SDL_MOUSEBUTTONDOWN)
			{
				if (even.button.button == SDL_BUTTON_LEFT)
				{
					int x, y;
					UINT32 hhh = SDL_GetMouseState(&x, &y);
					std::cout << x << " " << y << std::endl;
				}
			}
			if (even.type == SDL_KEYDOWN)
			{
				switch (even.key.keysym.sym)
				{
				case SDLK_UP: snakePosition.y -= 30; break;
				case SDLK_DOWN: snakePosition.y += 30; break;
				case SDLK_LEFT: snakePosition.x -= 30; break;
				case SDLK_RIGHT: snakePosition.x += 30; break;
				default: snakePosition.x = 200; snakePosition.y = 200; break;
				}
				if (VACHAM::food())
			    {
				fruitPosition.x = rand() %600;
				fruitPosition.y = rand()%900;
				fruitPosition.w = rand() % 70 + 20;
				fruitPosition.h = rand() % 70 + 20;
				addTail();
			    }
			    VACHAM::wall();
				tailSnake(screen);
				VACHAM::eatedFelf();
		    }
		}; 
		
		fillFood(screen);
		SDL_RenderPresent(screen);
	}
	close();
	std::cout << SNAKE.size();
	return 0;
}
