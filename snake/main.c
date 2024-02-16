#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 1000
#define INF __INT32_MAX__
#define BLOCKED -1
#define DIR 4

typedef struct{
  int lin;
  int col;
}pos;

pos err = {-INF-1, -INF-1};

pos head;
pos tail;

int p, n, m, z, a;
int mat[MAXSIZE+1][MAXSIZE+1];
int dir_lin[DIR] = {-1, 0, 1, 0};
int dir_col[DIR] = {0, 1, 0, -1};
int dir;
int length;

pos getNewHead(pos head, int dir){
  return (pos){(n+head.lin+dir_lin[dir])%n, (n+head.col+dir_col[dir])%n};
}

pos getNewTail(pos tail){
  for(int i=0; i<DIR; i++){
    pos _new = getNewHead(tail, i);
    if(mat[_new.lin][_new.col]==mat[tail.lin][tail.col]+1){
      return _new;
    }
  }
  return err;
}


void debug(){
  printf("\033[H\033[J");
  printf("MAP:\n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(head.lin==i && head.col==j){
        printf("☻");
      }
      else if(tail.lin==i && tail.col==j){
        pos p = {i, j};
        pos prev = getNewHead(p, 3);
        pos next = getNewHead(p, 1);
        pos up = getNewHead(p, 0);
        pos down = getNewHead(p, 2);
        if(mat[prev.lin][prev.col]>0) printf("<");
        else if(mat[next.lin][next.col]>0) printf(">");
        else if(mat[up.lin][up.col]>0) printf("^");
        else if(mat[down.lin][down.col]>0) printf("v");
        else printf("*");
      }
      else{
        if(mat[i][j] == BLOCKED) printf("#");
        else if(mat[i][j] == INF) printf(".");
        else if(mat[i][j]){
          pos p = {i, j};
          pos prev = getNewHead(p, 3);
          pos next = getNewHead(p, 1);
          pos up = getNewHead(p, 0);
          pos down = getNewHead(p, 2);
          if(mat[prev.lin][prev.col]>0){
            if(mat[next.lin][next.col]>0)
              printf("-");
            else if(mat[up.lin][up.col]>0)
              printf("┘");
            else if(mat[down.lin][down.col]>0)
              printf("┐");
            else printf("-");
          }
          else if(mat[next.lin][next.col]>0)
            if(mat[prev.lin][prev.col]>0)
              printf("-");
            else if(mat[up.lin][up.col]>0)
              printf("└");
            else if(mat[down.lin][down.col]>0)
              printf("┌");
            else printf("-");
          else
            printf("|");
        }
        else printf(" ");
      }
    }
    printf("\n");
  }
  printf("TAIL: [%d,%d]\nHEAD:[%d,%d]\nLENGTH:[%d]\n", tail.lin, tail.col, head.lin, head.col, length);
  usleep(90000);
}


int main(){
    FILE *fin, *fout;
    fin = fopen("snake.in", "r");
    fscanf(fin, "%d\n%d %d\n%d\n", &p, &n, &m, &z);
    for(int i=0; i<z; i++){
      int lin, col;
      fscanf(fin, "%d %d\n", &lin, &col);
      mat[lin-1][col-1] = BLOCKED;
    }
    fscanf(fin, "%d\n", &a);
    for(int i=0; i<a; i++){
      int lin, col;
      fscanf(fin, "%d %d\n", &lin, &col);
      mat[lin-1][col-1] = INF;
    }
    fclose(fin);

    head = tail = (pos){0, 0};
    mat[head.lin][head.col] = 1;
    dir = 1;
    length = 1;
    debug();
    while(m>0){
      pos newHead = getNewHead(head, dir);
      if(mat[newHead.lin][newHead.col]==BLOCKED){
        newHead = getNewHead(head, (dir+1)%DIR);
        dir = (dir+1)%DIR;
      }
      bool moved = false;
      if(newHead.lin==tail.lin && newHead.col == tail.col){
        moved = true;
        pos newTail = getNewTail(tail);
        mat[tail.lin][tail.col] = 0;
        tail = newTail;
      }

      bool apple = false;
      if(mat[newHead.lin][newHead.col]==INF){
        mat[newHead.lin][newHead.col]=0;
        apple = true;
      }

      if(mat[newHead.lin][newHead.col]) break;
      mat[newHead.lin][newHead.col] = mat[head.lin][head.col]+1;
      head = newHead;

      if(!apple){
        if(!moved){
          pos newTail = getNewTail(tail);
          mat[tail.lin][tail.col] = 0;
          tail = newTail;
        }
      }
      else length++;

      debug();
      m--;
    }

    fout = fopen("snake.out", "w");
    if(p==1)
      fprintf(fout, "%d %d\n", head.lin+1, head.col+1);
    else if(p==2)
      fprintf(fout, "%d %d %d\n", head.lin+1, head.col+1, length);
    else
      fprintf(fout, "%d %d %d %d %d\n", head.lin+1, head.col+1, length, tail.lin+1, tail.col+1);
    fclose(fout);
    return 0;
}
