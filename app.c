/*
ע�⣺mainGUI�����˻������滹û������
	  menuUserInitialization��ֲʱ��Ҫ�󲿷��޸�
*/
#include "app.h"
#include "str_user.h"
//BITO:�˵���ʼ��״̬
//BIT1:�˻�������״̬
//BIT2:��������ģʽ
//BIT3:��������ģʽ
//BIT4:�˵�ģʽ
//BIT5:
//BIT6:
//BIT7:
//����������������Ǹ��ݸ�״̬�ж�
status BIT_flag = 0;
extern int8_t key_value;

//�˵��ڵ�
Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
//ͷ�ڵ�
NodeMini Item, menuNode10, menuNode20, menuNode30;//ͷ�ڵ�
//��ѡ����������϶���ʾ����
List_node linked;
//�������϶˽ڵ�����
Node* array[MIN_SHOWTOP_LENGTH];
//�˵�����
List_node menuLinked1;//����һ��MenuItem����һ������
List_node menuLinked2;
List_node menuLinked3;

//�˵���
MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];
//��ʵ��ʹ���У�ֱ������mainTank����ʵ��Ӧ�ã����ٹ��Ĵ�������ʲô����
extern App_tank mainTank;

//��������±�
int8_t array_visit = 0;

//�˵������ָ��
extern MenuItem* menuVist;

