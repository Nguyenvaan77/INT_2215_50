#ifndef TIME_H_
#define TIME_H_

class TIME
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

private:

	int start_tick;
	int pause_tick;

	bool is_start;
	bool is_pause;

};


#endif // !TIME_H_

