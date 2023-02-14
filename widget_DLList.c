#include "widget_DLList.h"
#include "str_user.h"

App_tank mainTank;

extern List_node linked;

//设置控件的属性
//id:			控件id
//unit_flag:		单位类型
//gui_status:		选择状态
//gui_option:		是否启用选项框
//gui_option_status:	选项框的选择状态
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_option,bool gui_option_status)
{
	if (!Item)
		return WIDGET_ERROR;
	Item->id = id;
	Item->unit_flag = unit_flag;
	Item->gui_status = false;
	Item->gui_option = gui_option;
	Item->gui_option_status = gui_option_status;
	Item->subordinate = NULL;
	return OK;
}

//绑定控件事件
int8_t setDLListControlEvent(Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter))
{
	if (!Item)
		return WIDGET_ERROR;
	Item->action = action;
	Item->gui = gui;
	return OK;
}
//输出基本ui
void printBasicControlGui()
{
	int8_t length;
	for (length = 0;length < mainTank.basicLen;length++)
	{
		mainTank.basicTank[length]->gui(mainTank.basicTank[length]);
	}
}
//输出测量结果ui
void printDataControlGui()
{
	int8_t length;
	for (length = 0; length < mainTank.dataLen; length++)
	{
		mainTank.dataTank[length]->gui(mainTank.basicTank[length]);
	}
}

//同时刷新basic和datatank
void printControlGui()
{
	printBasicControlGui();
	printDataControlGui();
}


//底层访问不使用访问指针
//打印gui，这是测试程序，打印的应该是根据用户选择打印和启动动作
int8_t linkedGui(List_node linked)
{
	Node* Item;
	int16_t length;
	if (linked.tail->id == linked.head->id)
		return WIDGET_ERROR;
	Item = linked.head;
	for (length = 0;length < linked.num;length++)
	{
		Item = Item->next;
#if (win64 == 1)
		Item->gui(Item);
#endif // (win64 == 1)
	}
	return OK;
}
extern int8_t key_value;
void linkedUserGui(List_node* linked)
{
	switch (key_value)
	{
	case LEFT:
		linked->visit = linked->visit->next;
		if (linked->visit == linked->head) linked->visit = linked->visit->next;
		break;
	case RIGHT:
		linked->visit = linked->visit->prev;
		if (linked->visit == linked->head) linked->visit = linked->visit->prev;
		break;
	default:
		break;
	}
	if (linked->head != linked->tail)
	{
		if (linked->visit->id == 0)
			linked->visit = linked->visit->next;
		linked->visit->gui(linked->visit);
	}
	
		
}


//为单个控件进行注册
int8_t linkedLogin(Node** array, int8_t i, Node* Item)
{
	if (!array)
		return WIDGET_ERROR;
	if (i >= MIN_SHOWTOP_LENGTH)
		i -= MIN_SHOWTOP_LENGTH;
	if (!i)
		return WIDGET_ERROR;
	if (array[i]->id != 0)
		return WIDGET_ERROR;
	array[i] = Item;
	return OK;
}

//创建控件池
Node** widgetInitialTank(Node** array,int8_t length,...)
{
	int8_t i;
	va_list ap;
#if (win64 == 1)
	__crt_va_start(ap, length);
#else
	va_start(ap, length);
#endif // (win64 == 1)
	for (i = 0;i < length;i++)
	{
#if (win64 == 1)
		array[i] = __crt_va_arg(ap, Node*);
#elif
		array[i] = va_arg(ap, Node*);
#endif // (win64 == 1)

	}
#if (win64 == 1)
	__crt_va_end(ap);
#else
	va_end(ap);
#endif // (win64 == 1)

	return array;
}

void clearBasicControlTank()
{
	mainTank.basicLen = 0;
	mainTank.basicTank = NULL;
}

void clearDataControlTank()
{
	mainTank.dataLen = 0;
	mainTank.dataTank = NULL;
}


//被选中的动作程序
void actNodeOptionIsTrue(void* paramter)
{
	linkedAddList(&linked, (Node*)paramter);
	if(linked.head->next->id != ((Node*)paramter)->id )
		linked.head->next->gui_status = false;
}
void actNodeOptionIsFalse(void* paramter)
{
	linkedDeleteList((List_node*)((Node*)paramter)->subordinate, ((Node*)paramter)->id);
}

