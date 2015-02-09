#include "CollisionSystem.h"
#include "ReportError.h"
void CollisionSystem::HandleCollision(GameObject* lgo, GameObject* rgo)
{
	TypePair tp(lgo->GetTypeName(),rgo->GetTypeName());
	CollisionMap::iterator it=m_collResponce.find(tp);

	if(it!=m_collResponce.end())
	{
		CollisionHandler ch = it->second;
		ch(lgo,rgo);
		return;
	}
	std::swap(lgo,rgo);
	tp.first=lgo->GetTypeName();
	tp.second=rgo->GetTypeName();
	it=m_collResponce.find(tp);
	if(it!=m_collResponce.end())
	{
		CollisionHandler ch = it->second;
		ch(lgo,rgo);
		return;
	}
	ReportError("Anti matter-Matter mix, no collision responce known");
}

bool CollisionSystem::AddCollisionHandler(const std::string& type1, const std::string& type2,CollisionHandler ch)
{
	TypePair tp(type1,type2);
	m_collResponce[tp]=ch;
	return true;
}