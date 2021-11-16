#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H

#include <malloc.h>
#include <iostream>
#include <cassert>

//��ʼ��ʱ������Block����
#define INIT_BLOCK_COUNT 10

struct Block
{
	//�����ǰ��ָ��
	Block* next;
	Block* prev;
	//Block����Ŀ��С
	int size;
	//�Ƿ񱻷���
	bool isUsed;
#ifdef _WIN64
	//����ֽ�
	char pad[7];		//64λ����8�ֽ����
#else // WIN64
	char pad[3];		//32λ����4�ֽ����
#endif
	
};

/**
 * @brief MemoryChunk��������͹��������ڴ�飬����Block�Ƕ�һ���������
 * 	һ��Chunk��Ӧ�����һ��BlockSize��������˫����ά���ѷ���Ϳ�ʹ�õ�Block��
 */
class MemoryChunk
{

public:
	
	/**
	 * @brief Construct a new Memory Chunk object
	 * 
	 * @param block_size һ��Block������ֽڴ�С
	 * @param init_count ��ʼ��ʱ���ɵ�Block��
	 */
	MemoryChunk(int block_size, int init_count = INIT_BLOCK_COUNT);

	/**
	 * @brief �����ڴ�
	 * 
	 * @param n ������ڴ��ֽ���
	 * @return void* ���ص��ڴ�ָ�� 
	 */
	void* Allocate(int n);

	/**
	 * @brief �����ڴ�
	 * 
	 * @param p ���ص��ڴ��ַ
	 */
	void Deallocate(void* p);

	//�����ϵͳ����һ���ڴ棬������Block������
	Block* NewBlock();


	/**
	 * @brief free�б��п���Block����ʱ����
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

	//�����ã������Ϣ
	void inline PrintMes() const
	{
		std::cout << "==== USED ====    " << used_count << std::endl;
		std::cout << "$$$$ FREE $$$$    " << free_count << std::endl;
	}

private:

	//ÿ��Block�Ĵ�С����λ���ֽڣ�
	const int BLOCK_SIZE;

	//ͳ��Block����
	int block_count;

	//��ʹ�õ�Block����ͷ
	Block* block_used_head;

	//δʹ�õ�Block����ͷ
	Block* block_free_head;

	//Block������ռ���ֽ���
	const int BLOCK_TYPE_SIZE;

	//ͳ���ѷ����Block����
	int used_count = 0;

	//ͳ�ƿɷ����Block����
	int free_count = 0;

	//�������� Ĭ��1.5
	double expansion_factor = 1.5;
};

#endif // !MEMORYCHUNK_H