void* actMenuItem(void* paramter);
/// <summary>
/// ������gui�ӿڣ�Ĭ����ʾ���棩
/// </summary>
void mainGUI()
{
	if (GET_STATUS(BIT_flag, BIT1))
	{
		//����������������GUI����,������ֻ���ض���״̬ˢ��ȫ��������

		//���ȫ���ˢ��
		//CLE_STATUS(BIT_flag, BIT1);
	}
	
}
/// <summary>
/// ���������gui�ӿ�
/// </summary>
void passwordGUI()
{
	//������ģʽ
	if (GET_STATUS(BIT_flag,BIT1)|| GET_STATUS(BIT_flag, BIT3))
	{
		print(UART_Send, "\r\n�����밴��ֵ��");
	}
	//��������ģʽ
	else if (GET_STATUS(BIT_flag,BIT2))
	{
		print(UART_Send, "\r\n���������룺");
	}
	
	keyboardValue();
	switch(key_value)
	{
	case 'm':
		//����ģʽ 
		SET_STATUS(BIT_flag, BIT2); CLE_STATUS(BIT_flag, BIT1); break;
	default: break;
	}
}
/// <summary>
/// �˵�gui��ʾ��ӫĻ
/// </summary>
/// <param name="MenuGrade">
/// �˵����ʽڵ㣨��Ҫ�Լ��������ָ�룩
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
		//�����������״̬
		//CLE_STATUS(BIT_flag, BIT2);
		//�����˵�
		//menuInitCreat();
		//�����û��趨����˵��ʹ����˵�
		menuUserInitialization(key_value);
	}
	if (GET_STATUS(BIT_flag, BIT4))
	{
		if ((*MenuGrade).menu_type == false)
		{
			visit = (*MenuGrade).linked_pointer->head;
			for (i = 0; i < (*MenuGrade).linked_pointer->num; i++)
			{
				//Խ��ͷ�ڵ�
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
/// ��һ������
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ��һ���Ĳ˵���ַ
/// </returns>
MenuItem* appUP(void* paramter)
{
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		//ȷ����ǰ�˵����Ͳ�����������
		if(((MenuItem*)paramter)->menu_type != true)
			//���Ϸ��ʽ���������ָ��ָ��ͷ�ڵ�
			((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head;
		((MenuItem*)paramter) = ((MenuItem*)paramter)->prev_MenuPoint;
	}
	return paramter;
}
/// <summary>
/// ��һ������
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ��һ���˵���ַ
/// </returns>
MenuItem* appDOWN(void* paramter)
{
	
	if (((MenuItem*)paramter)->linked_pointer->num > 0)
	{
		((MenuItem*)paramter) = ((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id - 1];
		//����ģʽ
		if (((MenuItem*)paramter)->menu_type != true)
		{
			if (((MenuItem*)paramter)->linked_pointer->visit->id == 0)
				((MenuItem*)paramter)->linked_pointer->visit = ((MenuItem*)paramter)->linked_pointer->head->next;
		}
	}
	
	return paramter;
}
/// <summary>
/// ��ѯ��һ���˵��ڵ�
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ���º�Ĳ˵�����²˵����еĲ˵�����ķ��ʽڵ㣩
/// </returns>
MenuItem* appLEFT(void* paramter)
{
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//���gui��ѡ��״̬
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = false;
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
		//���ѡ��״̬
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = true;
	}
	else
	{
		//���ǰһ��״̬
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
		if (--array_visit < 0)
			array_visit = MIN_SHOWTOP_LENGTH - 1;
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
	}
		
	
	return paramter;
}
/// <summary>
/// ��ѯ��һ���˵��ڵ�
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ���º�Ĳ˵�����²˵����еĲ˵�����ķ��ʽڵ㣩
/// </returns>
MenuItem* appRIGHT(void* paramter)
{
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//���gui��ѡ��״̬
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = false;
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
		//gui��ѡ��״̬Ϊѡ��
		((MenuItem*)paramter)->linked_pointer->visit->gui_status = true;
	}
	else
	{
		//���ǰһ��״̬
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
		if (++array_visit >= MIN_SHOWTOP_LENGTH)
			array_visit = 0;
		((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
	}
	return paramter;
}
/// <summary>
/// �����¼��˵���ǰ�˵��ڵ�Ķ���
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ��ǰ�˵������һ���˵�
/// </returns>
MenuItem* appENTER(void* paramter)
{
	//��������˵�
	if (((MenuItem*)paramter)->menu_type != true)
	{
		//��һ���˵�����
		if (((MenuItem*)paramter)->next_MenuArray[((MenuItem*)paramter)->linked_pointer->visit->id - 1] != NULL)
		{
			//�����ƶ�
			((MenuItem*)paramter) = appDOWN(paramter);
			//���Դ���
			/*if (((MenuItem*)paramter)->menu_type != true)
				((MenuItem*)paramter)->linked_pointer->visit->gui(((MenuItem*)paramter)->linked_pointer->visit);
			else
				((Node*)((MenuItem*)paramter)->controlTank[0])->gui(((MenuItem*)paramter)->controlTank[0]);*/
		}
		//�¼��˵�������
		else
		{
			((MenuItem*)paramter)->linked_pointer->visit->action(((MenuItem*)paramter)->linked_pointer->visit);
			return ((MenuItem*)paramter);
		}
		return ((MenuItem*)paramter);
	}
	//����˵��������¼��˵�ֱ�ӽ�������˵��Ķ���
	((Node*)((MenuItem*)paramter)->controlTank[array_visit])->action(((MenuItem*)paramter)->controlTank[array_visit]);
	return ((MenuItem*)paramter);
}
/// <summary>
/// �����ϼ��˵��򷵻�������
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// �ϼ��˵�������÷����������־
/// </returns>
MenuItem* appQUIT(void* paramter)
{
	//��һ���˵�����
	if (((MenuItem*)paramter)->prev_MenuPoint != NULL)
	{
		if (((MenuItem*)paramter)->menu_type == true)
		{
			((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = false;
			array_visit = 0;
			((Node*)((MenuItem*)paramter)->controlTank[array_visit])->gui_status = true;
		}
		//�����ƶ�
		((MenuItem*)paramter) = appUP(paramter);
	}
	//��һ���˵������ڣ�����Ӧ�������˻������棩
	else
	{
		//����Ӧ����д�˻�������״̬
		
		SET_STATUS(BIT_flag, BIT1);
		CLE_STATUS(BIT_flag, BIT3);
		CLE_STATUS(BIT_flag, BIT4);
		//mainGUI();
		//((MenuItem*)paramter)->linked_pointer->visit->action(paramter);
	}
	return ((MenuItem*)paramter);
}
/// <summary>
/// ���ݰ���ִ����صĶ���
/// </summary>
/// <param name="paramter">
/// ��ǰ�˵���
/// </param>
/// <returns>
/// ��ǰ�˵������һ���˵�����һ���˵�
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
		paramter = NULL;
		break;
	}
	return (MenuItem*)paramter;
}


/// <summary>
/// ����������϶˳�ʼ����mainTank.basicTank��,
/// �ϸ����������̳�ʼ��,
/// ע�ᵽ�ؼ���->���Զ�����->��ʼ��ѡ��������
/// </summary>
void mainBasicInit()
{
	//ע���϶˿ؼ�����ӵ��ؼ���
	mainTank.basicTank = widgetInitialTank(array, MIN_SHOWTOP_LENGTH, &Item2, &Item3, &Item4);
	mainTank.basicLen = MIN_SHOWTOP_LENGTH;

	//���ԺͶ�����
	setDLListControlAttribute(&Item2, 1, 0, true, true);
	setDLListControlEvent(&Item2, act, gui);

	setDLListControlAttribute(&Item3, 2, 0, true, false);
	setDLListControlEvent(&Item3, act, gui);

	setDLListControlAttribute(&Item4, 3, 0, true, false);
	setDLListControlEvent(&Item4, act, gui);

	//�ؼ�ѡ������ʼ��
	linkedListInit(&linked, &Item);
	//��ѡ���������ָ������
	linkedAddList(&linked, &Item2);


	linkedGui(linked);
}

//��������˵�
void menuInitCreat()
{
	//�Բ˵��ڵ���г�ʼ��
	setDLListControlAttribute(&menuNode1, 1, 0, false, false);
	setDLListControlEvent(&menuNode1, act, gui);

	setDLListControlAttribute(&menuNode2, 2, 0,  false, false);
	setDLListControlEvent(&menuNode2, act, gui);

	setDLListControlAttribute(&menuNode3, 1, 0,  false, false);
	setDLListControlEvent(&menuNode3, act, gui);

	setDLListControlAttribute(&menuNode4, 1, 0,  false, false);
	setDLListControlEvent(&menuNode4, act, gui);

	//�˵��б��ʼ��
	linkedListInit(&menuLinked1, &menuNode10);
	linkedListInit(&menuLinked2, &menuNode20);
	linkedListInit(&menuLinked3, &menuNode30);

	//��ӳ�ʼ��״̬
	SET_STATUS(BIT_flag, BIT0);
}

//����userPass��ʼ���˵�����
//���д����˵��Ĺ���
void menuUserInitialization(int8_t userPass)
{
	if (!GET_STATUS(BIT_flag, BIT0))
	{
		menuInitCreat();
	}
	//ÿһ�ε����ض���Ҫ����
	linkedClearList(&menuLinked1);
	linkedClearList(&menuLinked2);
	linkedClearList(&menuLinked3);
	if (userPass == 'h')
	{
		//���˵��ڵ���ӵ�����
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//�����µĲ˵��ڵ�����
		linkedNumAddList(&menuLinked1, 2, &menuNode1, &menuNode2);
		menuLinkedListArrayInitial(&menuGrade2_1, array, 3, actMenuItem);
	
	}
	else if (userPass == 'i')
	{
		//���˵��ڵ���ӵ�����
		linkedAddList(&menuLinked2, &menuNode3);
		linkedAddList(&menuLinked3, &menuNode4);
		//�����µĲ˵��ؼ��ڵ�����
		linkedNumAddList(&menuLinked1, 1, &menuNode1);
		menuLinkedListArrayInitial(&menuGrade2_1, array, 3, actMenuItem);
	}
	if (userPass == 'i' || userPass == 'h')
	{
		//��ʼ���˵���ڵ�
		menuLinkedListInitial(&menuGrade1, &menuLinked1, 1, actMenuItem, menuArray1);
		menuLinkedListInitial(&menuGrade2, &menuLinked2, 2, actMenuItem, menuArray2);
		menuLinkedListInitial(&menuGrade3, &menuLinked3, 2, actMenuItem, menuArray3);


		//���¼��˵�������
		menuLinked(&menuGrade1, &menuGrade2, &menuGrade3);
		//ע�⣺ÿһ���˵����Ҫ��ʼ������ܱ����ӣ�û�жԲ˵�����г�ʼ���ģ�����������������ڴ�ռ䣩
		menuLinked(&menuGrade2, &menuGrade2_1);

		menuVist = &menuGrade1;

		//CLE_STATUS(BIT_flag, BIT0);
		//����˵�ģʽ
		SET_STATUS(BIT_flag, BIT4);
		//���������ģʽ
		CLE_STATUS(BIT_flag, BIT1);
		CLE_STATUS(BIT_flag, BIT2);
	}
	else
	{
		//������ģʽ
		SET_STATUS(BIT_flag, BIT1);
		//����˵�ģʽ
		CLE_STATUS(BIT_flag, BIT4);
	}
}

//�˵���Ķ���
//��Ҫ�������˵��Ͱ����Ŀ���
void* actMenuItem(void* paramter)
{
	if(GET_STATUS(BIT_flag, BIT4))
		SET_STATUS(BIT_flag, BIT3);
	//passwordGUI();
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

void menuScheduler(MenuItem MenuGrade)
{
	static uint8_t flag = 1;
	static List_node* linkedVisit;
	if (GET_STATUS(BIT_flag, BIT4))
	{
		flag = 1;
		menuVist = menuVist->menuPointAction(menuVist);
	}
	else if (GET_STATUS(BIT_flag, BIT1))
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