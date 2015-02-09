#ifndef BITMAPFONT_H_INCLUDED
#define BITMAPFONT_H_INCLUDED
#include "Texture.h"
#include <string>
class BitmapFont
{
public:
	bool Load(const std::string& file, int sheetWidth,int sheetHeight,float squareSize);
	void Draw(const std::string& words, int x, int y);
private:
	Texture tex_;
	Vec2i cellNum_;
	Vec2f cellSize_;
	float squareSize_;
};

#endif