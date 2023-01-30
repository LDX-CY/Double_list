#include"Double_list.h"
#pragma warning(disable:4133)
//只在链尾做运算

// 4.查找链表
//id：要查找的id
Node* linkedChackList(List_node* linked, int16_t id)
{
	int16_t length;
	Node* Item;
	if (!linked)
		return NULL;
	if (!id)
		return 0;
	//删除的不是最后一个节点
	Item = linked->tail;
	if (id != Item->id)
	{
		Item = linked->head;
		for (length = 0;length <= linked->num;length++)
		{
			if (Item->id != id)
				Item = Item->next;
			else
				break;
		}
		if (length > linked->num)
			return NULL;
	}
	return Item;
}

// 3.初始化链表和头节点
//Item：头节点
int8_t linkedListInit(List_node* linked , Node* Item)
{
	if(!Item||!linked)
		return DLLIST_INIT_ERROR;
	Item->action = NULL;
	Item->gui = NULL;
	Item->gui_status = false;
	Item->id = 0;
	//指向头节点本身
	Item->next = Item;
	Item->prev = Item;
	Item->unit_flag = NULL;
	//将头节点加入链表
	linked->head = Item;
	linked->tail = Item;
	linked->num = 0;//初始默认节点数为0（则不包含头节点）
	return OK;
}
// 1.添加节点
//Item：要添加的节点
int8_t linkedAddList(List_node* linked, Node* Item)
{
	if (!Item || !linked)
		return DLLIST_NULL_ERROR;
	Item->next = linked->head;
	Item->prev = linked->tail;
	linked->head->prev = Item;
	linked->tail->next = Item;
	linked->tail = Item;
	linked->num++;
	return OK;
}
// 2.删除节点
//id：要删除的id
int8_t linkedDeleteList(List_node* linked, int16_t id)
{
	Node *Item=0;
	Item = linkedChackList(linked, id);
	if (!Item)
		return DLLIST_ERROR;
	if (Item->id == linked->tail->id)
		linked->tail = Item->prev;
	//删除节点
	Item->prev->next = Item->next;
	Item->next->prev = Item->prev;

	linked->num--;

	
	
	return OK;
}
