/*
将Node结构视为控件，但创建控件并不能自动添加到窗口显示
，必须要在控件池（Node* array[]）中注册
，上端和中端需要分别在各自的控件池中注册
*/

#include "Double_list.h"
#include "include_user.h"
#include "widget_DLList.h"

extern App_tank mainTank;

#if (win64 == 1)

void gui1(void* paramter)
{
	if(*((bool*)paramter) == true)
		printf("[1]");
	else
	{
		printf(">1<");
	}
}
void gui2(void* paramter)
{
	printf("[2]");
}
void gui3(void* paramter)
{
	printf("[3]");
}
#endif // (win64 == 1)


int main()
{
	
#if (win64 == 1)
	Node Item, Item2, Item3, Item4;
	List_node linked;
	Node* array[3];//

	//注册上端控件并添加到应用池
	mainTank.basicTank = widgetInitialTank(array, 3, &Item2, &Item3, &Item4);
	mainTank.basicLen = 3;
	
	//属性和动作设置
	setDLListControlAttribute(&Item2, 1, 0, false);
	setDLListControlEvent(&Item2, NULL, gui1);

	setDLListControlAttribute(&Item3, 2, 0, false);
	setDLListControlEvent(&Item3, NULL, gui2);

	setDLListControlAttribute(&Item4, 3, 0, false);
	setDLListControlEvent(&Item4, NULL, gui3);


	printBasicControlGui(mainTank);
	


	//控件选择器初始化
	linkedListInit(&linked, &Item);

	linkedAddList(&linked, array[0]);
	linkedAddList(&linked, &Item3);
	linkedAddList(&linked, &Item4);
	linkedGui(linked);
	printf("\r\n---------------------\r\n");
	linkedDeleteList(&linked, 2);
	linkedGui(linked);
	printf("\r\n---------------------\r\n");
	linkedAddList(&linked, &Item3);
	linkedGui(linked);
	printf("\r\n---------------------\r\n");
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