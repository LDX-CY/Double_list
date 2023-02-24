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

//С���ڴ��Ĺ���
typedef struct mem
{
	unsigned char type;//δʹ������
	unsigned short int size_16;//�ֽڴ�С
	void* pointer;//�ڴ��ַ
}mem_t;

//�ڴ����ܹ���
typedef struct memm
{
	mem_t* head;//�ڴ���׵�ַ
	unsigned short int size_16;//�ܵĿ����ֽڴ�С
	unsigned short int size_end;//�Ѵ洢���ڴ��С�����������ƽڵ㣩
	mem_t* tail;//С���ڴ��Ĺ���ڵ㣬�����һ��
}_mem_;


//��ӡ�ڴ���Ϣ
void mem_info(char* array, uint16_t size);
void* test(char* array);

void init_mem();
void* malloc_ldx(uint16_t size_t);
void free_ldx(void** pointer);
#endif // ! MEMORY_H
