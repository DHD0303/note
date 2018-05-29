#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "stdbool.h"
#include "Windows.h"
#include "conio.h"

#define High 20
#define Width 41

int score, velocity, direction, die;
int mov[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};

char game_interface[High][Width];
int food[2];
typedef struct Snake{
  int x;
  int y;
  struct Snake * previous;
  struct Snake * next;
}Snake, * pSnake;

pSnake tail, head;

void init(void) {
  int i, j;
  for(i=0; i<High; i++) {
    for(j=0; j<Width; j++) {
      game_interface[i][j] = 32;
    }
  }

  return;
}

bool check(int x, int y) {
  if( x && y && x!=High-1 && y!=Width-1 && game_interface[x][y] != '*') {
    return true;
  } else {
    return false;
  }
}

void clean_view(void) {
  system("cls");

  return;
}

void set_node(pSnake node, pSnake next, pSnake previous, int x, int y) {
  node->x = x; node->y = y; node->next = next; node->previous = previous;
}

void set_food(void) {
  int x, y;
  while(1) {
    x=rand()%High;
    y=rand()%Width;
    if( check(x, y) && game_interface[x][y]== ' ') {
      food[0]=x; food[1]=y;
      game_interface[x][y] = '#';
      break;
    }
  }

  return;
}

void eat(void) {
  set_food();
  score++; velocity+=10;
  if(velocity>350) velocity = 350;
  return;
}

pSnake init_snake(void) {
  pSnake head = (pSnake)malloc( sizeof(Snake) );
  set_node(head, NULL, NULL, 1, 10);
  die = score = velocity = 0;
  direction = 2;
  set_food();

  return head;
}

void set_border(void) {
  int i, j=Width-1;
  for(i=0; i<High; i+=2) {
    game_interface[i][0] = '|';
    game_interface[i][j] = '|';
  }
  j=High-1;
  for(i=0; i<Width; i+=2) {
    game_interface[0][i] = '=';
    game_interface[j][i] = '=';
  }

  return;
}

void move(pSnake head) {
  int x=tail->x, y=tail->y;
  game_interface[tail->x][tail->y] = ' ';
  pSnake temp = tail;
  while( temp!=head ) {
    temp->x = temp->previous->x;
    temp->y = temp->previous->y;
    game_interface[temp->x][temp->y] = '*';
    temp = temp->previous;
  }
  head->x += mov[direction][0];
  head->y += mov[direction][1];
  if( !check(head->x, head->y) ) {
    game_interface[food[0]][food[1]] = ' ';
    die=1;
    if( game_interface[head->x][head->y] == '*' ) {
      die=2;
    }
    return;
  }
  if( food[0] == head->x && food[1] == head->y) {
    eat();
    tail->next = (pSnake)malloc( sizeof(Snake) );
    set_node(tail->next, NULL, tail, x, y);
    game_interface[x][y] = '*';
    tail = tail->next;
  }
  game_interface[head->x][head->y] = '@';
  return;
}

void updata(void) {
  int i, j, c;
  Sleep(400-velocity);
  if( kbhit() ) {
    while( kbhit() ) {
      c = getch();
    }
    switch ( c ) {
      case 72: if(direction != 2) direction=0; break;
      case 77: if(direction != 3) direction=1; break;
      case 80: if(direction != 0) direction=2; break;
      case 75: if(direction != 1) direction=3; break;
      case 32:
        printf("暂停 任意键继续\n");
        while( !kbhit() ) continue;
    }
  }
  move(head);
  clean_view();
  printf("score: %d\n", score);
  for(i=0; i<High; i++) {
    for(j=0; j<Width; j++) {
      printf("%c", game_interface[i][j]);
    }
    printf("\n");
  }
}
void delete_snake(void) {
  while( head->next!=NULL ) {
    game_interface[head->x][head->y] = ' ';
    head = head->next;
    free(head->previous);
  }
  game_interface[head->x][head->y] = ' ';
  free(head->previous);
  free(head);

  return;
}
int main(void) {
  init();
  int c=49;
  srand( time(NULL) );
  while( c==49 ) {
    set_border();
    head = init_snake();
    tail = head;
    while(!die) {
      updata();
    }
    clean_view();
    delete_snake();
    if(die == 1) {
      printf("撞墙死亡\n");
    } else {
      printf("咬到自己\n");
    }
    printf("您的最终得分为%d\n按1继续其他任意键退出\n", score);
    while( kbhit() ){ ; }
    while( !kbhit() ){ ; }
    while( kbhit() ) {
      c = getch();
    }
  }

  return 0;
}
