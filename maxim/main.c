//Rezolvare Bonus (pentru faima si prestigiu)
//Complexitate memorie: O(Σ)
#include <stdio.h>
 
// all stored values are digits,
// so we can store just that. digits.
// 10 digits with their frequencies, to be exact.
#define QUEUESIZE 16
#define MAXCIF 5
 
int a, b;
 
typedef struct{
  int val; // digit
  int frecv; // how many times that digit shows up
}node;
 
struct queue{
  node pair[QUEUESIZE+1];
  int first;
  int last;
};
 
// I/O
FILE *fin, *fout;
 
// queue
struct queue max;
 
// keep track of current number
char cif[MAXCIF+1]; int start;
int currNum, currDig=MAXCIF-1;
 
int getNextDigit();
 
int next(){
  currNum++;
  if(currNum>b){
    return -1;
  }
 
  int cp = currNum;
  int i=MAXCIF;
  while(cp>0){
    cif[--i]=cp%10;
    cp/=10;
  }
 
  start = i;
  currDig = start-1;
  return getNextDigit();
}
 
int getNextDigit(){
  currDig++;
  if(currDig>=MAXCIF)
    return next();
  return cif[currDig];
}
 
// dequeue operations
// (just for sake of it)
char empty(struct queue* q){
  return (*q).first==(*q).last;
}
 
node last(struct queue* q){
  return (*q).pair[((*q).last-1+QUEUESIZE)%QUEUESIZE];
}
 
node first(struct queue* q){
  return (*q).pair[(*q).first];
}
 
void pushlast(struct queue* q, node pair){
  node _last = last(q);
  if(empty(q
           ) || _last.val != pair.val){
    (*q).pair[(*q).last]=pair;
    (*q).last=((*q).last+1)%QUEUESIZE;
  }
  else{
    (*q).pair[((*q).last-1+QUEUESIZE)%QUEUESIZE].frecv+=pair.frecv;
  }
}
 
void pushfirst(struct queue* q, node pair){
  node _first = first(q);
  if(_first.val != pair.val){
    (*q).first=((*q).first-1+QUEUESIZE)%QUEUESIZE;
    (*q).pair[(*q).first]=pair;
  }
  else{
    (*q).pair[(*q).first].frecv++;
  }
}
 
node poplast(struct queue* q){
  // ignore frecv, will act like a stack
  node p = last(q);
  (*q).last=((*q).last-1+QUEUESIZE)%QUEUESIZE;
  return p;
}
 
int popfirst(struct queue* q){
  node p = first(q);
  if(p.frecv==1)
    (*q).first=((*q).first+1)%QUEUESIZE;
  else
    (*q).pair[(*q).first].frecv--;
  return p.val;
}
 
int main(){
  cif[MAXCIF]='\0';
  int k;
  fin=fopen("maxim.in", "r");
  fscanf(fin, "%d%d%d", &a, &b, &k);
  fclose(fin);
 
  currNum = a-1;
 
  // fill queue
  for(int i=0; i<k; i++){
    int val = getNextDigit();
    while(!empty(&max) && last(&max).val<val)
      poplast(&max);
 
    node pair = {val, 1};
    pushlast(&max, pair);
  }
 
  fout=fopen("maxim.out", "w");
 
  // no k needed. :)
  // With more digits removed, the window gets shorter and shorter.
  // (It starts with k elements and only gets smaller afterwards:
  //  + 1 digit back, -1 digit front, -all digits needed to reach the first one)
 
  while(1){
    int val = getNextDigit();
    if(val>-1){ // digit?
      while(!empty(&max) && last(&max).val<val) // acts like a stack
        poplast(&max);
 
      node pair = {val, 1};
      pushlast(&max, pair);
    }
    else // no digit :(
      break;// very structured
 
    int out = popfirst(&max);
    fputc(out+'0', fout);
  }
  fputc('\n', fout);
  fclose(fout);
  return 0;
}
