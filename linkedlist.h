/* Ben Elleman */

struct Node* allocNode(FILE* outFile) ;
int any(void *head, CriteriaFunction yes, void* unused) ;
int deleteSome(void *p2head, CriteriaFunction mustGo, void* helper, ActionFunction disposal, FILE* outFile) ;
void disposal(void *ptr) ;
void freeNode(void *ptr, FILE* outFile) ;
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, FILE* outFile) ;
void iterate(void *head, ActionFunction doThis) ;
void privateInsert(struct Node *newnode, struct Node **p2p2change, ComparisonFunction goesInFrontOf, FILE* outFile) ;
int privateSort(Node *head, ComparisonFunction goesInFrontOf) ;
void sort(void *hp, ComparisonFunction goesInFrontOf) ;
