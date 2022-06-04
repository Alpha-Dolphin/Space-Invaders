

/* header file for list */

/* these are the function pointer signatures needed */

typedef void (* ActionFunction)( void *data);
typedef int (* ComparisonFunction)(void *data1, void *data2);
typedef int (* CriteriaFunction)(void *data, void *helper);

typedef struct Node{
	struct Node *next;
	void *data;
} Node;

