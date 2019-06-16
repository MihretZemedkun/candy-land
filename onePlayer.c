/*MihretZemedkun
Candy Land (with a twist). The board will be composed of an unknown number of
"squares" (each "square" data will be read in from a file, which is included).
The board is a collection of these "squares" and is therefore dynamic,
so it uses a Generic Double Linked List to hold each "square".
The entire Generic Double Linked List is the board. This is a single player game,
and you win when you land on the WIN
space.
ONE PLAYER.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "onePlayer.h"


int main() {
  int count = 0;  // number of movements until a win
  space_t * board;
  node_t *player,*first,*last;
  FILE *fp;
  fp = fopen("board.txt", "r");   //board included in .zip file
  board = createBoardSpace(fp);
  if (board==NULL){
    printf("Your board file is empty :(");
  }
  else {
    first = createNode(board);    //node makes up the list
    last = first;
    while(1){
      board = createBoardSpace(fp);
      if (board == NULL)
        break;
      node_t * temp = createNode(board);
      insertEnd(last,temp);
      last = temp;
    }
    fclose(fp);
  }
  player = first;
  space_t * currentTile = player->item;
  char*win = "WIN";
  while(1){
    while(1){
      space_t * c = player->item;
      char * str1 = "GOBACK";
      char * str2 = "GOFORWARD";    //the four special movementsmovements
      char * str3 = "WIN";
      char * str4 = "NONE";
      if (strcmp(c->special, str1)==0) {
        count++;
        printf("Color: %s Special: %s X: %d\n", c->color, c->special, c->x);
        int moveNum = c->x;   // the third column, the integer, is the # movements
        int i;
        for (i=0;i<moveNum;i++){
          player = player->prev;
        }
      }
      else if (strcmp(c->special, str2)==0) {
        count++;
        printf("Color: %s Special: %s X: %d\n", c->color, c->special, c->x);
        int moveNum = c->x;       //^ outlines the board structure
        int i;
        for (i=0;i<moveNum;i++){
          player = player->next;
        }
      }
      else if (strcmp(c->special, str3)==0) {
        count++;
        break;
      }
      else if (strcmp(c->special, str4)==0) {
        count++;
        break;
      }
    }
    currentTile = player->item;
    printf("Color: %s Special: %s X: %d\n", currentTile->color, currentTile->special, currentTile->x);
    if (strcmp(currentTile->special, win)==0){
      break;
    }
    srand(time(NULL));      // without this, the random number generator returns same number
    int color = randomNumber(4);    // each color is a number, 1-4
    char*colour;                    // which represents number of steps to be taken
    if (color == 1){
      colour = "RED";
    }
    else if (color == 2){
      colour = "BLUE";
    }
    else if (color == 3){
      colour = "ORANGE";
    }
    else if (color == 4){
      colour = "GREEN";
    }
    player = findColour(colour,player);
    currentTile = player->item;
  }
  printf("Congrats, you won!!\n");      // only you can win!
  printf("Number of moves until a win: %d\n", count);
}

space_t *createBoardSpace(FILE *myFile) {
  char *color;
  char *special;
  char dummy;
  int tempint;
  space_t *board;

  board = (space_t *)malloc(sizeof(space_t));
  board->color = (char *)malloc(sizeof(char) * 10);
  board->special = (char *)malloc(sizeof(char) * 10);

  fscanf(myFile,"%s%s%d%c", board->color, board->special, &tempint, &dummy);
  if (feof(myFile)){    // scan the file until empty, aka no more steps to take
    return NULL;
  }
  board->x = tempint;
  return board;
}

void toString(space_t *b){
  printf("the board space: %s %s %d\n",b->color, b->special, b->x);
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
  space_t * currentSpace;
  while (temp != NULL){
    currentSpace = temp->item;
    printf("Color: %s, Special: %s Int: %d\n", currentSpace->color, currentSpace->special, currentSpace->x);
    temp = temp->next;
  }
}

int randomNumber(int upperBound){
    int j;
    j=1+(rand() % upperBound);
    return j;
}

node_t * findColour(char*colour, node_t*position){
  if (position->next == NULL){      // let color on the board is the position
    return position;
  }
  else {
    node_t* pos1 = position->next;
    while(1){

      if(pos1->next == NULL){

        return pos1;
      }
      else{
        space_t*pos1Space = pos1->item;
        char*pos1Colour = pos1Space->color;

        if (strcmp(pos1Colour, colour)==0){
          return pos1;
        }
        else{
          pos1 = pos1->next;
        }
      }
    }
  }
}
