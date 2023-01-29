#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "include_user.h"

//��ֻ��һ������Լ�����Ǵ����϶˽ڵ������еĽṹ
typedef struct Double_item
{
	int16_t id;//id:���ݵ�ӳ��
	struct Node* prev;//��һ���ڵ�
	struct Node* next;//��һ���ڵ�
	void (*action)(void *paramter);//����
	int8_t unit_flag;//��λ����ʱδȷ���ж��ٸ���λ�л�
	void (*gui)(void* paramter);//gui
	bool gui_status;//ѡ��״̬������ֵfalse/true
}Node;

typedef struct
{
	Node* head;
	Node* tail;
}List_node;

Node Showtop[MIN_SHOWTOP_LENGTH];



int8_t linkedListInit(Node* Item, List_node* linked);

#endif // !DOUBLE_LIST_H

