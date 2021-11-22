
#include <iostream>
#include <atomic>
#include <memory>
#include <Windows.h>
#include <vector>
#include <list>

#include "MemoryPool.h"

using namespace std;


//实现自己的 Allocator

std::atomic_int g_memory_used(0);

/*****
 * 
 * 测试用
 * 
继承自定义实现 Allocator
****/
template<typename T>
class MyAllocator : public std::allocator<T>
{
public:
	using Base = std::allocator<T>;
	using Pointer = typename std::allocator_traits<Base>::pointer;
	using SizeType = typename std::allocator_traits<Base>::size_type;

public:

	MemoryPool* pool = MemoryPool::GetInstance();

	SizeType count = 0;

	//类型转换
	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};

	//分配内存
	Pointer allocate(SizeType n)
	{
		count = n;
		//std::cout << "管老子要内存来了？  ======>  " << count << std::endl;
		return (T*)pool->Allocate(n * sizeof(T));
		//return (Base::allocate(n));
	}

	//回收内存
	void deallocate(Pointer p, SizeType n)
	{
		//std::cout << "老子不伺候你了！" << std::endl;
		g_memory_used.fetch_add(n * sizeof(T));
		pool->Deallocate(p);
		//Base::deallocate(p, n);
	}

	//对已申请的内存初始化（构造）
	template <class U, class... Args> 
	void construct(U* p, Args&&... args)
	{
		new (p) U(std::forward<Args>(args)...);
	}

	MyAllocator() = default;

	template<typename U>
	MyAllocator(const MyAllocator<U>& other) : Base(other) { }
	~MyAllocator() = default;
};
