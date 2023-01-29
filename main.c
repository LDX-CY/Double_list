#include "Double_list.h"
#include "include_user.h"

int main()
{
	Node* Item;
	List_node* linked;
#if (win64 == 1)
	Item = (Node*)malloc(sizeof(Node));
	linked = (List_node*)malloc(sizeof(List_node));
#endif // (win64 == 1)

	printf("test");
	linkedListInit(Item, linked);

	return 0;
}