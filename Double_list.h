#pragma once
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "include_user.h"

//��ֻ��һ������Լ�����Ǵ����϶˽ڵ������еĽṹ
typedef struct Double_item
{
	int16_t id;//id:���ݵ�ӳ��
	struct Double_item* prev;//��һ���ڵ�
	struct Double_item* next;//��һ���ڵ�
	void (*action)(void *paramter);//����
	int8_t unit_flag;//��λ����ʱδȷ���ж��ٸ���λ�л�
	void (*gui)(void* paramter);//gui
	bool gui_status;//ѡ��״̬������ֵfalse/true
}Node;

//�϶�����
typedef struct
{
	Node* head;
	Node* tail;
	int16_t num;
	//ʼ��ָ���϶���ʾ�����ͷ�ڵ��β�ڵ�
}List_node;



//�洢����
//Node *Showtop[MIN_SHOWTOP_LENGTH];



int8_t linkedListInit(List_node* linked, Node* Item);
int8_t linkedAddList(List_node* linked, Node* Item);
int8_t linkedDeleteList(List_node* linked, int16_t id);







#endif // !DOUBLE_LIST_H

