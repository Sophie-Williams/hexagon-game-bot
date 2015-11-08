struct node
{
	int id=-1;
	int value;
	bool visited = false;
	struct listNode *next = NULL;
};


struct listNode
{
	node *node = NULL;
	listNode *next = NULL;
};