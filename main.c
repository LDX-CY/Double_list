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
int main()
{
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