void gui(void* paramter)
{
	//对option的支持
	if (((Node*)paramter)->gui_option)
	{
		if (((Node*)paramter)->gui_option_status)
			print(UART_Send, "[#]");
		else
			print(UART_Send, "[]");
	}
	if (((Node*)paramter)->gui_status != true)
		print(UART_Send, "[%d]", ((Node*)paramter)->id);
	else
	{
		print(UART_Send, ">%d<", ((Node*)paramter)->id);
	}
	//方便对数据的整合
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

void act(void* paramter)
{
	print(UART_Send, "\r\n当前是节点的act\r\n");
	//对option的支持
	if (((Node*)paramter)->gui_option)
	{
		((Node*)paramter)->gui_option_status = !((Node*)paramter)->gui_option_status;
		if (((Node*)paramter)->gui_option_status)
		{
			print(UART_Send, "[#]");
			//节点的添加
			actNodeOptionIsTrue(paramter);
		}	
		else
		{
			print(UART_Send, "[]");
			//节点的删除
			actNodeOptionIsFalse(paramter);
		}
	}
	if (((Node*)paramter)->gui_status != true)
		print(UART_Send, "[%d]\r\n", ((Node*)paramter)->id);
	else
	{
		print(UART_Send, ">%d<\r\n", ((Node*)paramter)->id);
	}
	//方便对数据的整合
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

/// <summary>
/// 菜单初始化
/// 必须在链表已经载入完成的情况下才能初始化菜单节点
/// </summary>
/// <param name="menuItem">菜单项</param>
/// <param name="menuLinked">菜单链表</param>
/// <param name="menu_grade">菜单等级</param>
/// <param name="menuPointAction">菜单项的动作</param>
/// <param name="menuArray">下级菜单数组</param>
void menuLinkedListInitial(MenuItem* menuItem, 
						   List_node* menuLinked, 
						   int8_t menu_grade, 
	                       void* (*menuPointAction)(void* paramter),
	                       MenuItem** menuArray)
{
	int8_t i;
	Node* node;
	menuItem->menu_grade = menu_grade;
	menuItem->linked_pointer = menuLinked;
	menuItem->menuPointAction = menuPointAction;
	menuItem->menu_type = false;
	menuItem->controlTank = NULL;
	menuItem->next_MenuArray = menuArray;
	menuItem->prev_MenuPoint = NULL;
	node = menuLinked->head;
	if (menuLinked->num > 0)
	{
		for (i = 0;i < menuLinked->num;i++)
		{
			node = node->next;
			//设置从属
			node->subordinate = menuItem;
		}
	}
	
}
//菜单控件池初始化
void menuLinkedListArrayInitial(MenuItem* menuItem,
	void** controlTank,
	int8_t menu_grade,
	void* (*menuPointAction)(void* paramter))
{
	menuItem->menu_grade = menu_grade;
	menuItem->linked_pointer = NULL;
	menuItem->menuPointAction = menuPointAction;
	menuItem->menu_type = true;
	menuItem->controlTank = controlTank;
	menuItem->next_MenuArray = NULL;
	menuItem->prev_MenuPoint = NULL;

}
//必须按照树状结构链接，否则链接失败，先树的树干后树的叶子等
//上一级菜单链接下一级菜单节点
//传入上一级菜单句柄，再依次传入下一级菜单句柄
//如果上一级菜单的控件节点项大于下一级菜单的所有项，则按照他的顺序传入NULL，否则出错
int8_t menuLinked(MenuItem* menuHighGrade,...)
{
	va_list ap;
	int8_t i;
	if (menuHighGrade->menu_grade < 1)
		return MENU_ERROR;
	if (menuHighGrade->menu_grade == 1)
	{
		menuHighGrade->prev_MenuPoint = NULL;
	}
	else if (menuHighGrade->prev_MenuPoint == NULL)
	{
		return MENU_ERROR;
	}
#if (win64 == 1)
	__crt_va_start(ap, menuHighGrade);
#else
	va_start(ap, menuHighGrade);
#endif // (win64 == 1)
	for (i = 0;i < menuHighGrade->linked_pointer->num;i++)
	{
#if (win64 == 1)
		menuHighGrade->next_MenuArray[i] = __crt_va_arg(ap, MenuItem*);
#else
		menuHighGrade->next_MenuArray[i] = va_arg(ap, MenuItem*);
#endif // (win64 == 1)	
		if(menuHighGrade->next_MenuArray[i]!=NULL)
			menuHighGrade->next_MenuArray[i]->prev_MenuPoint = menuHighGrade;
	}
#if (win64 == 1)
	__crt_va_end(ap);
#else
	va_end(ap);
#endif // (win64 == 1)

	return OK;
}