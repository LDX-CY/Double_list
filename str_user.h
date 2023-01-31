#include "include_user.h"
#if STR_USER_CONFIG


void UART_Send(char data);
char* itoa(int value, char* string, int radix);
void print(void (*UART_Send)(char data), unsigned char* Data, ...);
#endif // STR_USER_CONFIG