/*MihretZemedkun
Candy Land (with a twist). The board will be composed of an unknown number of
"squares" (each "square" data will be read in from a file, which is included).
The board is a collection of these "squares" and is therefore dynamic,
so it uses a Generic Double Linked List to hold each "square".
The entire Generic Double Linked List is the board. This is a single player game,
and you win when you land on the WIN
TWO PLAYER.
space.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "twoPlayer.h"

int main() {
  int count = 0;    // number of movements until a win
  space_t * board;
  node_t *player,*first,*last;
  FILE *fp;
  fp = fopen("board.txt", "r"); //board included in .zip file
  board = createBoardSpace(fp);
  if (board==NULL){ // base case of file being empty
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
  char * name1 = "Player 1";
  char * name2 = "Player 2";
  player_t * pfirst = createPlayer(name1, first);
  player_t * psecond = createPlayer(name2, first);    //player is a struct
  node_t * node1 = createNode(pfirst);       //doubly linked list as initially
  node_t * node2 = createNode(psecond);           //designed
  node1->next = node2;
  node1->prev = node2;
  node2->next = node1;
  node2->prev = node1;
  node_t * temp = node1;
  player_t * currentplayer = temp->item;
  player = currentplayer->locus;
  space_t * currentTile = player->item;
  char*win = "WIN";
  while(1){
    while(1){
      printf("%s's turn:\n", currentplayer->name);
      space_t * c = player->item;
      char * str1 = "GOBACK";
      char * str2 = "GOFORWARD";    //the four special movementsmovements
      char * str3 = "WIN";
      char * str4 = "NONE";
      if (strcmp(c->special, str1)==0) {
        count++;
        printf("Color: %s Special: %s X: %d\n", c->color, c->special, c->x);
        int moveNum = c->x;  // the third column, the integer, is the # movements
        int i;
        for (i=0;i<moveNum;i++){
          player = player->prev;
        }
      }
      else if (strcmp(c->special, str2)==0) {
        count++;
        printf("Color: %s Special: %s X: %d\n", c->color, c->special, c->x);
        int moveNum = c->x;
        int i;      //^ outlines the board structure
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
    srand(time(NULL));
    int color = randomNumber(4);
    char*colour;
    if (color == 1){
      colour = "RED";
    }
    else if (color == 2){
      colour = "BLUE";
    }                       // each color is a number, 1-4
    else if (color == 3){   // which represents number of steps to be taken
      colour = "ORANGE";
    }
    else if (color == 4){
      colour = "GREEN";
    }
    player = findColour(colour,player);
    currentTile = player->item;
    currentplayer->locus = player;
    temp = temp->next;
    currentplayer = temp->item;
    player = currentplayer->locus;
}
  printf("Congrats, %s wins!\n", currentplayer->name); //which of two players wins
  printf("Number of moves until a win: %d\n", count);   //number of moves it took
}

space_t *createBoardSpace(FILE *myFile) {
  char *color;
  char *special;
  char dummy;
  int tempint;
  space_t *board = (space_t *)malloc(sizeof(space_t));
  board->color = (char *)malloc(sizeof(char) * 10);
  board->special = (char *)malloc(sizeof(char) * 10);

  fscanf(myFile,"%s%s%d%c", board->color, board->special, &tempint, &dummy);
  if (feof(myFile)){      // scan the file until empty, aka no more steps to take
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
  if (position->next == NULL){
    return position;
  }                           // let color on the board is the position
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
player_t * createPlayer(char*name,void*location){
  player_t * player = (player_t *)malloc(sizeof(player_t));
  player->name = name;
  player->locus = location;
  return player;
}
