#include "MemoryPool.h"

MemoryPool* MemoryPool::Instance = nullptr;


MemoryPool* MemoryPool::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new MemoryPool();
	}
	return Instance;
}


MemoryPool::MemoryPool()
{
	//创建Chunk
	for (int i = 0; i < 8; ++i)
	{
		int size = pow(2, i + 3);
		chunks[i] = new MemoryChunk(size, 10);
	}
}


void* MemoryPool::Allocate(int size)
{
	int index = Hash(size);
	//申请的内存太大，直接向系统申请，不通过内存池管理
	if (index == -1)
	{
		Block* block = (Block*)malloc(size + sizeof(Block));
		block->isUsed = true;
		block->size = size;
		return (block + 1);
	}

	return chunks[index]->Allocate(size);
}


void MemoryPool::Deallocate(void* p)
{
	Block* block = (Block*)p - 1;
	int index = Hash(block->size);
	if (index == -1)
	{
	
		free(block);
	}
	else
	{
		chunks[index]->Deallocate(p);
	}
	
}

int MemoryPool::Hash(int size)
{
	if (size > chunks[7]->GetBlockSize())
		return -1;

	for (int i = 0; i < 8; ++i)
	{
		if (size <= chunks[i]->GetBlockSize())
			return i;
	}
	
	return -1;
}

void MemoryPool::PrintState()
{
	for (auto chunk : chunks)
	{
		std::cout << std::endl <<std::endl << "Chunk Size " << chunk->GetBlockSize() << " : " << std::endl;
		chunk->PrintMes();
	}
}