#include "memory.h"

//uint8_t Memory[mem_size];
_mem_ _mem_t;

/// <summary>
/// 打印内存信息
/// </summary>
/// <param name="array">内存池</param>
void mem_info(char* array,uint16_t size)
{
	int a, b;
	printf("Array addr:%#x\r\n", array);
	for (a = 0; a < size; a++)
	{
		if ((a + 1) % 8)
			printf("%#x\t", ((char)(&array[a])) & 0xff);
		else
		{
			printf("%#x\t", ((char)(&array[a])) & 0xff);
			printf("\r\n");
			for (b = a - 7; b < a+1; b++)
				printf("%x\t", array[b] & 0xff);
			printf("\r\n----------------------------------------------------------------\r\n");
		}

	}
	if (size % 8 && (a == size))
	{
		printf("\r\n");
		for (a = a - size % 8; a < size; a++)
			printf("%x\t", array[a] & 0xff);
		printf("\r\n----------------------------------------------------------------\r\n");
	}
}

void init_mem()
{
	uint16_t i;
	if (Memory)
	{
		for (i = 0; i < mem_size; i++)
		{
			Memory[i] = 0;
		}
	}
	_mem_t.head = Memory;
	_mem_t.tail = NULL;
	_mem_t.size_16 = mem_size;
	_mem_t.size_end = 0;
}

void* malloc_ldx(uint16_t size_t)
{
	uint16_t num;
	mem_t* mem_t_;
	if (!_mem_t.head)
	{
		_mem_t.head = Memory;
		_mem_t.tail = NULL;
		_mem_t.size_16 = mem_size;
		_mem_t.size_end = 0;
	}
	if (_mem_t.size_16 < size_t + sizeof(mem_t))
		return NULL;
	if (_mem_t.tail == NULL)
	{
		num = mem_size - size_t;
		mem_t_ = (mem_t*)&Memory[0];
		mem_t_->pointer = &Memory[num];
		mem_t_->size_16 = size_t;
		_mem_t.tail = mem_t_;
		_mem_t.size_16 -= size_t+sizeof(mem_t);
		_mem_t.size_end += size_t;
	}
	else
	{
		num = mem_size - _mem_t.size_end - size_t;
		mem_t_ = (mem_t*)++_mem_t.tail;
		mem_t_->pointer = &Memory[num];
		mem_t_->size_16 = size_t;
		_mem_t.tail = mem_t_;
		_mem_t.size_16 -= size_t + sizeof(mem_t);
		_mem_t.size_end += size_t;
	}

	return mem_t_->pointer;
}

void free_ldx(void** pointer)
{
	mem_t* mem_t_, *mem_t_next,*mem_t_prev;
	uint16_t i;
	uint8_t* data;
	if (!_mem_t.head)
	{
		_mem_t.head = Memory;
		_mem_t.tail = NULL;
		_mem_t.size_16 = mem_size;
		_mem_t.size_end = 0;
		return;
	}
	else if(*pointer < _mem_t.head || *pointer > &Memory[mem_size-1])
		return;
	for (mem_t_ = _mem_t.head; mem_t_ <= _mem_t.tail; mem_t_++)
	{
		//查找删除内存
		if (mem_t_->pointer == *pointer)
			break;
	}
	if (mem_t_ > _mem_t.tail)
		return;
	//调整内存大小
	_mem_t.size_16 += mem_t_->size_16 + sizeof(mem_t);
	_mem_t.size_end -= mem_t_->size_16;
	//尾部删除修改（空间换时间）
	if (mem_t_ == _mem_t.tail)
	{
		if(_mem_t.tail == _mem_t.head)
			_mem_t.tail = NULL;
		else
			_mem_t.tail = --_mem_t.tail;
		*pointer = NULL;
		return;
	}
	else	//其他位置删除（时间换空间）
	{
		//将下一个节点的内存管理指针指向要删除的节点
		mem_t_next = mem_t_;
		for (; mem_t_next < _mem_t.tail; )
		{
			//指向下一个节点
			mem_t_next++;
			data = (uint8_t*)mem_t_next->pointer;
			data += mem_t_next->size_16-1;
			for (i = 0; i < mem_t_next->size_16; i++)
			{
				//数据迁移
				*(data + mem_t_->size_16) = *data;
				data--;
			}
			//修改控制块指向
			(uint8_t*)mem_t_next->pointer += mem_t_->size_16;
		}
		for (mem_t_next = mem_t_prev = mem_t_; mem_t_next < _mem_t.tail; ++mem_t_prev)
		{
			//控制块迁移
			mem_t_next++;
			mem_t_prev->pointer = mem_t_next->pointer;
			mem_t_prev->size_16 = mem_t_next->size_16;
			mem_t_prev->type = mem_t_next->type;
		}
		//清除最后数据增加内容（这一段代码用于调试）
		mem_t_next->pointer = NULL;
		mem_t_next->size_16 = NULL;
		mem_t_next->type = NULL;


		_mem_t.tail = --mem_t_next;

		*pointer = NULL;
	}
}

void* test(char* array)
{
	//在这里需要注意存储空间对齐的问题
	array[0] = 'c';
	array[1] = 'e';
	array[2] = 1000;
	array[3] = 1000>>8;
	return array;
}

