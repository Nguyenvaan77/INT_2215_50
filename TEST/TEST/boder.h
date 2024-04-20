#ifndef  BODER_H_
#define  BODER_H_

#include"commonFunc.h"
#include"baseobject.h"


class BODER :public baseObject
{
public:
	BODER() {};
	~BODER() {};

	void setIMG(SDL_Renderer* ren)
	{
		ngang.loadImg("anh//BODER//ngang.bmp", ren);
		doctrai.loadImg("anh//BODER//doc.bmp", ren);
		docphai.loadImg("anh//BODER//doc.bmp", ren);
	}

	void renderBoder(SDL_Renderer* ren)
	{
		ngang.setRect(0, 0);
		SDL_RenderCopy(ren, ngang.getObject(), NULL, &ngang.rect_);

		doctrai.setRect(0,30);
		SDL_RenderCopy(ren, doctrai.getObject(), NULL, &doctrai.rect_);

		docphai.setRect(SCREEN_WIDTH - 30, 30);
		SDL_RenderCopy(ren, docphai.getObject(), NULL, &docphai.rect_);
	}

private:
	baseObject ngang;
	baseObject doctrai;
	baseObject docphai;
};

#endif // ! BODER_H_

