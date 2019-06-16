/*MihretZemedkun
PP4 PartB
*/
typedef struct space {
  char *color;
  char *special;
  int x;
} space_t;

typedef struct node{
   void * item;
   struct node * next;
   struct node * prev;
}node_t;

node_t * createNode(void * data);
void insertEnd(node_t * last, node_t * newLink);
space_t *createBoardSpace(FILE *myFile);
void toString(space_t *b);
int goForward(node_t * d, space_t * e);
void forwardTraversal(node_t * start);
int randomNumber(int upperBound);
node_t * findColour(char*colour, node_t*position);
