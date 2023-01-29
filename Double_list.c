#include"Double_list.h"

//只在链尾做运算

// 3.初始化头节点
int8_t linkedListInit(Node *Item, List_node *linked)
{
	if(!Item||!linked)
		return DLLIST_INIT_ERROR;
	//Item->action = NULL;
	//Item->gui = NULL;
	Item->gui_status = false;
	Item->id = 0;
	//指向头节点本身
	Item->next = Item;
	Item->prev = Item;
	Item->unit_flag = NULL;
	//将头节点加入链表
	linked->head = Item;
	linked->tail = Item;
	return OK;
}
// 1.添加节点
// 2.删除节点

// 4.查询链表