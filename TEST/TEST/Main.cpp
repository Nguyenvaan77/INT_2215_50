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



void fillSnake1(SDL_Renderer* ren,SDL_Rect rect)// fill màu cho từng rect cua ran
{
	SDL_SetRenderDrawColor(ren, 150, 150, 150, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
	SDL_RenderFillRect(ren, &rect);

}

void fillFood(SDL_Renderer* ren)// fill màu cho từng rect thuc an
{
	SDL_SetRenderDrawColor(ren, 120, 30, 255, 0xFF);
	SDL_RenderFillRect(ren, &fruitPosition);
}

void START_GAME()
{
	snakePosition.x = rand() % 20 * 30;
	snakePosition.y = rand() % 20 * 30;
	fruitPosition.x = rand() % 20 * 30;
	fruitPosition.y = rand() % 20 * 30;
	cout << "snakeRandom " << snakePosition.x << " " << snakePosition.y << endl;
	SDL_Rect head = { snakePosition.x,snakePosition.y,30,30 };
	SNAKE.push_back(head);
	for (int i = 1; i <= 3; ++i)
	{
		SDL_Rect rec = { snakePosition.x - i * 30, snakePosition.y,30,30 };
		SNAKE.push_back(rec);
	}
	SDL_SetRenderDrawColor(screen, 150, 150, 150, 0xFF);
	SDL_RenderClear(screen);
	for (auto x : SNAKE)
	{
		SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(screen, &x);
	}
	fillFood(screen);
	cout << "SNAKE[0] " << snakePosition.x << " " << snakePosition.y << endl;
}


void close() { //closes everything properly
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


bool vaCham()
{
	bool vacham = false;

	int x_rightbottom = snakePosition.x + 30;
	int y_rightbottom = snakePosition.y + 30;

	int x_leftbottom = snakePosition.x ;
	int y_leftbottom = snakePosition.y + 30;

	int x_righttop = snakePosition.x + 30;
	int y_righttop = snakePosition.y;

	int x_lefttop = snakePosition.x ;
	int y_lefttop = snakePosition.y ;

	if (x_rightbottom<fruitPosition.x + 30*2 && x_rightbottom>fruitPosition.x && y_rightbottom < fruitPosition.y+30*2 && y_rightbottom > fruitPosition.y)
	{
		vacham = true;
	}
	if (x_righttop<fruitPosition.x + 30*2 && x_righttop>fruitPosition.x && y_righttop < fruitPosition.y + 30*2 && y_righttop > fruitPosition.y)
	{
		vacham = true;
	}
	if (x_leftbottom<fruitPosition.x + 30*2 && x_leftbottom>fruitPosition.x && y_leftbottom < fruitPosition.y + 30*2 && y_leftbottom > fruitPosition.y)
	{
		vacham = true;
	}
	if (x_lefttop<fruitPosition.x + 30*2 && x_lefttop>fruitPosition.x && y_lefttop < fruitPosition.y + 30*2 && y_lefttop > fruitPosition.y)
	{
		vacham = true;
	}

	return vacham;
}


void taiSnake(SDL_Renderer* ren)
{


	SNAKE[0].x = snakePosition.x;
	SNAKE[0].y = snakePosition.y;
	int prev_x = SNAKE[0].x;
	int prev_y = SNAKE[0].y;
	SDL_SetRenderDrawColor(ren, 150, 150, 150, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 177, 177, 117, 0xFF);
	SDL_RenderFillRect(ren,&SNAKE[0]);
	//SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
	//SDL_RenderFillRect(ren, &rect);
	for (int i = 0; i < SNAKE.size() ; ++i)
	{
		int prev2_x = SNAKE[i].x;
		int prev2_y = SNAKE[i].y;
		SNAKE[i].x = prev_x;
		SNAKE[i].y = prev_y;
		prev_x = prev2_x;
		prev_y = prev2_y;
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(ren, &SNAKE[i]);
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
				case SDLK_RIGHT: snakePosition.x+= 30; break;
				default: snakePosition.x = 200; snakePosition.y = 200; break;
				}
				cout << "x: " << snakePosition.x << " y: " << snakePosition.y << endl;
				taiSnake(screen);

				if(vaCham())//check va cham fruit
				{
					fruitPosition.x = rand() % 20 * 30;
					fruitPosition.y = rand() % 20 * 30;
				}
				fillFood(screen);
			}
			
			
		}
		SDL_RenderPresent(screen);
		
	}
	close();
	std::cout << SNAKE.size();
	return 0;
}
