#pragma once
#ifndef APP_H
#define APP_H
#include "include_user.h"
#include "Double_list.h"
#include "widget_DLList.h"

extern Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
extern NodeMini Item, menuNode10, menuNode20, menuNode30;//ͷ�ڵ�
extern List_node linked, menuLinked1;//����һ��MenuItem����һ������
extern List_node menuLinked2;
extern List_node menuLinked3;
extern Node* array[3];
extern MenuItem menuGrade1, menuGrade2, menuGrade3;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//�������϶˵ĳ�ʼ��
void mainBasicInit();
//���в˵���ʼ��
void menuInitialization();
//�û��˵���ʼ���������������������ʼ�����ݣ�
void menuUserInitialization(int8_t userPass);

//�����������Ͷ���
void passwordGUI();
//�˵�����
void menuGUI(MenuItem MenuGrade);

#endif // !APP_H
