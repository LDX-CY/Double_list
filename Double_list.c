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
//�ؼ�ѡ������ʼ��
int8_t linkedListInit(List_node* linked , NodeMini* Item)
{
	if(!Item||!linked)
		return DLLIST_INIT_ERROR;
	Item->id = 0;
	//ָ��ͷ�ڵ㱾��
	Item->next = (Node*)Item;
	Item->prev = (Node*)Item;
	//��ͷ�ڵ��������
	linked->head = (Node*)Item;
	linked->tail = (Node*)Item;
	linked->num = 0;//��ʼĬ�Ͻڵ���Ϊ0���򲻰���ͷ�ڵ㣩
	linked->visit = linked->head;//���ʽڵ�ָ��ͷ�ڵ�
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
	linked->visit = linked->head->next;
	linked->visit->gui_status = true;
	//����������
	Item->subordinate = linked;
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
	//ɾ��������ϵ
	Item->subordinate = NULL;
	//ɾ���ڵ�
	Item->prev->next = Item->next;
	Item->next->prev = Item->prev;

	linked->num--;

	
	
	return OK;
}

//�������
void linkedClearList(List_node* linked)
{
	linked->tail = linked->head;
	linked->head->next = linked->head;
	linked->head->prev = linked->head;
	linked->num = 0;
	linked->visit = linked->head;
}

//�ɱ�ν��ؼ���������
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