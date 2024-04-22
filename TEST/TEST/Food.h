#ifndef FOOD_H_
#define FOOD_H_

#include"baseobject.h"
#include"commonFunc.h"

class food :public baseObject
{
public:
	void setup_and_render(SDL_Renderer* ren)
	{
		rect_ = { (rand() % 34+1) * tile_frame, (rand() % 23+1) * tile_frame, tile_frame, tile_frame };
		SDL_RenderCopy(ren, object_, NULL, &rect_);
	};
	void setupAgain(SDL_Renderer* ren)
	{
		rect_ = { (rand() % 34+1) * tile_frame, (rand() % 23+1) * tile_frame, tile_frame, tile_frame };
	};
	
protected:

} ;


#endif 

