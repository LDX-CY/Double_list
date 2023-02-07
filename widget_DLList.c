#include "widget_DLList.h"
#include "str_user.h"

App_tank mainTank;

extern List_node linked;

//���ÿؼ�������
//id:�ؼ�id
//unit_flag:��λ����
//gui_status:ѡ��״̬
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

//�󶨿ؼ��¼�
int8_t setDLListControlEvent(Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter))
{
	if (!Item)
		return WIDGET_ERROR;
	Item->action = action;
	Item->gui = gui;
	return OK;
}
//�������ui
void printBasicControlGui(App_tank tank)
{
	int8_t length;
	for (length = 0;length < tank.basicLen;length++)
	{
		tank.basicTank[length]->gui(tank.basicTank[length]);
	}
}
//����������ui
void printDataControlGui(App_tank tank)
{
	int8_t length;
	for (length = 0; length < tank.dataLen; length++)
	{
		tank.dataTank[length]->gui(tank.basicTank[length]);
	}
}

//ͬʱˢ��basic��datatank
void printControlGui(App_tank tank)
{
	printBasicControlGui(tank);
	printDataControlGui(tank);
}


//�ײ���ʲ�ʹ�÷���ָ��
//��ӡgui�����ǲ��Գ��򣬴�ӡ��Ӧ���Ǹ����û�ѡ���ӡ����������
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


//Ϊ�����ؼ�����ע��
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

//�����ؼ���
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


//��ѡ�еĶ�������
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
	//��option��֧��
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
	//��������ݵ�����
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

void act(void* paramter)
{
	print(UART_Send, "\r\n��ǰ�ǽڵ��act\r\n");
	//��option��֧��
	if (((Node*)paramter)->gui_option)
	{
		((Node*)paramter)->gui_option_status = !((Node*)paramter)->gui_option_status;
		if (((Node*)paramter)->gui_option_status)
		{
			print(UART_Send, "[#]");
			//�ڵ�����
			actNodeOptionIsTrue(paramter);
		}	
		else
		{
			print(UART_Send, "[]");
			//�ڵ��ɾ��
			actNodeOptionIsFalse(paramter);
		}
	}
	if (((Node*)paramter)->gui_status != true)
		print(UART_Send, "[%d]\r\n", ((Node*)paramter)->id);
	else
	{
		print(UART_Send, ">%d<\r\n", ((Node*)paramter)->id);
	}
	//��������ݵ�����
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

//�˵���ʼ��
//�����������Ѿ�������ɵ�����²��ܳ�ʼ���˵��ڵ�
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
			//���ô���
			node->subordinate = menuItem;
		}
	}
	
}
//�˵��ؼ��س�ʼ��
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
//���밴����״�ṹ���ӣ���������ʧ�ܣ����������ɺ�����Ҷ�ӵ�
//��һ���˵�������һ���˵��ڵ�
//������һ���˵�����������δ�����һ���˵����
//�����һ���˵��Ŀؼ��ڵ��������һ���˵����������������˳����NULL���������
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