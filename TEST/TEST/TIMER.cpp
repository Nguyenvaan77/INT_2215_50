#include"commonFunc.h"
#include"TIMER.h"

TIME::TIME()
{
	start_tick = 0;
	pause_tick = 0;
	is_start = false;
	is_pause = false;
}

TIME::~TIME()
{

}

void TIME::start()
{
	is_start = true;
	is_pause = false;
	start_tick = SDL_GetTicks();
}

void TIME::stopGame()
{
	is_start = false;
	is_pause = false;
}

void TIME::pause()
{
	if (is_start == true && is_pause == false)
	{
		is_pause = true;
		pause_tick = SDL_GetTicks() - start_tick;
	}
}

void TIME::unpause()
{
	if (is_start == true && is_pause == true)
	{
		is_pause = false;
		start_tick = SDL_GetTicks() - pause_tick;
		pause_tick = 0;
	}
}

int TIME::get_ticks()
{
	if (is_start == true)
	{
		if (is_pause == true)
		{
			return pause_tick;
		}
		else
		{
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}

bool TIME::isStart()
{
	return is_start;
}

bool TIME::isPause()
{
	return is_pause;
}