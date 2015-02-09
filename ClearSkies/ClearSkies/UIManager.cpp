#include "UIManager.h"
#include <gl/glut.h>
UIManager::UIManager()
{}

void UIManager::AddUIElement(const GOComponent* g)
{
	UIElements::iterator it= uis_.find(g);
	if(it==uis_.end())
	{
		uis_.insert(g);
	}
}

void UIManager::RemoveUIElement(const GOComponent* g)
{
	UIElements::iterator it= uis_.find(g);
	if(it!=uis_.end())
	{
		uis_.erase(it);
	}
}

void UIManager::DrawUIElements()const
{
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT_MODEL_TWO_SIDE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	for(UIElements::iterator it=uis_.begin();
		it!=uis_.end();
		++it)
	{
		if((*it)->IsActive())
		{
			(*it)->Draw();
		}
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT_MODEL_TWO_SIDE);
	glPopMatrix();
}