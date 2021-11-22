//开启内存检测
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include <Windows.h>
#include <vector>
#include <stack>
#include <time.h>

#include"MemoryChunk.h"
#include "test/MyAllocate.h"
#include "MemoryPool.h"
#include "test/StackAlloc.h"


struct MyStruct
{
	double a;
	double b;
	double c;
	double d;
};

#define ELEMENTS 1000000

#define REPS 10

clock_t start;

void main() {

	std::cout << sizeof(MyStruct) << std::endl;

	MemoryChunk chunk(64);

	//std::vector<int, MyAllocator<int>> vec(10);

	//std::stack<int, MyAllocator<int>> vec;
	
	
	//使用默认的分配器
	StackAlloc<int> defaultstack;
	start = clock();
	for (int j = 0; j < REPS; j++)
	{
		assert(defaultstack.empty());
		for (int i = 0; i < ELEMENTS / 4; i++) {
			// Unroll to time the actual code and not the loop
			defaultstack.push(i);
			defaultstack.push(i);
			defaultstack.push(i);
			defaultstack.push(i);
		}
		for (int i = 0; i < ELEMENTS / 4; i++) {
			// Unroll to time the actual code and not the loop
			defaultstack.pop();
			defaultstack.pop();
			defaultstack.pop();
			defaultstack.pop();
		}
	}
	std::cout << "Default Allocator Time: ";
	std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";


	//使用我的分配器
	StackAlloc<int, MyAllocator<int>> mystack;
	start = clock();
	for (int j = 0; j < REPS; j++)
	{
		assert(mystack.empty());
		for (int i = 0; i < ELEMENTS / 4; i++) {
			// Unroll to time the actual code and not the loop
			mystack.push(i);
			mystack.push(i);
			mystack.push(i);
			mystack.push(i);
		}
		for (int i = 0; i < ELEMENTS / 4; i++) {
			// Unroll to time the actual code and not the loop
			mystack.pop();
			mystack.pop();
			mystack.pop();
			mystack.pop();
		}
	}
	std::cout << "My Allocator Time: ";
	std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

	MemoryPool::GetInstance()->PrintState();
	

	/*
	while (1)
	{

		//vec.push_back(9);
		//vec.push(0);

		Sleep(1);
	}
	*/
	
	//可在输出控制台中查看未释放内存的情况
	_CrtDumpMemoryLeaks();

	getchar();
}