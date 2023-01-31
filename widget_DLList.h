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

int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_status);
int8_t setDLListControlEvent( Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter));
void printBasicControlGui(App_tank tank);
void printDataControlGui(App_tank tank);
void printControlGui(App_tank tank);
void clearBasicControlTank();
void clearDataControlTank();

#endif // !WIDGET_H
