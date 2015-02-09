#include "MemoryDebug.h"
#include <memory>
#include <map>
#include <iostream>
#include <fstream>

#undef new
int AllocationManager::depth_=1;

std::ostream& operator<<(std::ostream& o, const Allocation& a)
{
	return o << "Leak of "<< a.size_ << " bytes, at line number "<< a.lineNumber_<< " in file " << a.fileName_<<"!\n";
}


void* operator new(size_t bytes,
	const char* fileName,
	int fileLine)
{
	void* mem=malloc(bytes);
	++AllocationManager::Instance()->depth_;
	if(AllocationManager::Instance()->depth_==1)
	{
		AllocationManager::Instance()->AddAllocation(Allocation(mem,bytes,fileName,fileLine));
	}
	--AllocationManager::Instance()->depth_;
	return mem;
}

void* operator new(size_t bytes)
{
	void * mem=malloc(bytes);
	++AllocationManager::Instance()->depth_;
	if(AllocationManager::Instance()->depth_==1)
	{
		AllocationManager::Instance()->AddAllocation(Allocation(mem,bytes));
	}
	--AllocationManager::Instance()->depth_;
	return mem;
}

void operator delete(void* victim)
{
	if(victim)
	{
		++AllocationManager::Instance()->depth_;
		if(AllocationManager::Instance()->depth_==1)
		{
			AllocationManager::Instance()->RemoveAllocation(victim);
		}
		--AllocationManager::Instance()->depth_;
		free(victim);
	}
}
