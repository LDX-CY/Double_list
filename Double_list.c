#include"Double_list.h"

//ֻ����β������

// 3.��ʼ��ͷ�ڵ�
int8_t linkedListInit(Node *Item, List_node *linked)
{
	if(!Item||!linked)
		return DLLIST_INIT_ERROR;
	Item->action = NULL;
	Item->gui = NULL;
	Item->gui_status = false;
	Item->id = 0;
	//ָ��ͷ�ڵ㱾��
	Item->next = Item;
	Item->prev = Item;
	Item->unit_flag = NULL;
	//��ͷ�ڵ��������
	linked->head = Item;
	linked->tail = Item;
	return OK;
}
// 1.��ӽڵ�
int8_t linkedAddList(List_node* linked, Node* Item)
{
	if (!Item || !linked)
		return DLLIST_NULL_ERROR;
	//linked->tail = Item;
	Item->next = linked->head;
	Item->prev = linked->tail;
	linked->head->prev = Item;
	linked->tail->next = Item;
	linked->tail = Item;
	return OK;
}
// 2.ɾ���ڵ�

// 4.��ѯ����