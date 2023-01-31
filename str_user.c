#include "str_user.h"


void UART_Send(char data)
{
    printf("%c", data);
}

/******************************************************
        整形数据转字符串函数
        char *itoa(int value, char *string, int radix)
        radix=10 标示是10进制	非十进制，转换结果为0;

        例：d=-379;
        执行	itoa(d, buf, 10); 后

        buf="-379"
**********************************************************/
char* itoa(int value, char* string, int radix)
{
    int     i, d;
    int     flag = 0;
    char* ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */



//可变参函数
void print(void (*UART_Send)(char data), unsigned char* Data, ...)
{
    const char* s;
    char buf[16];
    int d;

    va_list ap;

    //开始取值
    __crt_va_start(ap, Data);

    while (*Data != 0) {				                          //判断是否到达字符串结束符
        if (*Data == 0x5c) {									  //'\'
            switch (*++Data) {
            case 'r':							          //回车符
                UART_Send(0x0d);

                Data++;
                break;
            case 'n':							          //换行符
                UART_Send(0x0a);
                Data++;
                break;

            default:
                Data++;
                break;
            }

        }
        else if (*Data == '%') {									  //
            switch (*++Data) {
            case 's':										  //字符串
                s = __crt_va_arg(ap, const char*);
                for (; *s; s++) {
                    UART_Send(*s);
                }
                Data++;
                break;
            case 'd':										  //十进制
                d = __crt_va_arg(ap, int);
                itoa(d, buf, 10);

                for (s = buf; *s; s++) {
                    UART_Send(*s);
                }
                Data++;
                break;
            default:
                Data++;
                break;
            }
        }
        else UART_Send(*Data++);

    }
    __crt_va_end(ap);
}
