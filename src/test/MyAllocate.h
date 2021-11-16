
#include <iostream>
#include <atomic>
#include <memory>
#include <Windows.h>
#include <vector>
#include <list>

#include "MemoryPool.h"

using namespace std;


//ʵ���Լ��� Allocator

std::atomic_int g_memory_used(0);

/*****
 * 
 * ������
 * 
�̳��Զ���ʵ�� Allocator
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

	//����ת��
	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};

	//�����ڴ�
	Pointer allocate(SizeType n)
	{
		count = n;
		std::cout << "������Ҫ�ڴ����ˣ�  ======>  " << count << std::endl;
		return (T*)pool->Allocate(n * sizeof(T));
		//return (Base::allocate(n));
	}

	//�����ڴ�
	void deallocate(Pointer p, SizeType n)
	{
		std::cout << "���Ӳ��ź����ˣ�" << std::endl;
		g_memory_used.fetch_add(n * sizeof(T));
		pool->Deallocate(p);
		Base::deallocate(p, n);
	}

	MyAllocator() = default;

	template<typename U>
	MyAllocator(const MyAllocator<U>& other) : Base(other) { }
	~MyAllocator() = default;
};
