#include"include_user.h"
#include"keyboard.h"
//关闭对scanf的编译报错
#pragma warning(disable : 4996)

int8_t key_value = 0;

void keyboardValue()
{
	
#if (win64 == 1)
	//printf("\r\nplease enter password:");
	scanf(" %c", &key_value);
#else

#endif // (win64 == 1)
	//return value;
}