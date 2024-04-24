#ifndef  COMMON_H_
#define  COMMON_H_

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
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<fstream>
#include<cmath>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 725;
const int tile_frame = 25;//SCREEN_WIDTH/tile_frame=36 
const int FRAME_PER_SECOND = 15;
const int TOCDO = tile_frame;

const int COLOR_KEY_R = 99;
const int COLOR_KEY_G = 99;
const int COLOR_KEY_B = 99;

const int SIZE_FONT = 40;
const std::string FONT_ = "font//xe.ttf";

enum TRANGTHAI
{
	up=1,
	down=2,
	left=3,
	right=4
};

bool checkdoidien(int trangthai1, int trangthai2);


#endif // ! COMMON_H_