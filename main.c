#include "Double_list.h"
#include "include_user.h"

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
	//Node** test;//双重指针数组存储Node的地址
	Node* array[MIN_SHOWTOP_LENGTH];// = { &Item2 ,&Item3 ,&Item4 };

	Item2.id = 1;
	Item2.gui = gui1;
	Item2.gui_status = false;

	Item3.id = 2;
	Item3.gui = gui2;

	Item4.id = 3;
	Item4.gui = gui3;
	
	//注册上端控件
	linkedLogin(array, 1,&Item3);
	

	linkedListInit(&linked, &Item);
	linkedAddList(&linked, &Item2);
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