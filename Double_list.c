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
//控件选择器初始化
int8_t linkedListInit(List_node* linked , NodeMini* Item)
{
	if(!Item||!linked)
		return DLLIST_INIT_ERROR;
	Item->id = 0;
	//指向头节点本身
	Item->next = (Node*)Item;
	Item->prev = (Node*)Item;
	//将头节点加入链表
	linked->head = (Node*)Item;
	linked->tail = (Node*)Item;
	linked->num = 0;//初始默认节点数为0（则不包含头节点）
	linked->visit = linked->head;//访问节点指向头节点
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
	linked->visit = linked->head->next;
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

//清除链表
void linkedClearList(List_node* linked)
{
	linked->tail = linked->head;
	linked->head->next = linked->head;
	linked->head->prev = linked->head;
	linked->num = 0;
	linked->visit = linked->head;
}

//可变参将控件传入链表
void linkedNumAddList(List_node* linked, int16_t num, ...)
{
	va_list ap;
#if (win64 == 1)
	__crt_va_start(ap, num);
#else
	va_start(ap, num);
#endif // (win64 == 1)
	for (int8_t i = 0; i < num; i++)
	{
		linkedAddList(linked,
#if (win64==1)
			__crt_va_arg(ap, Node*)
#else
			va_arg(ap, Node*)
#endif // (win64==1)
		);
	}
	
}