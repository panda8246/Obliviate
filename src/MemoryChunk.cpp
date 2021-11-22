#include "MemoryChunk.h"


MemoryChunk::MemoryChunk(int block_size, int init_count) : 
	BLOCK_SIZE(block_size), block_count(0), block_used_head(nullptr), block_free_head(nullptr), BLOCK_TYPE_SIZE(sizeof(Block))
{
	//生成Blocks
	for (int i = 0; i < init_count; ++i)
	{
		NewBlock();
	}
}

void* MemoryChunk::Allocate(int size)
{
	//分配的大小应小于Block管理的最大字节
	assert(size <= BLOCK_SIZE);

	if (block_free_head == nullptr)
	{
		NewBlock();
	}
	Block* block = block_free_head;
	block_free_head = block_free_head->next;
	block->isUsed = true;
	if (block_used_head == nullptr)
	{
		
		block->next = nullptr;
		block->prev = nullptr;
		block_used_head = block;
	}
	else
	{
		block_used_head->prev = block;
		block->next = block_used_head;
		block->prev = nullptr;
		block_used_head = block;
	}

	++used_count;
	--free_count;

	if (free_count <= 1)
	{
		Expand();
	}

	//PrintMes();

	return (block + 1);
}


void MemoryChunk::Deallocate(void* p)
{
	--used_count;
	++free_count;

	Block* block = (Block*)p - 1;
	if (block->prev != nullptr)
	{
		block->prev->next = block->next;
	}
	else
	{
		block_used_head = block->next;
	}

	if (block->next != nullptr)
	{
		block->next->prev = block->prev;
	}
	
	block->isUsed = false;
	block->next = nullptr;
	block->prev = nullptr;
	if (block_free_head != nullptr)
	{
		block->next = block_free_head;
		if (block_free_head->next != nullptr)
		{
			block_free_head->next->prev = block;
		}
	}
	block_free_head = block;
}


Block* MemoryChunk::NewBlock()
{
	++free_count;

	int size = BLOCK_SIZE + BLOCK_TYPE_SIZE;
	void* pointer = malloc(size);
	Block* block = (Block*)pointer;
	block->isUsed = false;
	block->size = BLOCK_SIZE;
	block->next = block_free_head;
	block->prev = nullptr;
	if (block_free_head != nullptr)
	{
		block_free_head->prev = block;
	}
	block_free_head = block;
	return block;
}


void MemoryChunk::Expand()
{
	assert(expansion_factor > 1);
	int expansion_size = (expansion_factor - 1) * used_count + 1;
	for (int i = 0; i < expansion_size; ++i)
	{
		NewBlock();
	}
}