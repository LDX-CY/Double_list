#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include "include_user.h"

int8_t setDLListControlAttribute(Node* Item, int16_t id, int8_t unit_flag, bool gui_status);
int8_t setDLListControlEvent( Node* Item, void (*action)(void* paramter), void (*gui)(void* paramter));

#endif // !WIDGET_H
