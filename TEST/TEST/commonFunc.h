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

static Mix_Chunk* sound_click = NULL;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 725;
const int tile_frame = 25;//SCREEN_WIDTH/tile_frame=36 
const int FRAME_PER_SECOND = 15;
const int TOCDO = tile_frame;

const int COLOR_KEY_R = 99;
const int COLOR_KEY_G = 99;
const int COLOR_KEY_B = 99;

const int SIZE_FONT = 30;
const std::string FONT_ = "font//xe.ttf";

const int scoreWIN1payer = 700;

const int scoreWIN2player = 20;
const int time_to_win_2players = 60;
#endif // ! COMMON_H_