#include"commonFunc.h"
#include"baseobject.h"

baseObject::baseObject()
{
	object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = tile_frame;
	rect_.h = tile_frame;
};

baseObject::~baseObject()
{
	if (object_ != NULL)
	{
		
		SDL_DestroyTexture(object_);
	}
	object_ = NULL;
}

bool baseObject::loadImg(std::string path,SDL_Renderer* ren)
{
	Free();
	bool loadOk = true;
	SDL_Texture* new_text = NULL;
	SDL_Surface* sur = NULL;
	sur = SDL_LoadBMP(path.c_str());
	if (sur == NULL)
	{
		std::cout << "sur == NULL" << std::endl;
		loadOk = false;
		return loadOk;
	}
	else
	{
		rect_.w = sur->w;
		rect_.h = sur->h;
		SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_text = SDL_CreateTextureFromSurface(ren, sur);
		object_ = new_text;

		SDL_FreeSurface(sur);
	}
	if (new_text == NULL)
	{
		std::cout << "ERROR NEW TEXT=NULL" << std::endl;
		loadOk = false;
		return loadOk;
	}
	return loadOk;
};

void baseObject::render(SDL_Renderer* ren,SDL_Rect* rec)
{
	SDL_RenderCopy(ren, object_, NULL, rec);
}

void baseObject::Free()
{
	if (object_ != NULL)
	{
		
		SDL_DestroyTexture(object_);
	}
	object_ = NULL;
}

