#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include "include_user.h"
#include "Double_list.h"

typedef struct
{
	Node** basicTank;
	int8_t basicLen;
	Node** dataTank;
	int8_t dataLen;
}App_tank;


extern App_tank mainTank;

//�����ؼ���
Node** widgetInitialTank(Node** array,int8_t length, ...);
//�ؼ�ע�ᵽ�ؼ���
int8_t linkedLogin(Node** array, int8_t i, Node* Item);

int8_t linkedGui(List_node linked);
//���еĿؼ�������ͬһ��gui����
void gui(void* paramter);
void act(void* paramter);

//�ؼ��Ĳ����Ϳؼ��صĲ���
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_option, bool gui_option_status);
int8_t setDLListControlEvent( Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter));
void printBasicControlGui();
void printDataControlGui();
void printControlGui();
void clearBasicControlTank();
void clearDataControlTank();

void linkedUserGui(List_node* linked);

//�˵�����
void menuLinkedListInitial(MenuItem* menuItem,
	List_node* menuLinked,
	int8_t menu_grade,
	void* (*menuPointAction)(void* paramter),
	MenuItem** menuArray);
//�˵�����Ϊ��������
void menuLinkedListArrayInitial(MenuItem* menuItem,
	void** controlTank,
	int8_t menu_grade,
	void* (*menuPointAction)(void* paramter));
//�����˵�������
int8_t menuLinked(MenuItem* menuHighGrade, ...);

#endif // !WIDGET_H
