#include "widget_DLList.h"
#include "str_user.h"

App_tank mainTank;


//设置控件的属性
//id:控件id
//unit_flag:单位类型
//gui_status:选择状态
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_status,bool gui_option,bool gui_option_status)
{
	if (!Item)
		return WIDGET_ERROR;
	Item->id = id;
	Item->unit_flag = unit_flag;
	Item->gui_status = gui_status;
	Item->gui_option = gui_option;
	Item->gui_option_status = gui_option_status;
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

void printBasicControlGui(App_tank tank)
{
	int8_t length;
	for (length = 0;length < tank.basicLen;length++)
	{
		tank.basicTank[length]->gui(tank.basicTank[length]);
	}
}

void printDataControlGui(App_tank tank)
{
	int8_t length;
	for (length = 0; length < tank.dataLen; length++)
	{
		tank.dataTank[length]->gui(tank.basicTank[length]);
	}
}

//同时刷新basic和datatank
void printControlGui(App_tank tank)
{
	printBasicControlGui(tank);
	printDataControlGui(tank);
}



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
}