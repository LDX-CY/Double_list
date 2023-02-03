/*
注意：mainGUI函数退回主界面还没有完善
	  menuUserInitialization移植时需要大部分修改
*/
#include "app.h"
#include "str_user.h"
//BITO:菜单初始化状态
//BIT1:退回主界面状态
//BIT2:
//BIT3:
//BIT4:
//BIT5:
//BIT6:
//BIT7:
status BIT_flag = 0;
extern int8_t key_value;

Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
NodeMini Item, menuNode10, menuNode20, menuNode30;//头节点
List_node linked, menuLinked1;//链表（一个MenuItem定义一个链表）
List_node menuLinked2;
List_node menuLinked3;
Node* array[MIN_SHOWTOP_LENGTH];
MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//数组访问下标
int8_t array_visit = 0;

void* actMenuItem(void* paramter);

void mainGUI()
{
	if (SET_STATUS(BIT_flag, BIT1))
	{
		//在这里填入主界面GUI函数,主界面只在特定的状态刷新全主界面框架

		//清除全框架刷新
		CLE_STATUS(BIT_flag, BIT1);
	}
	
}
void passwordGUI()
{
	print(UART_Send, "\r\n请输入密码：");
}
void menuGUI(MenuItem MenuGrade)
{
	int8_t i;
	Node* visit;
	if (MenuGrade.menu_type == false)
	{
		visit = MenuGrade.linked_pointer->head;
		for (i = 0;i < MenuGrade.linked_pointer->num; i++)
		{
			visit = visit->next;
			visit->gui(visit);
		}
	}
	else
	{
		for(i=0;i< MIN_SHOWTOP_LENGTH;i++)
			((Node*)MenuGrade.controlTank[i])->gui((Node*)MenuGrade.controlTank[i]);
	}
	
	
}

MenuItem* appUP(void* paramter)
{
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		//确定当前菜单类型不是数组类型
		if(((MenuItem*)paramter)->menu_type != true)
			//向上访问将本级访问指针指向头节点
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head;
		((MenuItem*)paramter) = ((MenuItem*)paramter)->prev_MenuPoint;
	}
	return paramter;
}
MenuItem* appDOWN(void* paramter)
{
	
	if (((MenuItem*)paramter)->linked_pointer->num > 0)
	{
		((MenuItem*)paramter) = ((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id - 1];
		//链表模式
		if (((MenuItem*)paramter)->menu_type != true)
		{
			if (((MenuItem*)paramter)->linked_pointer->visit->id == 0)
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head->next;
		}
	}
	
	return paramter;
}
//上一个节点
MenuItem* appLEFT(void* paramter)
{
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//清除gui的选择状态
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = false;
		//保障菜单项下有菜单节点
		if (((MenuItem*)paramter)->linked_pointer->num > 0)
		{
			//当前节点如果是头节点,则指向下一个节点
			if (((MenuItem*)paramter)->linked_pointer->visit->id == 0)
			{
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->next;
			}

		}
		//先保证当前菜单下有至少2个菜单节点
		if (((MenuItem*)paramter)->linked_pointer->num > 1)
		{
			//如果访问指针指向了头节点
			if (((MenuItem*)paramter)->linked_pointer->visit->prev->id == 0)
			{
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->prev->prev;
			}
			else
			{
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->prev;
			}
		}
		//添加选择状态
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = true;
	}
	else
	{
		//清除前一个状态
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
		if (--array_visit < 0)
			array_visit = MIN_SHOWTOP_LENGTH - 1;
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
	}
		
	
	return paramter;
}
//下一个节点
MenuItem* appRIGHT(void* paramter)
{
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//清除gui的选择状态
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = false;
		//保障菜单项下有菜单节点
		if (((MenuItem*)paramter)->linked_pointer->num > 0)
		{
			//当前节点如果是头节点,则指向下一个节点
			if (((MenuItem*)paramter)->linked_pointer->visit->id == 0)
			{
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->next;
			}

		}
		//先保证当前菜单下有至少2个菜单节点
		if (((MenuItem*)paramter)->linked_pointer->num > 1)
		{
			//如果下一个节点指向的是头节点，那么指向头节点的下一个节点
			if (((MenuItem*)paramter)->linked_pointer->visit->next->id == 0)
			{
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head->next;
			}
			else
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->next;
		}
		//gui的选择状态为选中
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = true;
	}
	else
	{
		//清除前一个状态
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
		if (++array_visit >= MIN_SHOWTOP_LENGTH)
			array_visit = 0;
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
	}
	return paramter;
}
MenuItem* appENTER(void* paramter)
{
	//不是数组菜单
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//下一级菜单存在
		if (((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id - 1] != NULL)
		{
			//向下移动
			((MenuItem*)paramter) = appDOWN(paramter);
			//测试代码
			/*if (((MenuItem*)paramter)->menu_type != true)
				((MenuItem*)paramter)->linked_pointer->visit->gui(((MenuItem*)paramter)->linked_pointer->visit);
			else
				((Node*)((MenuItem*)paramter)->controlTank[0])->gui(((MenuItem*)paramter)->controlTank[0]);*/
		}
		//下级菜单不存在
		else
		{
			((MenuItem*)paramter)->linked_pointer->visit->action(((MenuItem*)paramter)->linked_pointer->visit);
			return ((MenuItem*)paramter);
		}
		return ((MenuItem*)paramter);
	}
	//数组菜单不存在下级菜单直接进入数组菜单的动作
	((Node*)((MenuItem*)paramter)->controlTank[array_visit])->action(((MenuItem*)paramter)->controlTank[array_visit]);
	return ((MenuItem*)paramter);
}
MenuItem* appQUIT(void* paramter)
{
	//上一级菜单存在
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		//向上移动
		((MenuItem*)paramter) = appUP(paramter);
	}
	//上一级菜单不存在，则不响应（可以退回主界面）
	else
	{
		//这里应该填写退回主界面状态
		
		SET_STATUS(BIT_flag, BIT1);
		//mainGUI();
		//((MenuItem*)paramter)->linked_pointer->visit->action(paramter);
	}
	return ((MenuItem*)paramter);
}
MenuItem* application(void* paramter)
{
	switch (key_value)
	{
	case LEFT:
		(MenuItem*)paramter = appLEFT(paramter);
		break;
	case RIGHT:
		(MenuItem*)paramter = appRIGHT(paramter);
		break;
	case ENTER:
		(MenuItem*)paramter = appENTER(paramter);
		break;
	case QUIT:
		(MenuItem*)paramter = appQUIT(paramter);
		break;
	default:
		//return choice;
		break;
	}
	return (MenuItem*)paramter;
}

