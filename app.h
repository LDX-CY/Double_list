#pragma once
#ifndef APP_H
#define APP_H
#include "include_user.h"
#include "Double_list.h"
#include "widget_DLList.h"

extern Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
extern NodeMini Item, menuNode10, menuNode20, menuNode30;//头节点
extern List_node linked, menuLinked1;//链表（一个MenuItem定义一个链表）
extern List_node menuLinked2;
extern List_node menuLinked3;
extern Node* array[3];
extern MenuItem menuGrade1, menuGrade2, menuGrade3;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//主界面上端的初始化
void mainBasicInit();
//所有菜单初始化
void menuInitialization();
//用户菜单初始化（根据输入参数决定初始化内容）
void menuUserInitialization(int8_t userPass);

//密码输入界面和动作
void passwordGUI();
//菜单界面
void menuGUI(MenuItem MenuGrade);

#endif // !APP_H
