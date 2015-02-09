#ifndef SMARTPOINTER_H_INCLUDED
#define SMARTPOINTER_H_INCLUDED
template<class T>
class SmartPointer;
class RefCounted
{
protected:
	RefCounted(): refCount_(0){};
private:
	template<class T>
	friend class SmartPointer;
	int refCount_;
};

template<class T>
class SmartPointer
{
public:
	SmartPointer(T* ptr=0) : ptr_(ptr){
		if(ptr_)
		{
			refObject_=ptr_;
			++refObject_->refCount_;
		}
		else
		{
			refObject_=0;
		}
	}

	SmartPointer(const SmartPointer<T>& rhs)
	{
		refObject_=rhs.refObject_;
		++refObject_->refCount_;
		ptr_=rhs.ptr_;
	}

	template<class O>
	SmartPointer<O> DynamicCast(SmartPointer<O> ptr)
	{
		O* v=dynamic_cast<O*>(ptr_);
		if(v!=0)
		{
		return SmartPointer<O>(v);
		}
		else
		{
		return NULL;
		}
	}

	~SmartPointer()
	{
		if(ptr_)
		{
			if(refObject_->refCount_==1)
			{
				delete ptr_;
			}
			else
			{
			--refObject_->refCount_;
			}
		}
	}

	void operator =(const SmartPointer<T>& rhs)
	{
		SmartPointer<T> temp(rhs);
		std::swap(rhs,this);
	}
	operator T*()
	{
		return ptr_;
	}

	T* operator->() const
	{
		return ptr_;
	}

private:
private:
	RefCounted* refObject_;
	T* ptr_;

};

#endif