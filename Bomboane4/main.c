// 100p (parsing furat)

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define MAXSIZE 100000
#define MAXLOG10 10
#define BUFSIZE (128 * 1024)

/*
 CTRL-C, CTRL-V la nitel parsing bun (poate merge):
 */

FILE *fin, *fout;
int p10[MAXLOG10 + 1] = { 0, 1, 10, 100, 1000, 10000, 100000, 1000000,
  10000000, 100000000, 1000000000 }; // santinela pe prima pozitie
int rpos; char rbuf[BUFSIZE];
int wpos; char wbuf[BUFSIZE];

// initializare citire
static inline void initRead() {
  rpos = BUFSIZE - 1;
}

// citire caracter
static inline char readChar() {
  if ( !(rpos = (rpos + 1) & (BUFSIZE - 1)) )
    fread( rbuf, 1, BUFSIZE, fin );
  return rbuf[rpos];
}
 
// citire intreg cu semn
int readInt() { // citeste un intreg
  int ch, res = 0, semn = 1;

  while ( isspace( ch = readChar() ) );
  if ( ch == '-' ) {
    semn = -1;
    ch = readChar();
  }
  do
    res = 10 * res + ch - '0';
  while ( isdigit( ch = readChar() ) );

  return semn * res;
}

// initializare scriere
static inline void initWrite() {
  wpos = 0;
}

// scriere caracter
static inline void writeChar( char ch ) {
  wbuf[wpos] = ch;
  if ( !(wpos = (wpos + 1) & (BUFSIZE - 1)) )
    fwrite( wbuf, 1, BUFSIZE, fout );
}
 
// scriere intreg cu semn
void writeInt( int x , char end) {
  int i, cf;

  if ( x < 0 ) {
    writeChar( '-' );
    x = -x;
  }
  i = MAXLOG10;
  while ( p10[i] > x )
    i--;
  if ( i == 0 )
    writeChar( '0' );
  else
    do {
      cf = '0';
      while ( p10[i] <= x ) {
        x -= p10[i];
        cf++;
      }
      writeChar( cf );
    } while ( --i > 0 );
  
  if(end!=0)
    writeChar( end ); 
}
// scriere intreg de tip long long (stupid but will do)
void writeLongLong( long long x) {
  while(x>INT_MAX){
    writeInt(x/1000000000, 0);
    x%=1000000000;
  }
  writeInt(x, ' ');
}

// scrie caracterele ramase in buffer
static inline void flushBuf() {
  fwrite( wbuf, 1, wpos, fout );
}

typedef struct{
  long long a;
  int b;
}fractie;

typedef struct{
  long long sum;
  int count;
}avg;

int cmmdc(long long a, int b){
  while(b>0){
    int r = b;
    b = a % b;
    a = r;
  }
  return a;
}

long long comp(fractie a, fractie b){
  return (a.a*b.b)-(b.a*a.b); 
}

fractie newFractie(long long a, int b){
  fractie new = {a, b};
  long long div = cmmdc(a, b);
  new.a/=div;
  new.b/=div;
  return new;
}

avg newAvg(int sum, int count){
  avg a = {sum, count};
  return a;
}

int v[MAXSIZE+1];
avg a[MAXSIZE+1];

int main(){
  int n;
  fin = fopen("bomboane4.in", "r");
  initRead();
  n = readInt();
  for(int i=0; i<n; i++){
    v[i] = readInt();
  }
  fclose(fin);

  a[n-1] = newAvg(v[n-1], 1);
  for(int i=n-2; i>=0; i--){
    a[i] = newAvg(v[i], 1);
    int j = i+1;
    while(true && j<n){
      if(comp(newFractie(a[j].sum, a[j].count), newFractie(a[i].sum, a[i].count))<=0)
        a[i].sum+=a[j].sum, a[i].count+=a[j].count;
      else 
        break;
      j = i + a[i].count;
    }
  }

  fout = fopen("bomboane4.out", "w");
  initWrite();
  for(int i=0; i<n; i++){
    fractie f = newFractie(a[i].sum, a[i].count);
    for(int j=0; j<a[i].count; j++){
      writeLongLong(f.a);
      writeInt(f.b, '\n'); 
    }
    i+=a[i].count-1;
  }
  flushBuf();
  fclose(fout);
}
