#ifndef FOOD_H_
#define FOOD_H_

#include"baseobject.h"
#include"commonFunc.h"
#include"snak.h"


class food :public baseObject
{
public:
	void setup_and_render(SDL_Renderer* ren)
	{
		rect_ = { (rand() % 34+1) * tile_frame, (rand() % 23+1) * tile_frame, tile_frame, tile_frame };
		SDL_RenderCopy(ren, object_, NULL, &rect_);
	};
	void setupAgain1P(SDL_Renderer* ren,snake SNAKEran)
	{
		reRamdom:
		vector<SDL_Rect> ran_copy = SNAKEran.diachiRan();
		int x_rec = (rand() % 34 + 1) * tile_frame;
		int y_rec = (rand() % 23 + 1) * tile_frame;
		for (int i = 0; i < ran_copy.size(); ++i)
		{
			if (x_rec == ran_copy[i].x || y_rec == ran_copy[i].y)
			{
				goto reRamdom;//Có thể thấy khi mà rect thức ăn tạo ra trùng với 1 bộ phận nào đó của con rắn thì ta sẽ cho chương trình lùi về vị trí tạo rect và chạy lại qusa trình so sánh vị trí để cho vị trí thức ăn không trung con rắn 
			}
		}
		rect_ = { (rand() % 34+1) * tile_frame, (rand() % 23+1) * tile_frame, tile_frame, tile_frame };
	};
	
protected:

} ;


#endif 

