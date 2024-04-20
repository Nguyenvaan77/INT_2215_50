#include"score.h"

SCORE::SCORE()
{
	score = 0;
};

SCORE::~SCORE()
{

}

void SCORE::resetScore(bool isRePlay)
{
	if (isRePlay)
	{
		score = 0;
	};
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
	str_val = "Your score: "+std::to_string(score);
}

bool SCORE::openFileScore()
{
		std::ifstream highestsc;
		highestsc.open("score//highestScore.txt");
		if (!highestsc.is_open())
		{
			std::cout << "OPEN FILESETUP  ERROR" << std::endl;
			return false;
		}
		else
		{
			std::cout << "OPEN FILESETUP OK" << std::endl;
			highestsc >> HIGHESTSCORE;
			std::cout << "HIGHEST SCORE : " << HIGHESTSCORE << std::endl;
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
			std::cout << "OPEN FILE ERROR" << std::endl;
			return false;
		}
		else
		{
			std::cout << "OPEN FILE OK" << std::endl;
			HIGHESTSCORE = score;
			highestsc << HIGHESTSCORE;
			highestsc.close();
			return true;
		}
	}
	return false;
}

