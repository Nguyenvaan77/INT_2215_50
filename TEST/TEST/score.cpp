﻿#include"score.h"

SCORE::SCORE()
{
	score = 0;
};

SCORE::~SCORE()
{

}

void SCORE::resetScore()
{
		score = 0;
}

void SCORE::updateScore()
{
	++score;
}

int SCORE::finalScore()
{
	return score;
}

void SCORE::SCORE_to_STRING()
{
	str_val = "Your score: "+ std::to_string(score);
}

void SCORE::SCORE_to_STRINGplayer1()
{
	str_val ="Player 1 : "+ std::to_string(score);
}

void SCORE::SCORE_to_STRINGplayer2()
{
	str_val = "Player 2 : " + std::to_string(score);
}

bool SCORE::openFileScore()
{
		std::ifstream highestsc;
		highestsc.open("score//highestScore.txt");
		if (!highestsc.is_open())
		{
			return false;
		}
		else
		{
			highestsc >> HIGHESTSCORE;
			highestsc.close();
			return true;
		}
		return false;
}

bool SCORE::newHighest()
{
	if (score > HIGHESTSCORE)// điểm chơi được cao hơn KỶ LỤC
	{
		std::fstream highestsc;
		highestsc.open("score//highestScore.txt", std::ios::in | std::ios::out);
		if (!highestsc.is_open())
		{
			return false;
		}
		else
		{
			HIGHESTSCORE = score;
			highestsc << HIGHESTSCORE;
			highestsc.close();
			return true;
		}
	}
	return false;
}

bool SCORE::checkWIN(int numberplayer)
{
	if (numberplayer == 1) {
		return score == scoreWIN1payer;
	}
	else
	{
		return score == scoreWIN2player;
	}
}
