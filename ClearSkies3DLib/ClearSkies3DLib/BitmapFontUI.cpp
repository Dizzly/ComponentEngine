#include "BitmapFontUI.h"

BitmapFontUI::BitmapFontUI()
{
	squareSize_=0;
}

bool BitmapFontUI::Load(const std::string& file, int cellXNum,int cellYNum, float cellSize)
{
	cellNum_.x=cellXNum;
	cellNum_.y=cellYNum;
	cellSize_.x=1.0f/(float)cellXNum;
	cellSize_.y=1.0f/(float)cellYNum;
	squareSize_=cellSize;
	if(tex_.Load(file))
	{
		return true;
	}
	return false;
}

void BitmapFontUI::DynamicDraw(const std::string& words, Vec2f start, Vec2f end)
{
	glPushMatrix();
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		GLboolean depth=0,light=0;
		glGetBooleanv(GL_LIGHTING,&light);
		glGetBooleanv(GL_DEPTH_TEST,&depth);
		if(light)
		{
			glDisable(GL_LIGHTING);
		}

		if(depth)
		{
			glDisable(GL_DEPTH_TEST);
		}
		float offset=0;
		float offY=0;
		int newLines=1;
		for(unsigned int i=0;i<words.size();++i)
		{
			if(words[i]=='\n')
			{
				++newLines;
			}
		}
		float tempX=abs(end.x-start.x)/words.size();
		float tempY=abs(end.y-start.y)/newLines;
		tex_.Begin();
		for(int i=0;i<words.size();++i)
		{
			int ascii=words[i];
			if(ascii==(int)'\n')
			{
				offY-=tempY;
				offset=0;
				continue;
			}
			float x=(ascii%cellNum_.x)*cellSize_.x;
			float y=(ascii/cellNum_.x)*cellSize_.y;
			
			glBegin(GL_QUADS);
			{
				glTexCoord2f(x+cellSize_.x,y);
				glVertex2f(start.x+offset+tempX,start.y+offY+tempY);
				glTexCoord2f(x+cellSize_.x,y+cellSize_.y);
				glVertex2f(start.x+offset+tempX,start.y+offY);
				glTexCoord2f(x,y+cellSize_.y);
				glVertex2f(start.x+offset,start.y+offY);
				glTexCoord2f(x,y);
				glVertex2f(start.x+offset,start.y+offY+tempY);
			}
			glEnd();
			offset+=tempX;
		}
		tex_.End();
		if(light)
		{
			glEnable(GL_LIGHTING);
		}
		if(depth)
		{
			glEnable(GL_DEPTH_TEST);
		}
	}
	glPopMatrix();

}
void BitmapFontUI::Draw(const std::string& words, Vec2f start,float size)
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLboolean depth=0,light=0;
	glGetBooleanv(GL_LIGHTING,&light);
	glGetBooleanv(GL_DEPTH_TEST,&depth);
	if(light)
	{
		glDisable(GL_LIGHTING);
	}

	if(depth)
	{
		glDisable(GL_DEPTH_TEST);
	}

	float offset=0;
	float offY=0;
	tex_.Begin();
	for(int i=0;i<words.size();++i)
	{
		int ascii=words[i];
		if(ascii==(int)'\n')
		{
			offY-=size;
			offset=0;
			continue;
		}
		float x=(ascii%cellNum_.x)*cellSize_.x;
		float y=(ascii/cellNum_.x)*cellSize_.y;
		glBegin(GL_QUADS);
		{
			glTexCoord2f(x+cellSize_.x,y);
			glVertex2f(start.x+offset+size,start.y+offY+size);
			glTexCoord2f(x+cellSize_.x,y+cellSize_.y);
			glVertex2f(start.x+offset+size,start.y+offY);
			glTexCoord2f(x,y+cellSize_.y);
			glVertex2f(start.x+offset,start.y+offY);
			glTexCoord2f(x,y);
			glVertex2f(start.x+offset,start.y+offY+size);
		}
		glEnd();
		offset+=size;
	}
	tex_.End();
	if(light)
	{
		glEnable(GL_LIGHTING);
	}

	if(depth)
	{
		glEnable(GL_DEPTH_TEST);
	}
	glPopMatrix();
}