#ifndef TEXT_H_
#define TEXT_H_

#include"commonFunc.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum MAU
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
	    BLACK_TEXT = 2,
	};

	
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* ren, int xp,  int yp,bool scoreingame);// score in game: hiện điểm tỏng game đang chơi, false là hiện khi kết thúc màn chơi 

	int GetWidth()const { return width; };
	int GetHeight() const { return height; };

	void SetText(const std::string& text) { str_val = text; };
	std::string GetText() const { return str_val; };

protected:
	std::string str_val;
	SDL_Color textColor;
	SDL_Texture* text;
	int width;
	int height;


};

#endif // !TEXT_H_
