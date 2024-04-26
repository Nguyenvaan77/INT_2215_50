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
	void resetScore();
	void updateScore();
	int  finalScore();
	int getHIGHESTSCORE() { return HIGHESTSCORE; };
	bool checkWIN(int numberplayer);

	void SCORE_to_STRING();
	void SCORE_to_STRINGplayer1();
	void SCORE_to_STRINGplayer2();

	bool newHighest();//Check điểm có phải cao nhất không và thay thế nếu turn này cao nhất 

	void intscore_toString(int n) {
		score = n;
	}

protected:
	int score;
	 int HIGHESTSCORE;
};

#endif // !SCORE_H_

