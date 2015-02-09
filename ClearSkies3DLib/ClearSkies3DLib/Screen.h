#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>
#include "Singleton.h"
#include "Vec2.h"
#include "Vec3.h"
#include "AABB2D.h"
#include "Matrix.h"
class Screen;
typedef Singleton<Screen> TheScreen;
class Screen : public NonCopyable
{
public:
    bool Init(int w, int h, unsigned int flag);
    void Flip();
    void Clear();
	bool InFrustrum(Matrix m, Vec3f pos);
	void SetPerspective();
	void DrawAABB2D(AABB2D&);
    SDL_Surface* GetScreen() const;
    Vec2<int> ScreenBounds();
private:
    int m_screenWidth;
    int m_screenHeight;
	bool m_isOpenGL;
    unsigned int m_flag;
    SDL_Surface* m_screenLoc;
    Screen();
    friend TheScreen;
};


#endif