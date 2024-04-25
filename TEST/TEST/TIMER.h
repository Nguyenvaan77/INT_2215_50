#ifndef TIME_H_
#define TIME_H_

#include"commonFunc.h"
#include"TEXT.h"

class TIME:public TextObject
{
public:
	TIME();
	~TIME();

	void start();
	void pause();
	void unpause();
	void stopGame();

	int get_ticks();

	bool isStart();
	bool isPause();

	int timeinGAME();


private:

	int start_tick;
	int pause_tick;

	bool is_start;
	bool is_pause;

};


#endif // !TIME_H_

