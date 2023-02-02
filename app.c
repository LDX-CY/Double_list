/*
ע�⣺mainGUI�����˻������滹û������
	  menuUserInitialization��ֲʱ��Ҫ�󲿷��޸�
*/
#include "app.h"
#include "str_user.h"
//BITO:�˵���ʼ��״̬
//BIT1:�˻�������״̬
//BIT2:
//BIT3:
//BIT4:
//BIT5:
//BIT6:
//BIT7:
status BIT_flag = 0;
extern int8_t key_value;

Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
NodeMini Item, menuNode10, menuNode20, menuNode30;//ͷ�ڵ�
List_node linked, menuLinked1;//����һ��MenuItem����һ������
List_node menuLinked2;
List_node menuLinked3;
Node* array[3];
MenuItem menuGrade1, menuGrade2, menuGrade3;
MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

void* actMenuItem(void* paramter);

void mainGUI()
{
	if (SET_STATUS(BIT_flag, BIT1))
	{
		//����������������GUI����,������ֻ���ض���״̬ˢ��ȫ��������

		//���ȫ���ˢ��
		CLE_STATUS(BIT_flag, BIT1);
	}
	
}
void passwordGUI()
{
	print(UART_Send, "\r\n���������룺");
}
void menuGUI(MenuItem MenuGrade)
{
	int8_t i;
	Node* visit = MenuGrade.linked_pointer->head;
	for (i = 0;i < MenuGrade.linked_pointer->num; i++)
	{
		visit = visit->next;
		visit->gui(visit);
	}
	
}

