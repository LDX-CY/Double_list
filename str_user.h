#include "include_user.h"
#if (STR_USER_CONFIG ==1)

//���ڷ��͵��ַ��ӿ�
void UART_Send(char data);
//��������ת�ַ�������;value:����;string:ת�������radix���������ͣ�Ŀǰֻ��ʮ���ƣ�
char* itoa(int value, char* string, int radix);
void print(void (*UART_Send)(char data), unsigned char* Data, ...);
#endif // STR_USER_CONFIG