/*
注意：mainGUI函数退回主界面还没有完善
	  menuUserInitialization移植时需要大部分修改
*/
#include "app.h"
#include "str_user.h"
//BITO:菜单初始化状态
//BIT1:退回主界面状态
//BIT2:密码输入模式
//BIT3:函数动作模式
//BIT4:菜单模式
//BIT5:
//BIT6:
//BIT7:
//按键的软件动作都是根据该状态判断
status BIT_flag = 2;
extern int8_t key_value;

//菜单节点
Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
//头节点
NodeMini Item, menuNode10, menuNode20, menuNode30;//头节点
//可选择的主界面上端显示链表
List_node linked;
//主界面上端节点数组
Node* array[MIN_SHOWTOP_LENGTH];
//菜单链表
List_node menuLinked1;//链表（一个MenuItem定义一个链表）
List_node menuLinked2;
List_node menuLinked3;

//菜单项
MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];
//在实际使用中，直接利用mainTank即可实现应用，不再关心创建的是什么数组
extern App_tank mainTank;

//数组访问下标
int8_t array_visit = 0;

//菜单项访问指针
extern MenuItem* menuVist;

void* actMenuItem(void* paramter);
/// <summary>
/// 主界面gui接口（默认显示界面）
/// </summary>
void mainGUI()
{
	if (GET_STATUS(BIT_flag, BIT1))
	{
		//在这里填入主界面GUI函数,主界面只在特定的状态刷新全主界面框架

		//清除全框架刷新
		//CLE_STATUS(BIT_flag, BIT1);
	}
	
}
/// <summary>
/// 输入密码的gui接口
/// </summary>
void passwordGUI()
{
	//主界面模式
	if (GET_STATUS(BIT_flag,BIT1)|| GET_STATUS(BIT_flag, BIT3))
	{
		print(UART_Send, "\r\n请输入按键值：");
	}
	//密码输入模式
	else if (GET_STATUS(BIT_flag,BIT2))
	{
		print(UART_Send, "\r\n请输入密码：");
	}
	
	keyboardValue();
	switch(key_value)
	{
	case 'm':
		//密码模式 
		SET_STATUS(BIT_flag, BIT2); CLE_STATUS(BIT_flag, BIT1); break;
	default: break;
	}
}
/// <summary>
/// 菜单gui显示到荧幕
/// </summary>
/// <param name="MenuGrade">
/// 菜单访问节点（需要自己定义访问指针）
/// </param>
void menuGUI(MenuItem* MenuGrade)
{
	int8_t i;
	Node* visit;
	if (GET_STATUS(BIT_flag, BIT1))
	{
		//linked.visit = linked.head->next;
		//linkedGui(linked);
		print(UART_Send, "\r\n");
		//CLE_STATUS(BIT_flag, BIT1);
	}
	while (GET_STATUS(BIT_flag, BIT2))
	{
		passwordGUI();
		//清除密码输入状态
		//CLE_STATUS(BIT_flag, BIT2);
		//创建菜单
		//menuInitCreat();
		//根据用户设定载入菜单和创建菜单
		menuUserInitialization(key_value);
	}
	if (GET_STATUS(BIT_flag, BIT4))
	{
		if ((*MenuGrade).menu_type == false)
		{
			visit = (*MenuGrade).linked_pointer->head;
			for (i = 0; i < (*MenuGrade).linked_pointer->num; i++)
			{
				//越过头节点
				visit = visit->next;
				visit->gui(visit);
			}
		}
		//array list
		else
		{
			for (i = 0; i < MIN_SHOWTOP_LENGTH; i++)
				((Node*)(*MenuGrade).controlTank[i])->gui((Node*)(*MenuGrade).controlTank[i]);
		}
	}
		
	
}
/// <summary>
/// 上一级动作
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 上一级的菜单地址
/// </returns>
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
/// <summary>
/// 下一级动作
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 下一级菜单地址
/// </returns>
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
/// <summary>
/// 查询上一个菜单节点
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 更新后的菜单项（更新菜单项中的菜单链表的访问节点）
/// </returns>
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
/// <summary>
/// 查询下一个菜单节点
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 更新后的菜单项（更新菜单项中的菜单链表的访问节点）
/// </returns>
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
/// <summary>
/// 进入下级菜单或当前菜单节点的动作
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 当前菜单项或下一级菜单
/// </returns>
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
/// <summary>
/// 返回上级菜单或返回主界面
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 上级菜单项或设置返回主界面标志
/// </returns>
MenuItem* appQUIT(void* paramter)
{
	//上一级菜单存在
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		if (((MenuItem*)paramter)->menu_type == true)
		{
			((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
			array_visit = 0;
			((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
		}
		//向上移动
		((MenuItem*)paramter) = appUP(paramter);
	}
	//上一级菜单不存在，则不响应（可以退回主界面）
	else
	{
		//这里应该填写退回主界面状态
		
		SET_STATUS(BIT_flag, BIT1);
		CLE_STATUS(BIT_flag, BIT3);
		CLE_STATUS(BIT_flag, BIT4);
		//mainGUI();
		//((MenuItem*)paramter)->linked_pointer->visit->action(paramter);
	}
	return ((MenuItem*)paramter);
}
/// <summary>
/// 依据按键执行相关的动作
/// </summary>
/// <param name="paramter">
/// 当前菜单项
/// </param>
/// <returns>
/// 当前菜单项或下一级菜单、下一级菜单
/// </returns>
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
		//paramter = NULL;
		break;
	}
	return (MenuItem*)paramter;
}


/// <summary>
/// 对主界面的上端初始化到mainTank.basicTank中,
/// 严格按照以下流程初始化,
/// 注册到控件池->属性动作绑定->初始化选择器链表
/// </summary>
void mainBasicInit()
{
	//注册上端控件并添加到控件池
	mainTank.basicTank = widgetInitialTank(array, MIN_SHOWTOP_LENGTH, &Item2, &Item3, &Item4);
	mainTank.basicLen = MIN_SHOWTOP_LENGTH;

	//属性和动作绑定
	setDLListControlAttribute(&Item2, 1, 0, true, true);
	setDLListControlEvent(&Item2, act, gui);

	setDLListControlAttribute(&Item3, 2, 0, true, false);
	setDLListControlEvent(&Item3, act, gui);

	setDLListControlAttribute(&Item4, 3, 0, true, false);
	setDLListControlEvent(&Item4, act, gui);

	//控件选择器初始化
	linkedListInit(&linked, &Item);
	//向选择器中添加指定内容
	linkedAddList(&linked, &Item2);


	linkedGui(linked);
}

//创建链表菜单
void menuInitCreat()
{
	//对菜单节点进行初始化
	setDLListControlAttribute(&menuNode1, 1, 0, false, false);
	setDLListControlEvent(&menuNode1, act, gui);

	setDLListControlAttribute(&menuNode2, 2, 0,  false, false);
	setDLListControlEvent(&menuNode2, act, gui);

	setDLListControlAttribute(&menuNode3, 1, 0,  false, false);
	setDLListControlEvent(&menuNode3, act, gui);

	setDLListControlAttribute(&menuNode4, 1, 0,  false, false);
	setDLListControlEvent(&menuNode4, act, gui);

	//菜单列表初始化
	linkedListInit(&menuLinked1, &menuNode10);
	linkedListInit(&menuLinked2, &menuNode20);
	linkedListInit(&menuLinked3, &menuNode30);

	//添加初始化状态
	SET_STATUS(BIT_flag, BIT0);
}

//依据userPass初始化菜单内容
//具有创建菜单的功能
void menuUserInitialization(int8_t userPass)
{
	if (!GET_STATUS(BIT_flag, BIT0))
	{
		menuInitCreat();
	}
	//每一次的重载都需要清零
	linkedClearList(&menuLinked1);
	linkedClearList(&menuLinked2);
	linkedClearList(&menuLinked3);
	if (userPass == 'h')
	{
		//将菜单节点添加到链表
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//链表下的菜单节点载入
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
		menuLinkedListArrayInitial(&menuGrade2_1, array, 3, actMenuItem);
	}
	if (userPass == 'i' || userPass == 'h')
	{
		//初始化菜单项节点
		menuLinkedListInitial(&menuGrade1, &menuLinked1, 1, actMenuItem, menuArray1);
		menuLinkedListInitial(&menuGrade2, &menuLinked2, 2, actMenuItem, menuArray2);
		menuLinkedListInitial(&menuGrade3, &menuLinked3, 2, actMenuItem, menuArray3);


		//上下级菜单的链接
		menuLinked(&menuGrade1, &menuGrade2, &menuGrade3);
		//注意：每一个菜单项都需要初始化后才能被链接（没有对菜单项进行初始化的，编译器将不会分配内存空间）
		menuLinked(&menuGrade2, &menuGrade2_1);

		menuVist = &menuGrade1;

		//CLE_STATUS(BIT_flag, BIT0);
		//进入菜单模式
		SET_STATUS(BIT_flag, BIT4);
		//清除主界面模式
		CLE_STATUS(BIT_flag, BIT1);
		CLE_STATUS(BIT_flag, BIT2);
	}
	else
	{
		//主界面模式
		SET_STATUS(BIT_flag, BIT1);
		//清除菜单模式
		CLE_STATUS(BIT_flag, BIT4);
	}
}

//菜单项的动作
//主要是用作菜单和按键的控制
void* actMenuItem(void* paramter)
{
	if(GET_STATUS(BIT_flag, BIT4))
		SET_STATUS(BIT_flag, BIT3);
	//passwordGUI();
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

void menuScheduler(MenuItem MenuGrade)
{
	static uint8_t flag = 1;
	static List_node* linkedVisit;
	if (GET_STATUS(BIT_flag, BIT4))
	{
		flag = 1;
		menuVist = menuVist->menuPointAction(menuVist);
	}
	if (GET_STATUS(BIT_flag, BIT1) && !GET_STATUS(BIT_flag, BIT4))
	{
		if (flag)
		{
			flag = 0;
			linkedVisit = &linked;
			linkedVisit->visit = linked.head;
		}
		//linkedGui(linkedVisit);
		linkedUserGui(linkedVisit);
	}
		
}