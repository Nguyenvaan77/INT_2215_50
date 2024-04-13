#ifndef FOOD_H_
#define FOOD_H_

#include"baseobject.h"
#include"commonFunc.h"

class food :public baseObject
{
public:
	void setup_and_render(SDL_Renderer* ren)
	{
		rect_ = { (rand() % 20) * 30, (rand() % 30) * 30, 30, 30 };
		SDL_RenderCopy(ren, object_, NULL, &rect_);
	};
	void setupAgain(SDL_Renderer* ren)
	{
		rect_ = { (rand() % 20) * 30, (rand() % 30) * 30, 30, 30 };
	};
	
protected:

} ;


#endif 

