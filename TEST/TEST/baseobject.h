#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include"commonFunc.h"

class baseObject
{
public:
	baseObject();
	~baseObject();
	void setRect(const int& a, const int& b) { this->rect_.x = a; this->rect_.y = b;  };
	SDL_Texture* getObject() { return object_; };
	bool loadImg(std::string path,SDL_Renderer* ren);
	void render(SDL_Renderer* ren,SDL_Rect* rec);
	SDL_Rect getRect() { return rect_; };
	void Free();


	SDL_Texture* object_;
	SDL_Rect     rect_;
};


#endif // !BASE_OBJECT_H_
