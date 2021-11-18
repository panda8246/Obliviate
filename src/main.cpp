//开启内存检测
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include <Windows.h>
#include <vector>
#include <stack>
#include"MemoryChunk.h"
#include "test/MyAllocate.h"
#include "MemoryPool.h"

struct MyStruct
{
	double a;
	double b;
	double c;
	double d;
};

void main() {

	std::cout << sizeof(MyStruct) << std::endl;

	MemoryChunk chunk(64);

	std::vector<int, MyAllocator<int>> vec(10);

	//std::stack<int, MyAllocator<int>> vec;

	while (1)
	{

		vec.push_back(9);

		Sleep(1);
	}
	
	//可在输出控制台中查看未释放内存的情况
	_CrtDumpMemoryLeaks();

	getchar();
}