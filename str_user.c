#include "str_user.h"


void UART_Send(char data)
{
    printf("%c", data);
}

/******************************************************
        ��������ת�ַ�������
        char *itoa(int value, char *string, int radix)
        radix=10 ��ʾ��10����	��ʮ���ƣ�ת�����Ϊ0;

        ����d=-379;
        ִ��	itoa(d, buf, 10); ��

        buf="-379"
**********************************************************/
char* itoa(int value, char* string, int radix)
{
    int     i, d;
    int     flag = 0;
    char* ptr = string;
    char ptr_t[8];

    /* This implementation only works for decimal numbers. */
    if (radix != 10 && radix != 16)
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
    if (radix == 10)
    {
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
    }
    else if (radix == 16)
    {
        i = 0;
        for (; value > 0;)
        {
            d = value & 0xf;
            value = value >> 4;
            if (d < 10)
            {
                ptr_t[i] = d + '0';
            }
            else if(d >= 10)
            {
                d -= 10;
                ptr_t[i] = d + 'a';
            }
            i++;
        }
        for (; i > 0;)
        {
            *ptr++ = ptr_t[--i];    
        }
    }
    

    

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */



//�ɱ�κ���
void print(void (*UART_Send)(char data), unsigned char* Data, ...)
{
    const char* s;
    char buf[16];
    int d;
    unsigned char x=0;

    va_list ap;

    //��ʼȡֵ
    __crt_va_start(ap, Data);

    while (*Data != 0) {				                          //�ж��Ƿ񵽴��ַ���������
        if (*Data == 0x5c) {									  //'\'
            switch (*++Data) {
            case 'r':							          //�س���
                UART_Send(0x0d);

                Data++;
                break;
            case 'n':							          //���з�
                UART_Send(0x0a);
                Data++;
                break;

            default:
                Data++;
                break;
            }

        }
        else if (*Data == '%' || *Data == '#') {									  //
            switch (*++Data) {
            case 's':										  //�ַ���
                s = __crt_va_arg(ap, const char*);
                for (; *s; s++) {
                    UART_Send(*s);
                }
                Data++;
                break;
            case 'd':										  //ʮ����
                d = __crt_va_arg(ap, int);
                itoa(d, buf, 10);

                for (s = buf; *s; s++) {
                    UART_Send(*s);
                }
                Data++;
                break;
            case '#':										  //ʮ����
                x = 1;
                break;
            case 'x':										  //ʮ������
                d = __crt_va_arg(ap, unsigned int);
                if (x)
                {
                    x = 0;
                    UART_Send('0');
                    UART_Send('x');
                }   
                itoa(d, buf, 16);
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
