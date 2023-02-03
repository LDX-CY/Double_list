#pragma once
#ifndef TYPE_USER_H
#define TYPE_USER_H

//可移植库
#include "include_user.h"


#define BIT0 1			//BITO:菜单初始化状态
#define BIT1 BIT0<<1	//BIT1:退回主界面状态
#define BIT2 BIT0<<2	//BIT2:密码输入模式
#define BIT3 BIT0<<3	//BIT3:函数动作模式
#define BIT4 BIT0<<4	//BIT4:
#define BIT5 BIT0<<5
#define BIT6 BIT0<<6
#define BIT7 BIT0<<7

//状态的设置、清除和获取
#define SET_STATUS(CHAR,BIT) CHAR |= BIT
#define CLE_STATUS(CHAR,BIT) CHAR &= ~(BIT)
#define GET_STATUS(CHAR,BIT) (CHAR&&BIT)

typedef unsigned char status;

typedef enum 
{
	false,
	true
}bool;

#endif // !TYPE_USER_H

