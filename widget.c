#include "widget.h"

//设置控件的属性
//id:控件id
//unit_flag:单位类型
//gui_status:选择状态
int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_status)
{
	if (!Item)
		return WIDGET_ERROR;
	Item->id = id;
	Item->unit_flag = unit_flag;
	Item->gui_status = gui_status;
	return OK;
}

//绑定控件事件
int8_t setDLListControlEvent(Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter))
{
	if (!Item)
		return WIDGET_ERROR;
	Item->action = action;
	Item->gui = gui;
	return OK;
}