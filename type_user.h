#pragma once
#ifndef TYPE_USER_H
#define TYPE_USER_H

//ø…“∆÷≤ø‚
#include "include_user.h"


#define BIT0 1
#define BIT1 BIT0<<1
#define BIT2 BIT0<<2
#define BIT3 BIT0<<3
#define BIT4 BIT0<<4
#define BIT5 BIT0<<5
#define BIT6 BIT0<<6
#define BIT7 BIT0<<7

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

