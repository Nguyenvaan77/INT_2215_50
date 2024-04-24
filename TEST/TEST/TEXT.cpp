#include"TEXT.h"

TextObject::TextObject()
{
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	text = NULL;
}

TextObject::~TextObject()
{
	if (text != NULL)
	{
		SDL_DestroyTexture(text);
	}
	text = NULL;
};

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	if (text != NULL)
	{
		SDL_DestroyTexture(text);
	}

	SDL_Surface* sur = NULL;
	sur = TTF_RenderText_Solid(font, str_val.c_str(),textColor);
	if (sur == NULL)
	{
		std::cout << "ERROR LOAD FONT 1" << std::endl;
		return false;
	}
	else
	{
		text = SDL_CreateTextureFromSurface(screen, sur);
		width = sur->w;
		height = sur->h;
		SDL_FreeSurface(sur);
	}
	if (text != NULL)
	{
		
		return true;
	}
	else
	{
		std::cout << "LOAD FONT ERROR 2" << std::endl;
		return false;
	}
}

void TextObject::Free()
{
	if (text != NULL)
	{
		SDL_DestroyTexture(text);
		text = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
};

void TextObject::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		textColor = color;
	}
	if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 };
		textColor = color;
	}
	if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0,0,0 };
		textColor = color;
	}
}

void TextObject::RenderText(SDL_Renderer* ren,int xp, int yp,bool scoreingame)
{
	if (scoreingame)
	{
		SDL_Rect rec = { 0,0, width,height };
		SDL_Rect rec1 = { xp,yp,width,height };
		SDL_RenderCopy(ren, text, NULL, &rec1);
	}
	else
	{
		SDL_Rect rec1 = { xp,yp,600,300 };
		SDL_RenderCopy(ren, text, NULL, &rec1);
	}
}

