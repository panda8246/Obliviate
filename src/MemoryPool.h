#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include "MemoryChunk.h"


class MemoryPool {
	
public:
	
	/**
	 * @brief Get the Instance object
	 * 
	 * ����ģʽ����MemoryPoolʵ��
	 * 
	 * @return MemoryPool* 
	 */
	static MemoryPool* GetInstance();


	/**
	 * @brief �ⲿ���õ������ڴ溯��
	 * 
	 * @param size ������ֽ���
	 * @return void* ���صĿ��ڴ��ַ
	 */
	void* Allocate(int size);


	/**
	 * @brief �����ڴ�
	 * 
	 * @param p �������ڴ��ַ
	 */
	void Deallocate(void* p);


	/**
	 * @brief ���������ڴ�Ĵ�С�жϽ����ĸ�Chunk����
	 * 
	 * @param size 
	 * @return int 
	 */
	int Hash(int size);

private:

	MemoryPool();

	//ʵ��
	static MemoryPool* Instance;

	//Chunk��Ӧ������ֽڣ�8	16	  32	64	  128	 256	512	   1024
	MemoryChunk* chunks[8];
	
};

#endif // !MEMORYPOOL_H
