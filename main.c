/*
��Node�ṹ��Ϊ�ؼ����������ؼ��������Զ���ӵ�������ʾ
������Ҫ�ڿؼ��أ�Node* array[]����ע��
���϶˺��ж���Ҫ�ֱ��ڸ��ԵĿؼ�����ע��
*/

#include "Double_list.h"
#include "include_user.h"
#include "widget_DLList.h"
#include "str_user.h"

extern App_tank mainTank;



int main()
{
	
#if (win64 == 1)
	Node  Item2, Item3, Item4;
	NodeMini Item;
	List_node linked;
	Node* array[3];

	//ע���϶˿ؼ�����ӵ�Ӧ�ó�
	mainTank.basicTank = widgetInitialTank(array, 3, &Item2, &Item3, &Item4);
	mainTank.basicLen = 3;
	
	//���ԺͶ�����
	setDLListControlAttribute(&Item2, 1, 0, false,true,false);
	setDLListControlEvent(&Item2, NULL, gui);

	setDLListControlAttribute(&Item3, 2, 0, false, true, true);
	setDLListControlEvent(&Item3, NULL, gui);

	setDLListControlAttribute(&Item4, 3, 0, false, true, false);
	setDLListControlEvent(&Item4, NULL, gui);


	printBasicControlGui(mainTank);
	


	//�ؼ�ѡ������ʼ��
	linkedListInit(&linked, &Item);

	linkedAddList(&linked, array[0]);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedGui(linked);
	
	linkedDeleteList(&linked, 2);
	linkedGui(linked);
	
	linkedAddList(&linked, &Item3);
	linkedGui(linked);

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