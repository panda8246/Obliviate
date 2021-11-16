#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H

#include <malloc.h>
#include <iostream>
#include <cassert>

//初始化时创建的Block数量
#define INIT_BLOCK_COUNT 10

struct Block
{
	//链表的前后指针
	Block* next;
	Block* prev;
	//Block负责的块大小
	int size;
	//是否被分配
	bool isUsed;
#ifdef _WIN64
	//填充字节
	char pad[7];		//64位机下8字节填充
#else // WIN64
	char pad[3];		//32位机下4字节填充
#endif
	
};

/**
 * @brief MemoryChunk负责申请和管理具体的内存块，其中Block是对一个块的描述
 * 	一个Chunk对应分配的一个BlockSize，由两个双链表维护已分配和可使用的Block。
 */
class MemoryChunk
{

public:
	
	/**
	 * @brief Construct a new Memory Chunk object
	 * 
	 * @param block_size 一个Block管理的字节大小
	 * @param init_count 初始化时生成的Block数
	 */
	MemoryChunk(int block_size, int init_count = INIT_BLOCK_COUNT);

	/**
	 * @brief 申请内存
	 * 
	 * @param n 申请的内存字节数
	 * @return void* 返回的内存指针 
	 */
	void* Allocate(int n);

	/**
	 * @brief 返还内存
	 * 
	 * @param p 返回的内存地址
	 */
	void Deallocate(void* p);

	//向操作系统申请一块内存，并创建Block描述它
	Block* NewBlock();


	/**
	 * @brief free列表中可用Block不足时扩容
	 * 
	 */
	void Expand();


	/**
	 * @brief Get the Block Size object
	 * 
	 * @return int 
	 */
	int inline GetBlockSize() const
	{
		return BLOCK_SIZE;
	}

	//测试用，输出信息
	void inline PrintMes() const
	{
		std::cout << "==== USED ====    " << used_count << std::endl;
		std::cout << "$$$$ FREE $$$$    " << free_count << std::endl;
	}

private:

	//每个Block的大小（单位：字节）
	const int BLOCK_SIZE;

	//统计Block数量
	int block_count;

	//已使用的Block链表头
	Block* block_used_head;

	//未使用的Block链表头
	Block* block_free_head;

	//Block类型所占的字节数
	const int BLOCK_TYPE_SIZE;

	//统计已分配的Block数量
	int used_count = 0;

	//统计可分配的Block数量
	int free_count = 0;

	//扩容因子 默认1.5
	double expansion_factor = 1.5;
};

#endif // !MEMORYCHUNK_H