MenuItem* appUP(void* paramter)
{
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		//���Ϸ��ʽ���������ָ��ָ��ͷ�ڵ�
		((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head;
		((MenuItem*)paramter) = ((MenuItem*)paramter)->prev_MenuPoint;
	}
	return paramter;
}
MenuItem* appDOWN(void* paramter)
{
	if (((MenuItem*)paramter)->linked_pointer->num > 0)
	{
		((MenuItem*)paramter) = ((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id-1];
		if(((MenuItem*)paramter)->linked_pointer->visit->id==0)
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head->next;
	}
	return paramter;
}
//��һ���ڵ�
MenuItem* appLEFT(void* paramter)
{
	//�ȱ�֤��ǰ�˵���������2���˵��ڵ�
	if (((MenuItem*)paramter)->linked_pointer->num > 1)
	{
		//�������ָ��ָ����ͷ�ڵ�
		if (((MenuItem*)paramter)->linked_pointer->visit->prev->id == 0)
		{
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->prev->prev;
		}
		else
		{
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->prev;
		}
	}
	return paramter;
}
//��һ���ڵ�
MenuItem* appRIGHT(void* paramter)
{
	//���ϲ˵������в˵��ڵ�
	if (((MenuItem*)paramter)->linked_pointer->num > 0)
	{
		//��ǰ�ڵ������ͷ�ڵ�,��ָ����һ���ڵ�
		if (((MenuItem*)paramter)->linked_pointer->visit->id == 0)
		{
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->next;
		}
		
	}
	//�ȱ�֤��ǰ�˵���������2���˵��ڵ�
	if (((MenuItem*)paramter)->linked_pointer->num > 1)
	{
		//�����һ���ڵ�ָ�����ͷ�ڵ㣬��ôָ��ͷ�ڵ����һ���ڵ�
		if (((MenuItem*)paramter)->linked_pointer->visit->next->id == 0)
		{
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head->next;
		}
		else
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->visit->next;
	}
	//((MenuItem*)paramter)->linked_pointer->visit->gui(((MenuItem*)paramter)->linked_pointer->visit);
	return paramter;
}
MenuItem* appENTER(void* paramter)
{
	//��һ���˵�����
	if (((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id-1] != NULL)
	{
		//�����ƶ�
		((MenuItem*)paramter) = appDOWN(paramter);
		((MenuItem*)paramter)->linked_pointer->visit->gui(((MenuItem*)paramter)->linked_pointer->visit);
	}
	//��һ���˵������ڣ����ǽ���˵��Ķ���
	else
	{
		((MenuItem*)paramter)->linked_pointer->visit->action(((MenuItem*)paramter)->linked_pointer->visit);
	}
	return ((MenuItem*)paramter);
}
MenuItem* appQUIT(void* paramter)
{
	//��һ���˵�����
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		//�����ƶ�
		((MenuItem*)paramter) = appUP(paramter);
	}
	//��һ���˵������ڣ�����Ӧ�������˻������棩
	else
	{
		//����Ӧ����д�˻�������״̬
		
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

//����������϶˳�ʼ����mainTank.basicTank��
//�ϸ����������̳�ʼ��
//ע�ᵽ�ؼ���->���Զ�����->��ʼ��ѡ��������
void mainBasicInit()
{
	//ע���϶˿ؼ�����ӵ��ؼ���
	mainTank.basicTank = widgetInitialTank(array, 3, &Item2, &Item3, &Item4);
	mainTank.basicLen = 3;

	//���ԺͶ�����
	setDLListControlAttribute(&Item2, 1, 0, false, true, false);
	setDLListControlEvent(&Item2, act, gui);

	setDLListControlAttribute(&Item3, 2, 0, false, true, true);
	setDLListControlEvent(&Item3, act, gui);

	setDLListControlAttribute(&Item4, 3, 0, false, true, false);
	setDLListControlEvent(&Item4, act, gui);

	//�ؼ�ѡ������ʼ��
	linkedListInit(&linked, &Item);
	//��ѡ���������ָ������
	linkedAddList(&linked, array[0]);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedGui(linked);
}

//�˵���ʼ��
void menuInitialization()
{
	//�Բ˵��ڵ���г�ʼ��
	setDLListControlAttribute(&menuNode1, 1, 0, false, false, false);
	setDLListControlEvent(&menuNode1, act, gui);

	setDLListControlAttribute(&menuNode2, 2, 0, false, false, false);
	setDLListControlEvent(&menuNode2, act, gui);

	setDLListControlAttribute(&menuNode3, 3, 0, false, false, false);
	setDLListControlEvent(&menuNode3, act, gui);

	setDLListControlAttribute(&menuNode4, 4, 0, false, false, false);
	setDLListControlEvent(&menuNode4, act, gui);

	//�˵����ʼ��
	linkedListInit(&menuLinked1, &menuNode10);
	linkedListInit(&menuLinked2, &menuNode20);
	linkedListInit(&menuLinked3, &menuNode30);

	//��ӳ�ʼ��״̬
	SET_STATUS(BIT_flag, BIT0);
}

//����userPass��ʼ���˵�����
void menuUserInitialization(int8_t userPass)
{
	if (!GET_STATUS(BIT_flag, BIT0))
	{
		menuInitialization();
	}
	//ÿһ�ε����붼��Ҫ����
	linkedClearList(&menuLinked1);
	linkedClearList(&menuLinked2);
	linkedClearList(&menuLinked3);
	if (userPass == 'h')
	{
		//���˵��ڵ���ӵ�����
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//�����µĲ˵��ؼ��ڵ�����
		linkedNumAddList(&menuLinked1, 2, &menuNode1, &menuNode2);
	
	}
	else if (userPass == 'i')
	{
		//���˵��ڵ���ӵ�����
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//�����µĲ˵��ؼ��ڵ�����
		linkedNumAddList(&menuLinked1, 1, &menuNode1);
		
	}
	
	//��ʼ���˵���ڵ�
	menuLinkedListIintial(&menuGrade1, &menuLinked1, 1, actMenuItem, menuArray1);
	menuLinkedListIintial(&menuGrade2, &menuLinked2, 2, actMenuItem, menuArray2);
	menuLinkedListIintial(&menuGrade3, &menuLinked3, 2, actMenuItem, menuArray3);
	

	//���¼��˵�������
	menuLinked(&menuGrade1, &menuGrade2, &menuGrade3);

	CLE_STATUS(BIT_flag, BIT0);
}

//�˵���Ķ���
void* actMenuItem(void* paramter)
{
	return application(paramter);
	//��������ݵ�����
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}

//�˵��ڵ�Ķ���
void actMenuNode(void* paramter)
{
	//application(paramter);
	//��������ݵ�����
	//printf("\r\n%c%d\r\n", 9>=10?'\0':'0',9);
}