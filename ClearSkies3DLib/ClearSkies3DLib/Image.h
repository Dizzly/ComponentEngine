#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <string>
#include <SDL_image.h>


class Image
{
public:
    Image();
    bool Load(const std::string& fileName);
    SDL_Surface* GetImage();
    void Draw(int x, int y);
    void Draw(SDL_Rect);

protected:
    SDL_Surface* m_imageLoc;

};

#endif