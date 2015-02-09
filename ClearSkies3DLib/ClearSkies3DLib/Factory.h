#ifndef FACTORY_H_INCLUDED
#define FACTORY_H_INCLUDED
#include "NonCopyable.h"
#include <string>
#include <map>
#include <assert.h>


template<class T>
class Factory:public NonCopyable
{
typedef T* (*CreateFun)();
typedef std::map<std::string, CreateFun> FactoryMap;
public:
	T* Create(const std::string& name)
	{
		CreateFun create=factoryMap_[name];
		assert(create);
		if(!create)
		{
			return NULL;
		}
		return create();
	}
	bool AddType(const std::string& key, CreateFun create)
	{
		if(factoryMap_.find(key)==factoryMap_.end())
		{
			factoryMap_[key]=create;
			return true;
		}
		return false;
	}
private:
	FactoryMap factoryMap_;
};

#endif