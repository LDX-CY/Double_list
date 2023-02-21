#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "include_user.h"

#define mem_size 100

uint8_t Memory[mem_size];

typedef struct tru 
{
	unsigned char first;
	unsigned char end;
	unsigned short int midd;
}stru;

//小型内存块的管理
typedef struct mem
{
	unsigned char type;//未使用内容
	unsigned short int size_16;//字节大小
	void* pointer;//内存地址
}mem_t;

//内存块的总管理
typedef struct memm
{
	mem_t* head;//内存块首地址
	unsigned short int size_16;//总的可用字节大小
	unsigned short int size_end;//已存储的内存大小（不包含控制节点）
	mem_t* tail;//小型内存块的管理节点，是最后一个
}_mem_;


//打印内存信息
void mem_info(char* array, uint16_t size);
void* test(char* array);

void init_mem();
void* malloc_ldx(uint16_t size_t);
void free_ldx(void** pointer);
#endif // ! MEMORY_H
