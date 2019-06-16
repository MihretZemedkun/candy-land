/*MihretZemedkun
*/

typedef struct node{
   void * item;     // data item is a void pointer, so we can insert the address
   struct node * next;    // of any item here
   struct node * prev;
}node_t;

typedef struct student {
   int id;
   char name[20];
}student_t;

student_t * createStudent(int id,char * name);
node_t * createNode(void * data);
void insertEnd(node_t * last, node_t * newLink);
void forwardTraversal(node_t * start);
void backwardTraversal(node_t * start);
node_t * deleteFront(node_t * first);
node_t * deleteEnd(node_t * last);
void particularTraversal(node_t * start, int numNode);
