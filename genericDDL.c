/*MihretZemedkun
Candy Land (with a twist). The board will be composed of an unknown number of
"squares" (each "square" data will be read in from a file, which is included).
The board is a collection of these "squares" and is therefore dynamic,
so it uses a Generic Double Linked List to hold each "square".
The entire Generic Double Linked List is the board. This is a single player game,
and you win when you land on the WIN
space.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genericDDL.h"

int main(){
  int firstid = 100;
  char *firstname = "FirstKid";
  student_t * kid = createStudent(firstid,firstname);
  node_t * first = createNode(kid);
  node_t * last = first;

  int secid = 101;
  char* secname= "SecondKid";
  student_t *kid2 = createStudent(secid,secname);
  node_t * newNode = createNode(kid2);
  insertEnd(last,newNode);
  last = newNode;

  int thirdid = 102;
  char*thirdname = "ThirdKid";
  student_t * kid3 = createStudent(thirdid,thirdname);
  newNode = createNode(kid3);
  insertEnd(last,newNode);

  last = newNode;
  forwardTraversal(first);
  backwardTraversal(last);
  int desirednum = 2;
  particularTraversal(first,desirednum);
  node_t * second = deleteFront(first);
  first = second;
  node_t * secondtolast = deleteEnd(last);
  last = secondtolast;
  forwardTraversal(first);
  backwardTraversal(last);
}

student_t  * createStudent(int id,char * name){
  student_t * newStu = (student_t *)malloc(sizeof(student_t));
  newStu->id = id;
  strcpy(newStu->name,name);
  return newStu;
}

node_t * createNode(void * data){
  node_t * newNode = (node_t *)malloc(sizeof(node_t));
  newNode->item = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

void insertEnd(node_t * last, node_t * newLink){
  last->next = newLink;
  newLink->prev = last;
}

void forwardTraversal(node_t * start){
  node_t * temp = start;
  int currentId;
  char currentName[20];
  student_t * currentStu;
  while (temp != NULL){
    currentStu = temp->item;
    currentId = currentStu->id;
    strcpy(currentName,currentStu->name);
    printf("ID: %d, Name: %s\n", currentId, currentName);
    temp = temp->next;
  }
}

void backwardTraversal(node_t * start){
  node_t * temp = start;
  int currentId;
  char currentName[20];
  student_t * currentStu;
  while (temp != NULL){
    currentStu = temp->item;
    currentId = currentStu->id;
    strcpy(currentName,currentStu->name);
    printf("ID:%d, Name: %s\n", currentId, currentName);
    temp = temp->prev;
  }
}

node_t * deleteFront(node_t * first){
  node_t * temp = first;
  student_t * currentStu;
  currentStu = first->item;
  node_t * second = first->next;
  second->prev = NULL;
  free(currentStu);
  free(temp);
  return second;
}

node_t * deleteEnd(node_t * last){
  node_t * temp = last;
  student_t * currentStu;
  currentStu = last->item;
  node_t * secondtolast = last->prev;
  secondtolast->next = NULL;
  free(currentStu);
  free(temp);
  return secondtolast;
}

void particularTraversal(node_t * start, int numNode){
  node_t * temp = start;
  int currentId;
  char currentName[20];
  student_t * currentStu;
  int i;
  for (i=0;i<numNode;i++){
    temp = temp->next;
  }
  currentStu = temp->item;
  currentId = currentStu->id;
  strcpy(currentName,currentStu->name);
  printf("Specific node:\nID: %d, Name: %s\n", currentId, currentName);
}
