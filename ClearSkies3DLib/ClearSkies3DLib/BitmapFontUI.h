#ifndef BITMAPFONTUI_H_INCLUDED
#define BITMAPFONTUI_H_INCLUDED
#include "Texture.h"
class BitmapFontUI
{
public:
	BitmapFontUI();
	bool Load(const std::string& file, int cellW, int cellH, float sqrS);
	void Draw(const std::string& words, Vec2f start,float size);
	void DynamicDraw(const std::string& words, Vec2f start, Vec2f end);
	
private:
	Texture tex_;
	Vec2i cellNum_;
	Vec2f cellSize_;
	float squareSize_;
};


#endif