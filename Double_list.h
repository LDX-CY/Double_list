#pragma once
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "include_user.h"
typedef struct MenuPoint MenuItem;

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
	bool gui_option;//ѡ�����gui_option_status���ʹ�ã�����ֵfalse/true
	bool gui_option_status;//ѡ���ȷ������״̬������ֵfalse/true
	void* subordinate;//�ڵ�Ĵ���(������������ڵ�)
}Node;


//mini��ͷ�ڵ㣬��ʱ����ָ��Ҳ������mini�����Լ��ٴ洢��
typedef struct
{
	int16_t id;
	Node* prev;
	Node* next;
}NodeMini;

//�ؼ�����
typedef struct
{
	Node* head;
	Node* tail;
	int16_t num;
	//ʼ��ָ���϶���ʾ�����ͷ�ڵ��β�ڵ�
	Node* visit;//�ڵ����ָ��,ֻ�ڲ˵��ķ�����ʹ�ø�ָ��
}List_node;

struct MenuPoint
{
	List_node* linked_pointer;//����ָ��
	bool menu_type;//�˵�����
	int8_t menu_grade;//��ǰ�˵��ȼ�
	void** controlTank;//�ؼ���
	struct MenuPoint* prev_MenuPoint;//��һ���˵�ָ��
	struct MenuPoint** next_MenuArray;//��һ���˵�����
	void* (*menuPointAction)(void* paramter);//����
};

int8_t linkedListInit(List_node* linked, NodeMini* Item);
int8_t linkedAddList(List_node* linked, Node* Item);
int8_t linkedDeleteList(List_node* linked, int16_t id);
//�ɱ�ν��ؼ���������
void linkedNumAddList(List_node* linked, int16_t num, ...);
//�������
void linkedClearList(List_node* linked);

#endif // !DOUBLE_LIST_H

