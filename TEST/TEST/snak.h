#ifndef SNAKE_H_
#define SNAKE_H_

#include"commonFunc.h"
#include"baseobject.h"

static Mix_Chunk* sound_bit = NULL;

using namespace std;

class snake
{
public:
	snake(int indexPlayer);
	~snake() { ; };

	bool dangDichuyen() { return isMove; };
	void dichuyen(bool a) { isMove = a; }
	bool isAlive();                           // check chết chưa 
	bool bitWall();    // đụng tường
	bool nearlyFood(SDL_Rect FOOD);
	bool eatFood(SDL_Rect FOOD);              // check ăn quả
	bool eatSHIT();
	bool bitHimSelf();                        //check tự cắn bản thân
	void addTail();                           // khi ăn quả thì sẽ được thêm phần đuôi 
	void updateTail(SDL_Renderer* ren);       // update vị trí rect và trạng thái dir của từng phần trong snake 
	void peeShit();
	void handleInput(SDL_Event& even);         // nhận sự kiện chỉ có bạn phím để thay đổi dir 
	void setupPlay1();
	void setupPlay2();
	SDL_Rect getRectHEAD() { return HEAD.getRect(); };
	void xulyDichuyen(bool ismove)                          // dùng để cho con rắn chạy tự động khi không nhân phím 
	{
		if (isMove)
		{
			switch (dirHead)
			{
			case 1:HEAD.rect_.y -= TOCDO; break;
			case 2:HEAD.rect_.y += TOCDO; break;
			case 3:HEAD.rect_.x -= TOCDO; break;
			case 4:HEAD.rect_.x += TOCDO; break;
			}
		}
	}
	bool showfullbodysnake(SDL_Renderer* ren, SDL_Rect Food);// hàm render lên màn hình con rắn hoàn thiện 
	void renderShit(SDL_Renderer* ren);
	bool loadHEAD(int dir, SDL_Renderer* ren, bool eat);// hàm load thành phần của rắn theo từng trạng thái
	bool loadBODY(int dir_trc, int dir_now, SDL_Renderer* ren);//...
	bool loadTAIL(int dir, SDL_Renderer* ren);//...
	vector<SDL_Rect> diachiRan() { return SNAKE; };
	int printDiem() { return diem; };
	int getDIRHEAD() { return dirHead; };
	
protected:
	vector<SDL_Rect> SNAKE;
	vector<int> dir_of_iterm;
	vector<SDL_Rect> shit_on_map;

	baseObject HEAD;
	baseObject BODY;
	baseObject TAIL;
	baseObject shit;

	int index_of_player;

	bool alive = true;
	bool isMove = true;
	int dirHead;

	int diem;
};



#endif 