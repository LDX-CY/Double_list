#include "widget_DLList.h"

//���ÿؼ�������
//id:�ؼ�id
//unit_flag:��λ����
//gui_status:ѡ��״̬
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_status)
{
	if (!Item)
		return WIDGET_ERROR;
	Item->id = id;
	Item->unit_flag = unit_flag;
	Item->gui_status = gui_status;
	return OK;
}

//�󶨿ؼ��¼�
int8_t setDLListControlEvent(Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter))
{
	if (!Item)
		return WIDGET_ERROR;
	Item->action = action;
	Item->gui = gui;
	return OK;
}