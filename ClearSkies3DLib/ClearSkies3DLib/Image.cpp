#include "Image.h"
#include "Screen.h"
#include <assert.h>


Image::Image()
{
    m_imageLoc=0;
}

bool Image::Load(const std::string& fileName)
{
    m_imageLoc = IMG_Load(fileName.c_str());
    assert(m_imageLoc);
    return (m_imageLoc!=0);
}

SDL_Surface* Image::GetImage()
{
    return m_imageLoc;
}

void Image::Draw(int x, int y)
{
    SDL_Rect r= {x,y,0,0};
    SDL_BlitSurface(m_imageLoc, 0, TheScreen::Instance()->GetScreen(), &r);
}

void Image::Draw(SDL_Rect rect)
{
    SDL_Rect r;
    r.x=rect.x;
    r.y=rect.y;
    SDL_Rect crop;
    crop.x=0;
    crop.y=0;
    crop.w=rect.w;
    crop.h=rect.h;
    SDL_BlitSurface(m_imageLoc,&crop,TheScreen::Instance()->GetScreen(),&r);
}

