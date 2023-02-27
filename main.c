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
#include "memory.h"

//状态寄存器
extern status BIT_flag;

//在实际使用中，直接利用mainTank即可实现应用，不再关心创建的是什么数组
extern App_tank mainTank;

//菜单节点
extern Node  menuNode1, menuNode2, menuNode3, menuNode4;
//头节点
extern NodeMini menuNode10, menuNode20, menuNode30;
//链表（一个MenuItem定义一个链表）
extern List_node menuLinked1;
extern List_node menuLinked2;
extern List_node menuLinked3;
//菜单项
extern MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//按键键值
extern int8_t key_value;
//菜单访问节点
MenuItem* menuVist;

//特殊运算符(用于确定i的取值范围也是初始化的一种办法)
struct test
{
	//特殊的只有在结构体中才具有这个运算符 : 
	//表示将i%（2^n）；运输的结构就只能是0到n-1
	//例如i'=88，n=3，则i=0；
	uint16_t i : 3;
};

//stru tes;

extern _mem_ _mem_t;
char* ttt;
int main()
{
	stru* tes,*tes1,*tes2;
	init_mem();
	printf("_mem_t.tail:%p\r\n", _mem_t.tail);
	printf("_mem_t.size_16:%d\r\n", _mem_t.size_16);
	printf("_mem_t.size_end:%d\r\n", _mem_t.size_end);

	tes = (stru*)malloc_ldx(sizeof(stru));
	ttt = (char*)malloc_ldx(sizeof(char) * 20);
	tes1 = (stru*)malloc_ldx(sizeof(stru));
	

	tes2 = (stru*)malloc_ldx(sizeof(stru));
	mem_info(Memory, mem_size);
	
	ttt[0] = 1;
	ttt[10] = 0;
	ttt[11] = 1;
	ttt[12] = 2;
	ttt[13] = 3;
	ttt[14] = 4;
	ttt[15] = 5;
	ttt[16] = 6;
	ttt[17] = 7;
	ttt[18] = 8;
	ttt[19] = 9;
	
	mem_info(Memory, mem_size);
	
	

	tes->end = 'a';
	tes->first = 'x';
	tes->midd = 1000;
	mem_info(Memory, mem_size);

	tes1->end = 0x11;
	tes1->first = 0x11;
	tes1->midd = 0x1111;
	mem_info(Memory, mem_size);

	tes2->end = 0x22;
	tes2->first = 0x22;
	tes2->midd = 0x2222;
	mem_info(Memory, mem_size);
	printf("_mem_t.tail:%p\r\n", _mem_t.tail);
	printf("_mem_t.size_16:%d\r\n", _mem_t.size_16);
	printf("_mem_t.size_end:%d\r\n", _mem_t.size_end);
	printf("_mem_t.head = %x\r\n",_mem_t.head);
	mem_info(Memory,mem_size);
	printf("tes2 = %p\r\n", tes2);
	free_ldx(&tes);
	mem_info(Memory, mem_size);
	printf("tes2 = %p\r\n",tes2);
	printf("sizeof(mem_t):%d\r\n",sizeof(mem_t));
	printf("_mem_t.tail:%p\r\n", _mem_t.tail);
	printf("_mem_t.size_16:%d\r\n", _mem_t.size_16);
	printf("_mem_t.size_end:%d\r\n", _mem_t.size_end);
	printf("tes.first:%c\r\n", tes->first);	
	printf("tes.midd:%d\r\n", tes->midd);
	printf("tes.end:%c\r\n", tes->end);





	//初始化主界面上端显示(初始化了mainTank)
	mainBasicInit();
	//输出上端GUI
	printBasicControlGui();
	print(UART_Send, "\r\n------------------------------\r\n");
	menuInitCreat();
	//相当于初始化
	menuVist = &menuGrade1;
	//SET_STATUS(BIT_flag, BIT1);
	while (true)
	{
		key_value = 0; 
		menuGUI(menuVist);
		
		print(UART_Send, "\r\n--------------------------\r\n");
		passwordGUI();
		menuScheduler(*menuVist);
	}
	return 0;
}