/*
将Node结构视为控件，但创建控件并不能自动添加到窗口显示
，必须要在控件池（Node* array[]）中注册
，上端和中端需要分别在各自的控件池中注册
*/

#include "Double_list.h"
#include "include_user.h"
#include "widget_DLList.h"
#include "str_user.h"
#include "keyboard.h"
#include "app.h"

//在实际使用中，直接利用mainTank即可实现应用，不再关心创建的是什么数组
extern App_tank mainTank;

extern Node  menuNode1, menuNode2, menuNode3, menuNode4;
extern NodeMini menuNode10, menuNode20, menuNode30;//头节点
extern List_node menuLinked1;//链表（一个MenuItem定义一个链表）
extern List_node menuLinked2;
extern List_node menuLinked3;
extern MenuItem menuGrade1, menuGrade2, menuGrade3;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//按键键值
extern int8_t key_value;

void test()
{
	int16_t test_id;

	linkedGui(*(menuGrade1.linked_pointer));
	print(UART_Send, "\r\n------------------------------\r\n");
	linkedGui(*(menuGrade1.next_MenuArray[0]->linked_pointer));
	linkedGui(*(menuGrade1.next_MenuArray[1]->linked_pointer));
	print(UART_Send, "\r\n-----------选择----------------\r\n");
	menuGrade1.linked_pointer->visit = menuGrade1.linked_pointer->visit->next;
	test_id = menuGrade1.linked_pointer->visit->id;
	menuGrade1.linked_pointer->visit->gui(menuGrade1.linked_pointer->visit);
	print(UART_Send, "\r\n---------------选择------------\r\n");
	linkedGui(*(menuGrade1.next_MenuArray[test_id - 1]->linked_pointer));
	print(UART_Send, "\r\n---------------上一级------------\r\n");
	((MenuItem*)menuGrade1.next_MenuArray[test_id - 1]->linked_pointer->visit->next->subordinate)->prev_MenuPoint->linked_pointer->visit->gui(((MenuItem*)menuGrade1.next_MenuArray[test_id - 1]->linked_pointer->visit->next->subordinate)->prev_MenuPoint->linked_pointer->visit);

}

int main()
{
	MenuItem* menuVist;
#if (win64 == 1)
	
	//初始化主界面上端显示
	mainBasicInit();
	//输出上端GUI
	printBasicControlGui(mainTank);

	print(UART_Send, "\r\n------------------------------\r\n");

	//初始化菜单
	menuInitialization();
	//根据用户设定载入菜单
	menuUserInitialization('i');

	menuVist = &menuGrade1;
	while (true)
	{
		key_value = 0;
		menuGUI(*menuVist);
		print(UART_Send, "\r\n--------------------------\r\n");
		passwordGUI();
		keyboardValue();
		menuVist = menuVist->menuPointAction(menuVist);
	}
	

	/*test();
	print(UART_Send, "\r\n------------------------------\r\n");
	menuUserInitialization('i');
	test();*/
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