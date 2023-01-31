#include"Double_list.h"
#pragma warning(disable:4133)
//ֻ����β������

// 4.��������
//id��Ҫ���ҵ�id
Node* linkedChackList(List_node* linked, int16_t id)
{
	int16_t length;
	Node* Item;
	if (!linked)
		return NULL;
	if (!id)
		return 0;
	//ɾ���Ĳ������һ���ڵ�
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

// 3.��ʼ�������ͷ�ڵ�
//Item��ͷ�ڵ�
int8_t linkedListInit(List_node* linked , Node* Item)
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
	linked->num = 0;//��ʼĬ�Ͻڵ���Ϊ0���򲻰���ͷ�ڵ㣩
	return OK;
}
// 1.��ӽڵ�
//Item��Ҫ��ӵĽڵ�
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
// 2.ɾ���ڵ�
//id��Ҫɾ����id
int8_t linkedDeleteList(List_node* linked, int16_t id)
{
	Node *Item=0;
	Item = linkedChackList(linked, id);
	if (!Item)
		return DLLIST_ERROR;
	if (Item->id == linked->tail->id)
		linked->tail = Item->prev;
	//ɾ���ڵ�
	Item->prev->next = Item->next;
	Item->next->prev = Item->prev;

	linked->num--;

	
	
	return OK;
}
