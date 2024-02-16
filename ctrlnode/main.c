#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 1000000
#define GROUPS 20
#define NIL -1

typedef struct{
  int size;
  char content[50];
}string;

typedef struct{
  unsigned long long type;
  unsigned long long name;
}server;

int v[MAXSIZE+1];
int next[MAXSIZE+1];
server val[MAXSIZE+1];

int includes[MAXSIZE+1];
int nextg[MAXSIZE+1];

server working[MAXSIZE+1]; int size;

void getGroup(string *name, FILE *fin){
  char c = fgetc(fin);
  while(c!=']'){
    name->content[name->size++]=c;
    c=fgetc(fin);
  }
}

void getName(string *name, FILE *fin){
  char c = fgetc(fin);
  while(c!='\n'){
    name->content[name->size++]=c;
    c=fgetc(fin);
  }
}

bool isGroup(string *name){
  {
    char cmp[] = "all\0";
    bool flag = true;
    for(int i=0; i<3; i++){
      if(name->content[i]!=cmp[i]) flag = false;
    }
    if(flag) return true;
  }

  char cmp[] = "group\0";
  for(int i=0; i<5; i++){
    if(name->content[i]!=cmp[i]) return false;
  }
  return true;
}

int getIndex(string *name){
  int i=0;
  while(i<name->size && !isdigit(name->content[i])){i++;}
  int n=0;
  if(i>=name->size) return -1;
  while(i<name->size && isdigit(name->content[i])){n=n*10+name->content[i]-'0';i++;}
  return n;
}
server getServer(string *name){
  server new = {1, 1};
  int c=0;
  for(int i=0; i<20; i++){
    new.type=new.type*16+(name->content[i]>='a'?10+name->content[i]-'a':name->content[i]-'0');
    c++;
    if(!(c%4)){
      i++;
      c=0;
    }
  }
  for(int i=20; i<39; i++){
    new.name=new.name*16+(name->content[i]>='a'?10+name->content[i]-'a':name->content[i]-'0');
    c++;
    if(!(c%4)){
      i++;
      c=0;
    }
  }
  return new;
}

void add(int workingIndex){
  int j = v[workingIndex];
  while(j!=NIL){
    working[size++]=val[j];
    j=next[j];
  }
}

bool eval(int workingIndex){
  int includej=includes[workingIndex];
  if(includej==-5) return true;
  while(includej!=NIL){
    add(includej);
    eval(includej);
    includej=nextg[includej];
  }
  return false;
}

int compServ(const void* a, const void* b){
  server _a = *((const server*)a);
  server _b = *((const server*)b);

  if(_a.type!=_b.type) return (_a.type>_b.type)-(_a.type<_b.type);
  else return (_a.name>_b.name)-(_a.name<_b.name);
}

string getbackaddr(server s){
  string name = {0, ""};
  unsigned long long p16=1;
  for(int i=0; i<15; i++){
    p16*=16;
  }
  int c=0;
  while(p16>0){
    name.content[name.size++] = (s.type/p16>=10?s.type/p16-10+'a':s.type/p16+'0');
    s.type%=p16;
    p16/=16;
    c++;
    if(!(c%4)){
      name.content[name.size++]=':';
      c=0;
    }
  }

  p16=1;
  for(int i=0; i<15; i++){
    p16*=16;
  }
  c=0;
  while(p16>0){
    name.content[name.size++] = (s.name/p16>=10?s.name/p16-10+'a':s.name/p16+'0');
    s.name%=p16;
    p16/=16;
    c++;
    if(!(c%4)){
      name.content[name.size++]=':';
      c=0;
    }
  }
  name.content[name.size-1]='\0';
  name.size--;
  return name;
}

int main(){
  memset(v, NIL, sizeof(v));
  memset(includes, NIL, sizeof(includes));
  FILE *fin, *fout;
  fin = fopen("ctrlnode.in", "r");
  char c = fgetc(fin);
  int workingIndex = -1;
  int i=0;
  string name = {0, ""};
  while(c!='#'){
    switch (c) {
      case '[':;
        name = (string) {0, ""};
        getGroup(&name, fin);
        workingIndex = getIndex(&name);
        break;
      case '\n':
        break;
      default:;
        name = (string) {1, {c}};
        getName(&name, fin);
        if(!isGroup(&name)){
          server serv = getServer(&name);
          working[size++]=serv;
          if(workingIndex!=-1){
            next[i]=v[workingIndex];
            v[workingIndex]=i;
            val[i]=serv;
            i++;
          }
        }
        else{
          if(workingIndex!=-1){
            int num = getIndex(&name);
            if(num==-1) includes[workingIndex]=-5;
            else if(includes[workingIndex]!=-5){
              nextg[num]=includes[workingIndex];
              includes[workingIndex]=num;
            }
          }
        }
        break;
    }
    c=fgetc(fin);
  }
  while(c=='#') c=fgetc(fin);
  name = (string) {0, ""};
  getName(&name, fin);
  workingIndex=getIndex(&name);
  while (c!='\n')c=fgetc(fin);
  c=fgetc(fin)-'0';
  fclose(fin);

 /*
  for(int i=0; i<14; i++){
    printf("%d. ", i); fflush(stdout);
    int j = v[i];
    while(j!=NIL){
      printf("|%llu %llu|->", val[j].type, val[j].name);
      j=next[j];
    }printf("*\n   ");
    j = includes[i];
    while(j!=NIL){
      printf("|%d|->", j);
      j=nextg[j];
    }printf("*\n");
  }
  */
  if(workingIndex!=-1){
    int backup = size;
    size=0;


    if(eval(workingIndex)) size = backup;
    else add(workingIndex);
  }

  qsort(working, size, sizeof(server), compServ);

  fout = fopen("ctrlnode.out", "w");
  if(c==1){
    for(int i=0; i<size; i++){
      fprintf(fout, "%s\n", getbackaddr(working[i]).content);
    }
  }
  else {
    int consec=1;
    int max=1, maxp=0;
    for(int i=1; i<size; i++){
      if(working[i].type!=working[i-1].type) consec=1;
      else consec++;
      if(consec>max){max=consec; maxp=i;}
    }
    string s = getbackaddr(working[maxp]);
    s.content[19]='\0';
    fprintf(fout, "%s\n", s.content);
  }
  fclose(fout);
  return EXIT_SUCCESS;
}
