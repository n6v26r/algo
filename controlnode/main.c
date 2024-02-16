#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000

typedef struct{
  unsigned long long type;
  unsigned long long name;
}server;

int compServ(const void* a, const void* b){
  server _a = *((const server*)a);
  server _b = *((const server*)b);
 
  if(_a.type!=_b.type) return (_a.type>_b.type)-(_a.type<_b.type);	
  else return (_a.name>_b.name)-(_a.name<_b.name);
}

int comp(server a, server b){
  if(a.type!=b.type) return (a.type>b.type)-(a.type<b.type);	
  else return (a.name>b.name)-(a.name<b.name);
}

void swap(server *a, server *b){
  server aux = (*a);
  (*a) = (*b);
  (*b) = aux;
}

int pivot(server *v, int a, int b){
  server pi = v[a];
  int i=a, j=b;
  while(1){
    while(comp(v[i], pi)<0)i++;
    while(comp(v[j], pi)>0)j--;
    
    if(i>=j) return j;

    swap(&v[i], &v[j]);
    i++;
    j--;
  }
}

void quicksort(server *v, int a, int b){
  if(a<b){
    int pi = pivot(v, a, b);
    quicksort(v, a, pi);
    quicksort(v, pi+1, b);
  }
}

server serv[MAXSIZE+1]; int n;
char ip[40] = "";
int ips = 0;

int main(){
  int p;
  FILE *fin, *fout;
  fin=fopen("controlnode.in", "r");
  fscanf(fin, "%d\n", &p);
  char c = fgetc(fin);
  while(c!='#'){
    ips = 0;
    while(c!='\n'){
      if(c!=':')ip[ips++]=c;
      c=fgetc(fin);
    }
    {
      server new = {1, 1};
      for(int i=0; i<16; i++){
        new.type=new.type*16+(ip[i]>='a'?10+ip[i]-'a':ip[i]-'0');
      }
      for(int i=16; i<32; i++){
        new.name=new.name*16+(ip[i]>='a'?10+ip[i]-'a':ip[i]-'0');
      }
      serv[n++] = new;
    }
    c=fgetc(fin);
  }

  // Din motive pe care nu le cunosc, functia custom intra in memorie...
  quicksort(serv, 0, n-1);
  // 
  // i dont understand...
     // qsort(serv, n, sizeof(server), compServ);

  fout=fopen("controlnode.out", "w");
  if(p==2){
    for(int i=0; i<n; i++){
      server s = serv[i];
      ips = 0;
      unsigned long long p16=1;
      for(int i=0; i<15; i++){
        p16*=16;
      }
      int c=0;
      while(p16>0){
        ip[ips++] = (s.type/p16>=10?s.type/p16-10+'a':s.type/p16+'0');
        s.type%=p16;
        p16/=16;
        c++;
        if(!(c%4)){
          ip[ips++]=':';	
          c=0;
        }
      }
     
      p16=1;	
      for(int i=0; i<15; i++){
        p16*=16;
      }
      c=0;
      while(p16>0){
        ip[ips++] = (s.name/p16>=10?s.name/p16-10+'a':s.name/p16+'0');
        s.name%=p16;
        p16/=16;
        c++;
        if(!(c%4)){
          ip[ips++]=':';
          c=0;
        }
      }
      ip[ips-1]='\0';
      ips--;
      fprintf(fout, "%s\n", ip);
    }
  }
  else{
    int total=0;
    for(int i=0; i<n; i++){
      while(i<n-1 && serv[i+1].type == serv[i].type)i++;
      total++;
    }
    fprintf(fout, "%d\n", total);
  }
  fclose(fout);
  return EXIT_SUCCESS;
}
