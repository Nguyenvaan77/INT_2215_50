#ifndef SCORE_H_
#define SCORE_H_


#include"TEXT.h"



class SCORE: public TextObject
{
public:
	SCORE();
	~SCORE();
	//inGame
	bool openFileScore();//Mở khi bắt đầu game để cài đặt điểm cao nhất 
	void resetScore(bool isRePlay);
	void updateScore();
	int  finalScore();


	void SCORE_to_STRING();

	bool newHighest();//Check điểm có phải cao nhất không và thay thế nếu turn này cao nhất 


protected:
	int score;
	int HIGHESTSCORE;
};

#endif // !SCORE_H_

