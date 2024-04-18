#ifndef SNAKE_H_
#define SNAKE_H_

#include"commonFunc.h"
#include"baseobject.h"

using namespace std;

class snake
{
public:
	snake(SDL_Renderer*ren);
	~snake() { ; };

	void setpos(int a, int b) { HEAD.rect_.x = a;HEAD.rect_.y = b; HEAD.rect_.w = 30; HEAD.rect_.h = 30; };//set HEAD snake
	bool dangDichuyen() { return isMove; };
	void dichuyen(bool a) { isMove = a; }
	bool isAlive();                           // check chết chưa 
	bool bitWall();                           // đụng tường
	bool eatFood(SDL_Rect FOOD);              // check ăn quả
	bool bitHimSelf();                        //check tự cắn bản thân
	void addTail();                           // khi ăn quả thì sẽ được thêm phần đuôi 
	void updateTail(SDL_Renderer* ren);       // update vị trí rect và trạng thái dir của từng phần trong snake 
	bool setIMGforIterm(SDL_Renderer* ren);    // 1 phần nhỏ của showfullbodysnake phía dưới nhưng không dùng nữa 

	void tangScore();
	void inScore();

	void handleInput(SDL_Event &even);         // nhận sự kiện chỉ có bạn phím để thay đổi dir 

	

	void showfullbody(SDL_Renderer* ren);       // bản demo của showfullbodysnake phía dưới(ko dùng)
	
	

	void xulyDichuyen(bool ismove)                          // dùng để cho con rắn chạy tự động khi không nhân phím 
	{
		if (isMove)
		{
			switch (dirHead)
			{
			case 1: HEAD.rect_.y -= tile_frame; break;
			case 2:HEAD.rect_.y += tile_frame; break;
			case 3:HEAD.rect_.x -= tile_frame; break;
			case 4:HEAD.rect_.x += tile_frame; break;
			}
		}
	}

	bool showfullbodysnake(SDL_Renderer* ren,bool eat);// hàm render lên màn hình con rắn hoàn thiện 
	bool loadHEAD(int dir,SDL_Renderer*ren,bool eat);// hàm load thành phần của rắn theo từng trạng thái
	bool loadBODY(int dir_trc,int dir_now, SDL_Renderer* ren);//...
	bool loadTAIL(int dir, SDL_Renderer* ren);//...


	int dirHead;
protected:

	vector<SDL_Rect> SNAKE;
	vector<int> dir_of_iterm;

	baseObject HEAD;
	baseObject BODY;
	baseObject TAIL;

	bool alive = true;
	bool isMove = true;

	int score;
};



#endif 