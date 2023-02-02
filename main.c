/*
��Node�ṹ��Ϊ�ؼ����������ؼ��������Զ���ӵ�������ʾ
������Ҫ�ڿؼ��أ�Node* array[]����ע��
���϶˺��ж���Ҫ�ֱ��ڸ��ԵĿؼ�����ע��
*/

#include "Double_list.h"
#include "include_user.h"
#include "widget_DLList.h"
#include "str_user.h"

//��ʵ��ʹ���У�ֱ������mainTank����ʵ��Ӧ�ã����ٹ��Ĵ�������ʲô����
extern App_tank mainTank;



int main()
{
	
#if (win64 == 1)
	Node  Item2, Item3, Item4, menuNode1, menuNode2, menuNode3, menuNode4;
	NodeMini Item, menuNode10, menuNode20, menuNode30;//ͷ�ڵ�
	List_node linked, menuLinked1;//����һ��MenuItem����һ������
	List_node menuLinked2;
	List_node menuLinked3;
	Node* array[3];
	MenuItem menuGrade1, menuGrade2, menuGrade3;
	MenuItem* menuArray1[3],* menuArray2[3], * menuArray3[3];

	int16_t test_id;

	//ע���϶˿ؼ�����ӵ��ؼ���
	mainTank.basicTank = widgetInitialTank(array, 3, &Item2, &Item3, &Item4);
	mainTank.basicLen = 3;
	
	//���ԺͶ�����
	setDLListControlAttribute(&Item2, 1, 0, false,true,false);
	setDLListControlEvent(&Item2, act, gui);

	setDLListControlAttribute(&Item3, 2, 0, false, true, true);
	setDLListControlEvent(&Item3, act, gui);

	setDLListControlAttribute(&Item4, 3, 0, false, true, false);
	setDLListControlEvent(&Item4, act, gui);

	//�Բ˵��ڵ���г�ʼ��
	setDLListControlAttribute(&menuNode1, 1, 0, false, false, false);
	setDLListControlEvent(&menuNode1, act, gui);

	setDLListControlAttribute(&menuNode2, 2, 0, false, false, false);
	setDLListControlEvent(&menuNode2, act, gui);

	setDLListControlAttribute(&menuNode3, 3, 0, false, false, false);
	setDLListControlEvent(&menuNode3, act, gui);

	setDLListControlAttribute(&menuNode4, 4, 0, false, false, false);
	setDLListControlEvent(&menuNode4, act, gui);


	//����϶�GUI
	printBasicControlGui(mainTank);
	


	//�ؼ�ѡ������ʼ��
	linkedListInit(&linked, &Item);
	linkedListInit(&menuLinked1, &menuNode10);
	linkedListInit(&menuLinked2, &menuNode20);
	linkedListInit(&menuLinked3, &menuNode30);

	//��������ӵ��˵��ڵ�
	linkedAddList(&menuLinked1, &menuNode1);
	linkedAddList(&menuLinked1, &menuNode2);

	linkedAddList(&menuLinked2, &menuNode3);
	linkedAddList(&menuLinked3, &menuNode4);


	//��ѡ���������ָ������
	linkedAddList(&linked, array[0]);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedGui(linked);

	print(UART_Send, "\r\n------------------------------\r\n");

	//��ʼ���˵��ڵ�
	menuLinkedListIintial(&menuGrade1, &menuLinked1, 1, NULL, menuArray1);

	menuLinkedListIintial(&menuGrade2, &menuLinked2, 2, NULL, menuArray2);
	menuLinkedListIintial(&menuGrade3, &menuLinked3, 2, NULL, menuArray3);

	//���¼��˵�������
	menuLinked(&menuGrade1, &menuGrade2, &menuGrade3);

	linkedGui(*(menuGrade1.linked_pointer));
	print(UART_Send, "\r\n------------------------------\r\n");
	linkedGui(*(menuGrade1.next_MenuArray[0]->linked_pointer));
	linkedGui(*(menuGrade1.next_MenuArray[1]->linked_pointer));
	print(UART_Send, "\r\n-----------ѡ��----------------\r\n");
	menuGrade1.linked_pointer->visit = menuGrade1.linked_pointer->visit->next->next;
	test_id = menuGrade1.linked_pointer->visit->id;
	menuGrade1.linked_pointer->visit->gui(menuGrade1.linked_pointer->visit);
	print(UART_Send, "\r\n---------------ѡ��------------\r\n");
	linkedGui(*(menuGrade1.next_MenuArray[test_id-1]->linked_pointer));
	print(UART_Send, "\r\n---------------��һ��------------\r\n");
	((MenuItem*)menuGrade1.next_MenuArray[test_id-1]->linked_pointer->visit->next->subordinate)->prev_MenuPoint->linked_pointer->visit->gui(((MenuItem*)menuGrade1.next_MenuArray[test_id-1]->linked_pointer->visit->next->subordinate)->prev_MenuPoint->linked_pointer->visit);


	/*linkedDeleteList(&linked, 2);
	linkedGui(linked);
	
	linkedAddList(&linked, &Item3);
	linkedGui(linked);*/

	/*mainTank.basicTank[0]->action(mainTank.basicTank[0]);
	mainTank.basicTank[1]->action(mainTank.basicTank[1]);*/

#else
	Node Item, Item2,Item3, Item4;
	List_node linked;

	Item2.id = 1;
	Item3.id = 2;
	Item4.id = 3;

	linkedListInit(&linked, &Item);
	linkedAddList(&linked, &Item2);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedDeleteList(&linked, 2);
#endif // (win64 == 1)

	
	return 0;
}