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

//状态寄存器
extern status BIT_flag;

//在实际使用中，直接利用mainTank即可实现应用，不再关心创建的是什么数组
extern App_tank mainTank;

extern Node  menuNode1, menuNode2, menuNode3, menuNode4;
extern NodeMini menuNode10, menuNode20, menuNode30;//头节点
extern List_node menuLinked1;//链表（一个MenuItem定义一个链表）
extern List_node menuLinked2;
extern List_node menuLinked3;
extern MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//按键键值
extern int8_t key_value;

int main()
{
	MenuItem* menuVist;

	
	//初始化主界面上端显示
	mainBasicInit();
	//输出上端GUI
	printBasicControlGui(mainTank);

	print(UART_Send, "\r\n------------------------------\r\n");

	//初始化菜单
	menuInitialization();
	//根据用户设定载入菜单
	menuUserInitialization('h');

	menuVist = &menuGrade1;
	//print(UART_Send, "%d", menuVist->next_MenuArray[0]);
	
	//menuGUI(*menuVist);
	while (true)
	{
		key_value = 0;
		menuGUI(*menuVist);
		print(UART_Send, "\r\n--------------------------\r\n");
		passwordGUI();
		keyboardValue();
		menuVist = menuVist->menuPointAction(menuVist);
	}


	
	return 0;
}