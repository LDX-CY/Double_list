/*
��Node�ṹ��Ϊ�ؼ����������ؼ��������Զ���ӵ�������ʾ
������Ҫ�ڿؼ��أ�Node* array[]����ע��
���϶˺��ж���Ҫ�ֱ��ڸ��ԵĿؼ�����ע��
*/
#include "Double_list.h"
#include "include_user.h"
#include "widget_DLList.h"
#include "str_user.h"
#include "keyboard.h"
#include "app.h"
#include "memory.h"

//״̬�Ĵ���
extern status BIT_flag;

//��ʵ��ʹ���У�ֱ������mainTank����ʵ��Ӧ�ã����ٹ��Ĵ�������ʲô����
extern App_tank mainTank;

//�˵��ڵ�
extern Node  menuNode1, menuNode2, menuNode3, menuNode4;
//ͷ�ڵ�
extern NodeMini menuNode10, menuNode20, menuNode30;
//����һ��MenuItem����һ������
extern List_node menuLinked1;
extern List_node menuLinked2;
extern List_node menuLinked3;
//�˵���
extern MenuItem menuGrade1, menuGrade2, menuGrade3, menuGrade2_1;
extern MenuItem* menuArray1[3], * menuArray2[3], * menuArray3[3];

//������ֵ
extern int8_t key_value;
//�˵����ʽڵ�
MenuItem* menuVist;

//���������(����ȷ��i��ȡֵ��ΧҲ�ǳ�ʼ����һ�ְ취)
struct test
{
	//�����ֻ���ڽṹ���вž����������� : 
	//��ʾ��i%��2^n��������Ľṹ��ֻ����0��n-1
	//����i'=88��n=3����i=0��
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
	free_ldx(&ttt);
	mem_info(Memory, mem_size);
	printf("tes2 = %p\r\n",tes2);
	printf("sizeof(mem_t):%d\r\n",sizeof(mem_t));
	printf("_mem_t.tail:%p\r\n", _mem_t.tail);
	printf("_mem_t.size_16:%d\r\n", _mem_t.size_16);
	printf("_mem_t.size_end:%d\r\n", _mem_t.size_end);
	printf("tes.first:%c\r\n", tes->first);	
	printf("tes.midd:%d\r\n", tes->midd);
	printf("tes.end:%c\r\n", tes->end);





	//��ʼ���������϶���ʾ(��ʼ����mainTank)
	mainBasicInit();
	//����϶�GUI
	printBasicControlGui();
	print(UART_Send, "\r\n------------------------------\r\n");
	menuInitCreat();
	//�൱�ڳ�ʼ��
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