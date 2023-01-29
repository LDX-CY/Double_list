#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "include_user.h"

//这只是一个数据约定，是存入上端节点数组中的结构
typedef struct Double_item
{
	int16_t id;//id:内容的映射
	struct Node* prev;//上一个节点
	struct Node* next;//下一个节点
	void (*action)(void *paramter);//动作
	int8_t unit_flag;//单位，暂时未确定有多少个单位切换
	void (*gui)(void* paramter);//gui
	bool gui_status;//选择状态，布尔值false/true
}Node;

typedef struct
{
	Node* head;
	Node* tail;
}List_node;

Node Showtop[MIN_SHOWTOP_LENGTH];



int8_t linkedListInit(Node* Item, List_node* linked);

#endif // !DOUBLE_LIST_H

