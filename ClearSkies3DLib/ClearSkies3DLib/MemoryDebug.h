#ifdef MEM_DEBUG
#ifndef MEMORYDEBUG_H_INCLUDED
#define MEMORYDEBUG_H_INCLUDED
#include <memory>
#include <map>
#include <iostream>
#include <fstream>

#undef new
struct Allocation
{
	Allocation(void* add=NULL, size_t s=0,const char* fileName="N/A",int lineNumber=0): 
		size_(s), 
		addr_(add), 
		lineNumber_(lineNumber), 
		fileName_(fileName)
	{}
	void* addr_;
	size_t size_;
	int lineNumber_;
	const char* fileName_;
};

std::ostream& operator<<(std::ostream& os, const Allocation& alloc);
void* operator new(size_t bytes);

void* operator new(size_t bytes,
	const char* fileName,
	int fileLine);



void operator delete(void* victim);
class AllocationManager
{
public:
	~AllocationManager(){
	//report leaks
	++depth_;
	};
	static AllocationManager* Instance(){
		static AllocationManager t;
		return &t;
	}
	void AddAllocation(Allocation& a){
		allocs_[a.addr_]=a;
	}
	void RemoveAllocation(void* a){
		allocs_.erase(a);
	}
	void WriteLeaks(){
		std::ofstream file;
		file.open("MemoryLeaks.txt");
		if(allocs_.empty())
		{
			std::cout<<"All is well in memory land\n";
			file<<"All is well in memory land\n";
		}
		for(AllocMap::iterator it = allocs_.begin();
			it!=allocs_.end();
			++it)
		{
			std::cout<< it->second;
			file<< it->second;
		}
	}
private:
	AllocationManager(){
	depth_=0;
	}
	friend void* operator new(size_t bytes);
	friend void* operator new(size_t bytes,
	const char* fileName,
	int fileLine);
	friend void operator delete(void* victim);
	AllocationManager(const AllocationManager&){}
private:
	typedef std::map<void*,Allocation> AllocMap;
	static int depth_;
	AllocMap allocs_;

};


#define new new(__FILE__,__LINE__)


#endif//include guard
#endif// MEM_DEBUG