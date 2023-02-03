#pragma once
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "include_user.h"
typedef struct MenuPoint MenuItem;

//这只是一个数据约定，是存入上端节点数组中的结构
typedef struct Double_item
{
	int16_t id;//id:内容的映射
	struct Double_item* prev;//上一个节点
	struct Double_item* next;//下一个节点
	void (*action)(void *paramter);//动作
	int8_t unit_flag;//单位，暂时未确定有多少个单位切换
	void (*gui)(void* paramter);//gui
	bool gui_status;//选择状态，布尔值false/true
	bool gui_option;//选项框，与gui_option_status组合使用，布尔值false/true
	bool gui_option_status;//选项框确定与否的状态，布尔值false/true
	void* subordinate;//节点的从属(均从属于链表节点)
}Node;


//mini是头节点，零时访问指针也可以用mini，可以减少存储量
typedef struct
{
	int16_t id;
	Node* prev;
	Node* next;
}NodeMini;

//控件链表
typedef struct
{
	Node* head;
	Node* tail;
	int16_t num;
	//始终指向上端显示链表的头节点和尾节点
	Node* visit;//节点访问指针,只在菜单的访问中使用该指针
}List_node;

struct MenuPoint
{
	List_node* linked_pointer;//链表指针
	bool menu_type;//菜单类型
	int8_t menu_grade;//当前菜单等级
	void** controlTank;//控件池
	struct MenuPoint* prev_MenuPoint;//上一级菜单指针
	struct MenuPoint** next_MenuArray;//下一级菜单数组
	void* (*menuPointAction)(void* paramter);//动作
};

int8_t linkedListInit(List_node* linked, NodeMini* Item);
int8_t linkedAddList(List_node* linked, Node* Item);
int8_t linkedDeleteList(List_node* linked, int16_t id);
//可变参将控件传入链表
void linkedNumAddList(List_node* linked, int16_t num, ...);
//清除链表
void linkedClearList(List_node* linked);

#endif // !DOUBLE_LIST_H

