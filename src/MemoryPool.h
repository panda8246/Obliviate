#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include "MemoryChunk.h"


class MemoryPool {
	
public:
	
	/**
	 * @brief Get the Instance object
	 * 
	 * 单例模式返回MemoryPool实例
	 * 
	 * @return MemoryPool* 
	 */
	static MemoryPool* GetInstance();


	/**
	 * @brief 外部调用的申请内存函数
	 * 
	 * @param size 申请的字节数
	 * @return void* 返回的块内存地址
	 */
	void* Allocate(int size);


	/**
	 * @brief 返还内存
	 * 
	 * @param p 返还的内存地址
	 */
	void Deallocate(void* p);


	/**
	 * @brief 根据申请内存的大小判断交由哪个Chunk管理
	 * 
	 * @param size 
	 * @return int 
	 */
	int Hash(int size);

private:

	MemoryPool();

	//实例
	static MemoryPool* Instance;

	//Chunk对应分配的字节：8	16	  32	64	  128	 256	512	   1024
	MemoryChunk* chunks[8];
	
};

#endif // !MEMORYPOOL_H
