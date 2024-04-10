#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <cmath>
#include <Windows.h>
#include<vector>
#include <sstream>
#include<string>
#include<map>
#include<iostream>
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 900;
const int tile_frame = 30;

SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Rect snakePosition = { 0,0,tile_frame,tile_frame };//dau ran
SDL_Rect fruitPosition = {0,0,tile_frame*2,tile_frame*2};

vector<SDL_Rect> SNAKE;

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
	SDL_SetRenderDrawColor(screen, 77, 77, 77, 0xFF);
	SDL_RenderFillRect(screen, &snakePosition);
	SDL_SetRenderDrawColor(screen, 105, 255, 0, 0xFF);

	for (int i = 1; i <= 3; ++i)
	{
		SNAKE.push_back(taorec(snakePosition.x - i * 30, snakePosition.y));
		SDL_RenderFillRect(screen,& SNAKE[i]);
	}


	cout << "size in vector: " << SNAKE.size()<<endl;

}


void close() { //closes everything properly
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

namespace VACHAM {
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
	void wall()
	{
		if (snakePosition.x > SCREEN_WIDTH - 30||snakePosition.x<0||snakePosition.y>SCREEN_HEIGHT-30||snakePosition.y<0)
		{
			close();
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
	SDL_RenderFillRect(ren, &SNAKE[0]);
	cout << "SNAKE [0] : " << SNAKE[0].x << " " << SNAKE[0].y << endl;
	for (int i = 1; i < SNAKE.size(); ++i)
	{
		int prev2_x_ = SNAKE[i].x;
		int prev2_y_ = SNAKE[i].y;
		SNAKE[i].x = prev_x_;
		SNAKE[i].y = prev_y_;
		prev_x_ = prev2_x_;
		prev_y_ = prev2_y_;
		SDL_SetRenderDrawColor(ren, 105, 255, 0, 0xFF);
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



int main(int argc, char* args[])
{
	srand(time(NULL));
	game_Screen();
	START_GAME();
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
				tailSnake(screen);
			}
			if (VACHAM::food())
			{
				fruitPosition.x = rand() % 20 * 30;
				fruitPosition.y = rand()%30*30;
				fruitPosition.w = rand() % 70 + 20;
				fruitPosition.h = rand() % 70 + 20;
			}
			VACHAM::wall();
		}

		fillFood(screen);
		SDL_RenderPresent(screen);
	}
	close();
	std::cout << SNAKE.size();
	return 0;
}
