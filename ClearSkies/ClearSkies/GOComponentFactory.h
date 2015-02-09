#ifndef GOCOMPONENTFACTORY_H_INCLUDED
#define GOCOMPONENTFACTORY_H_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include "GOComponent.h"
#include "GOCompOwner.h"
#include <File.h>
class GOComponentFactory;
typedef Singleton<GOComponentFactory> TheGOComponentFactory;
class GOComponentFactory: public NonCopyable
{
private:
	typedef std::map<int,GOComponent*> CompMap;
	typedef GOComponent* (*CreateFun)();
	typedef std::map<std::string,CreateFun> FactoryMap;
public:
	GOComponent* CreateComponent(const std::string& type);
	bool AddComponentFunc(const std::string& key, CreateFun create);
	void LoadComponents(GOCompOwner& compOwner,File* file);
private:
	FactoryMap factoryMap_;
};


#endif