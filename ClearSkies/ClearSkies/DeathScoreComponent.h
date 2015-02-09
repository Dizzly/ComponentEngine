#ifndef DEATHSCORECOMPONENT_H_INCLUDED
#define DEATHSCORECOMPONENT_H_INCLUDED
#include "GOComponentFactory.h"

class DeathScoreComponent:public GOComponent
{
public:
	void Draw()const override;
	void Update()override;
	const char* GetTypeName()const override;
	bool Load(File& file)override;
	bool Load(GOComponentLO* loadObj)override;
	void Destroy()override;
	void PassEvent(EventPtrList* eve)override;
public:
	static const char* TYPENAME;
private:
	int scoreValue_;
};


#endif