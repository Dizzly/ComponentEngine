#include "BitmapFont.h"
#include <gl/glut.h>
bool BitmapFont::Load(const std::string& file, int w, int h,float sqrS)
{
	cellNum_.x=w;
	cellNum_.y=h;
	cellSize_.x=1.0f/(float)w;
	cellSize_.y=1.0f/(float)h;
	squareSize_=sqrS;
	if(tex_.Load(file))
	{
	return true;
	}

return false;
}

void BitmapFont::Draw(const std::string& words, int w, int h)
{
	float offset=0;
	float offY=0;

	glEnd();
	for(int i=0;i<words.size();++i)
	{
		int ascii=words[i];
		if(ascii==(int)'\n')
		{
		--offY;
		offset=0;
		continue;
		}
		float x=(ascii%cellNum_.x)*cellSize_.x;
		float y=(ascii/cellNum_.x)*cellSize_.y;
		tex_.Begin();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(x+cellSize_.x,y);
			glVertex2f(offset+squareSize_,offY+squareSize_);
			glTexCoord2f(x+cellSize_.x,y+cellSize_.y);
			glVertex2f(offset+squareSize_,offY+0);
			glTexCoord2f(x,y+cellSize_.y);
			glVertex2f(offset+0,offY+0);
			glTexCoord2f(x,y);
			glVertex2f(offset+0,offY+squareSize_);
		}
		glEnd();
		offset+=squareSize_;
	}


}
