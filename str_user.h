#include "include_user.h"
#if (STR_USER_CONFIG ==1)

//串口发送单字符接口
void UART_Send(char data);
//整形数据转字符串函数;value:整形;string:转换结果；radix：进制类型（目前只有十进制）
char* itoa(int value, char* string, int radix);
void print(void (*UART_Send)(char data), unsigned char* Data, ...);
#endif // STR_USER_CONFIG