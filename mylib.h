struct connect
{
	int idConn = 0;
	int idNew = 0;
	int inputConn = 0;
	int inputNew = 0;
	bool active = false;
};

class nodeType
{
public:
	nodeType *input[6];
	int id;
	int value;
	nodeType()
	{
		input[0] = NULL;
		input[1] = NULL;
		input[2] = NULL;
		input[3] = NULL;
		input[4] = NULL;
		input[5] = NULL;
	}
};

struct graphType
{
	nodeType *head;
	nodeType *tail;
};