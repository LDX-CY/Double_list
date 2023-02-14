#include "include_user.h"
#if (STR_USER_CONFIG ==1)

//串口发送单字符接口
void UART_Send(char data);
//整形数据转字符串函数;value:整形;string:转换结果；radix：进制类型（目前只有十进制）
char* itoa(int value, char* string, int radix);
//这是一个万能的节点，可以选择发送设备和发送的内容，和printf非常类似
void print(void (*UART_Send)(char data), unsigned char* Data, ...);
#endif // STR_USER_CONFIG