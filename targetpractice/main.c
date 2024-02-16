#include <stdio.h>

#define MIN(a, b) (((a)<(b))?(a):(b))

int t;

int scorem[10][10] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
{1, 2, 3, 3, 3, 3, 3, 3, 2, 1},
{1, 2, 3, 4, 4, 4, 4, 3, 2, 1},
{1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
{1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
{1, 2, 3, 4, 4, 4, 4, 3, 2, 1},
{1, 2, 3, 3, 3, 3, 3, 3, 2, 1},
{1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int main(){
  int score;
  scanf("%d\n", &t);
  while(t>0){
    score=0;
    for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
        char hit = fgetc(stdin);
        if(hit=='X'){
          score+=scorem[i][j];
        }
      }
      fgetc(stdin); // \n
    }
    printf("%d\n", score);
    t--;
  }
  return 0;
}
