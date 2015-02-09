#include "Menu.h"
#include <ReportError.h>
#include <sstream>
Menu::Menu()
{}

bool Menu::Load(std::string load,LoadFunction func)
{
	if(func(load,*this))
	{
	menuName_=load;
	return true;
	}
	return false;
}

bool Menu::AddButton(Button* button)
{
	if(button->GetTag()==-1)
	{
		return false;
	}
	buttons_.push_back(button);
	return true;
}

void Menu::SetActive(bool b)
{
isActive_=b;
}

bool Menu::AddCall(int tag, Callback c)
{
	for(ButtonVec::iterator it=buttons_.begin();
		it!=buttons_.end();
		++it)
	{
		if((*it)->GetTag()==tag)
		{
			tagMap_[tag]=c;
			return true;
		}
	}
	return false;
}

void Menu::ClickAt(Vec2f click)
{
	if(isActive_)
	{
		Button* b=NULL;
		for(ButtonVec::iterator it=buttons_.begin();
			it!=buttons_.end();
			++it)
		{
			if((*it)->CheckCollision(click))
			{
				b=(*it);
				b->OnClick();
			}
		}
		if(b)
		{
			if(!tagMap_[b->GetTag()])
			{
				std::stringstream ss;
				ss<<"The button tag ";
				ss<<b->GetTag();
				ss<<" in ";
				ss<<menuName_;
				ss<<" does not have a function bound.\n";
				ReportError(ss.str());
			}
			tagMap_[b->GetTag()]();
		}
	}
}

void Menu::MouseMove(Vec2f move)
{
	if(isActive_)
	{
		for(ButtonVec::iterator it=buttons_.begin();
			it!=buttons_.end();
			++it)
		{
			if((*it)->CheckCollision(move))
			{
				(*it)->OnOver();
			}
			else
			{
				(*it)->OnUp();
			}
		}
	}
}

void Menu::Draw()
{
	if(isActive_)
	{
		for(ButtonVec::iterator it=buttons_.begin();
			it!=buttons_.end();
			++it)
		{
			(*it)->Draw();
		}
	}
}

void Menu::ClearButtons()
{
buttons_.clear();
}