//对主界面的上端初始化到mainTank.basicTank中
//严格按照以下流程初始化
//注册到控件池->属性动作绑定->初始化选择器链表
void mainBasicInit()
{
	//注册上端控件并添加到控件池
	mainTank.basicTank = widgetInitialTank(array, 3, &Item2, &Item3, &Item4);
	mainTank.basicLen = 3;

	//属性和动作绑定
	setDLListControlAttribute(&Item2, 1, 0, false, true, false);
	setDLListControlEvent(&Item2, act, gui);

	setDLListControlAttribute(&Item3, 2, 0, false, true, true);
	setDLListControlEvent(&Item3, act, gui);

	setDLListControlAttribute(&Item4, 3, 0, false, true, false);
	setDLListControlEvent(&Item4, act, gui);

	//控件选择器初始化
	linkedListInit(&linked, &Item);
	//向选择器中添加指定内容
	linkedAddList(&linked, array[0]);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedGui(linked);
}

//菜单初始化
void menuInitialization()
{
	//对菜单节点进行初始化
	setDLListControlAttribute(&menuNode1, 1, 0, false, false, false);
	setDLListControlEvent(&menuNode1, act, gui);

	setDLListControlAttribute(&menuNode2, 2, 0, false, false, false);
	setDLListControlEvent(&menuNode2, act, gui);

	setDLListControlAttribute(&menuNode3, 1, 0, false, false, false);
	setDLListControlEvent(&menuNode3, act, gui);

	setDLListControlAttribute(&menuNode4, 1, 0, false, false, false);
	setDLListControlEvent(&menuNode4, act, gui);

	//菜单列表初始化
	linkedListInit(&menuLinked1, &menuNode10);
	linkedListInit(&menuLinked2, &menuNode20);
	linkedListInit(&menuLinked3, &menuNode30);

	//添加初始化状态
	SET_STATUS(BIT_flag, BIT0);
}

//依据userPass初始化菜单内容
void menuUserInitialization(int8_t userPass)
{
	if (!GET_STATUS(BIT_flag, BIT0))
	{
		menuInitialization();
	}
	//每一次的载入都需要清零
	linkedClearList(&menuLinked1);
	linkedClearList(&menuLinked2);
	linkedClearList(&menuLinked3);
	if (userPass == 'h')
	{
		//将菜单节点添加到链表
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//链表下的菜单控件节点载入
		linkedNumAddList(&menuLinked1, 2, &menuNode1, &menuNode2);
		menuLinkedListArrayInitial(&menuGrade2_1, array, 3, actMenuItem);
	
	}
	else if (userPass == 'i')
	{
		//将菜单节点添加到链表
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//链表下的菜单控件节点载入
		linkedNumAddList(&menuLinked1, 1, &menuNode1);
		
	}
	
	//初始化菜单项节点
	menuLinkedListInitial(&menuGrade1, &menuLinked1, 1, actMenuItem, menuArray1);
	menuLinkedListInitial(&menuGrade2, &menuLinked2, 2, actMenuItem, menuArray2);
	menuLinkedListInitial(&menuGrade3, &menuLinked3, 2, actMenuItem, menuArray3);
	

	//上下级菜单的链接
	menuLinked(&menuGrade1, &menuGrade2, &menuGrade3);
	menuLinked(&menuGrade2, &menuGrade2_1);

	CLE_STATUS(BIT_flag, BIT0);
}

//菜单项的动作
void* actMenuItem(void* paramter)
{
	return application(paramter);
	//方便对数据的整合
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

//菜单节点的动作
void actMenuNode(void* paramter)
{
	//application(paramter);
	//方便对数据的整合
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}