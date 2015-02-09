#ifndef ACTORFACTORY_H_INCLUDED
#define ACTORFACTORY_H_INCLUDED
#include "Actor.h"
#include <Singleton.h>
#include <NonCopyable.h>
#include <map>
class ActorFactory;
typedef Singleton<ActorFactory> TheActorFactory;
class ActorFactory:public NonCopyable
{
public:
	Actor* Create(std::string& name);
	void AddType(std::string& name,std::string& file);
private:
	ActorFactory();
	friend TheActorFactory;
	typedef std::map<std::string,std::string> TemplateLoadMap;
	TemplateLoadMap templateLoadMap_;
};

#endif