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

//创建控件池
Node** widgetInitialTank(Node** array,int8_t length, ...);
//控件注册到控件池
int8_t linkedLogin(Node** array, int8_t i, Node* Item);

int8_t linkedGui(List_node linked);
//所有的控件都调用同一个gui函数
void gui(void* paramter);
void act(void* paramter);

//控件的操作和控件池的操作
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_option, bool gui_option_status);
int8_t setDLListControlEvent( Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter));
void printBasicControlGui();
void printDataControlGui();
void printControlGui();
void clearBasicControlTank();
void clearDataControlTank();

//菜单设置
void menuLinkedListInitial(MenuItem* menuItem,
	List_node* menuLinked,
	int8_t menu_grade,
	void* (*menuPointAction)(void* paramter),
	MenuItem** menuArray);
//菜单类型为数组类型
void menuLinkedListArrayInitial(MenuItem* menuItem,
	void** controlTank,
	int8_t menu_grade,
	void* (*menuPointAction)(void* paramter));
//各级菜单的链接
int8_t menuLinked(MenuItem* menuHighGrade, ...);

#endif // !WIDGET_H
