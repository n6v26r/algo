#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
FILE *fin, *fout;
 
const int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
enum an{
  ian,
  feb,
  mar,
  apr,
  mai,
  iun,
  iul,
  aug,
  sep,
  oct,
  nov,
  dec
};
 
typedef struct{
  int val;
  char type;
}time;
 
char month[20]; int ms;
time intv[2001];
 
int getMonth(){
  switch(month[0]){
  case 'i':
    switch(month[1]){
    case 'a':
      return ian;
      break;
    case 'u':
      switch(month[2]){
      case 'n':
        return iun;
        break;
      case 'l':
        return iul;
        break;
      default:
        return -1;
        break;
      }
      break;
    default:
      return -1;
      break;
    }
    break;
  case 'f':
    return feb;
    break;
  case 'm':
    switch(month[2]){
    case 'r':
      return mar;
      break;
    case 'i':
      return mai;
      break;
    default:
      return -1;
      break;
    }
    break;
  case 'a':
    switch(month[1]){
      case 'p':
        return apr;
        break;
      case 'u':
        return aug;
        break;
      default:
        return -1;
        break;
    }
    break;
  case 's':
    return sep;
    break;
  case 'o':
    return oct;
    break;
  case 'n':
    return nov;
    break;
  case 'd':
    return dec;
    break;
  }
  return -1;
}
 
int readDate(){
  int day;fscanf(fin, "%d", &day);
  //printf("%d\n", day);
  int hour=0; int min=0;
  char c = fgetc(fin);
  while(c==' ') c=fgetc(fin);
  ms = 0;
  while(isalpha(c)){
    month[ms++]=(c<='Z')? 'a'+c-'A' : c;
    c=fgetc(fin);
  }
  //printf("%s\n", month);
  while(c==' ') c=fgetc(fin);
  while(isdigit(c))
    hour=hour*10+c-'0', c=fgetc(fin);
  while(c!='.') c=fgetc(fin);
  c=fgetc(fin);
  while(c==' ') c=fgetc(fin);
  while(isdigit(c))
    min=min*10+c-'0', c=fgetc(fin);
  ungetc(c, fin);
 
  int mon = getMonth();
  int days = day;
  for(int i=0; i<mon; i++)
    days+=v[i];
  return (days*24+hour)*60+min;
}
 
int comp(const void* a, const void* b){
  int _a = ((const time*) a) ->val;
  int _b = ((const time*) b) ->val;
 
  int ta = ((const time*) a) ->type;
  int tb = ((const time*) b) ->type;
 
  if(_a!=_b)
    return (_a>_b)-(_b>_a);
  return -((ta>tb)-(tb>ta));
}
 
int main(){
  int n;
  int max = 0;
  fin=fopen("agenda.in", "r");
  fscanf(fin, "%d\n", &n);
  char c = 0;
  int i=0;
  while(c!=EOF){
    int d1 = readDate();
 
    c=fgetc(fin);
    while(c!='-'){
      c=fgetc(fin);
    }
 
    int d2 = readDate();
 
    c=fgetc(fin);
    while(c!='\n')
      c=fgetc(fin);
    c=fgetc(fin);
    ungetc(c, fin);
 
    printf("%d\n", c);fflush(stdout);
    int dif = d2-d1;
    if(dif>max)
      max = dif;
 
    intv[i].val=d1;
    intv[i].type=0;
    i++;
    intv[i].val=d2;
    intv[i].type=1;
    i++;
  }
  fclose(fin);
  int size = i;
 
  int intersect=0;
  int maxint = 0;
  int maxfree = 0;
 
  qsort(intv, size, sizeof(time), comp);
 
  if(n==2){
  for(int i=0; i<size; i++){
    if(intv[i].type==0)
      intersect++;
    else
      intersect--;
 
    if(intersect>maxint)
      maxint = intersect;
    }
  }
 
  int last=0;
  int free = 0;
 
  for(i=0; i<size && intv[i].type == 0; i++){intersect++;};
  last = intv[i].val; intersect--;
  i++;
 
  for(; i<size; i++){
    if(intv[i].type==1)
      last = intv[i].val, intersect--;
    else{
      free = intv[i].val - last, intersect++;
 
      if(free>maxfree && intersect==1)
        maxfree = free;
    }
  }
 
 
  fout=fopen("agenda.out", "w");
  if(n==1){
    int dd = max/24/60; max%= 24*60;
    int dh = max/60; max%=60;
    int dm = max;
    fprintf(fout, "%d %d %d\n", dd, dh, dm);
  }else if(n==2){
    fprintf(fout, "%d\n", maxint);
  }
  else{
    int dd = maxfree/24/60; maxfree%= 24*60;
    int dh = maxfree/60; maxfree%=60;
    int dm = maxfree;
    fprintf(fout, "%d %d %d\n", dd, dh, dm);
  }
  fclose(fout);
  return 0;
}
