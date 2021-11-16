#include"MemoryChunk.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <stack>

#include "test/MyAllocate.h"

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
		/*
		MyStruct* p = (MyStruct*)chunk.Allocate(32);
		p->a = 0;
		p->b = 2;
		p->c = 2;
		p->d = -213;
		*/

		MyStruct* ms = (MyStruct*)malloc(100);
		MyStruct* ms2 = ms + 1;
		
		ms->a = 0;
		ms->b = 2;
		ms->c = 2;
		ms->d = -213;

		char ad[100 - 32];
		char* pt = ad;
		pt = (char*)ms;
		delete[](pt);

		ms2->a = 0;

		//vec.push_back(9);

		//chunk.Deallocate(p);
		Sleep(1);
	}

	getchar();
}