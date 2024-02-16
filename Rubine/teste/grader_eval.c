#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define LIN_INCORECT 1
#define REZ_INCORECT 2
#define REZ_PARTIAL_B 4
#define LIPSA 3

char linie[1000000], extra[1000000];
const char *erori[] = { "OK", "linie incorecta", "rez incorect", "lipsa","rez partial" };

void error(const char msg[], int p) {
  fprintf(stderr, msg);
  printf("%d", p);
  exit(0);
}

void error3( int b1, int b2, int b3 ) {
  int punctaj = 0;
  char msg[1000] = { 0 };

  if ( b1 == 0 )
    punctaj += 3;
  if ( b2 == 0 )
    punctaj += 4;
  if ( b2 == 4 )
    punctaj += 2;
  if ( b3 == 0 )
    punctaj += 3;

  sprintf( msg, "a) %s;   b) %s;   c) %s", erori[b1], erori[b2], erori[b3] );

  error( msg, punctaj );
}

void bun(int p) {
  fprintf( stderr, "OK\n" );
  printf("%d", p);
  exit(0);
}

int main() {
  FILE *fok, *fout;
  int ok1, ok21, ok22, ok3;
  int out1, out21, out22, out3;
  int b1, b2, b3;

  fok = fopen( "rubine.ok", "r" );
  fscanf( fok, "%d%d%d%d", &ok1, &ok21, &ok22, &ok3 );
  fclose( fok );

  fout = fopen( "rubine.out", "r" );
  if(!fout)
    error("Fisier de iesire 'rubine.out' lipsa!", 0);

  b1 = b2 = b3 = LIPSA;
  // verifica prima linie
  if ( fgets( linie, 1000000, fout ) == NULL )
    error("Fisier de iesire 'rubine.out' gol!", 0);
  if ( sscanf( linie, "%d %s", &out1, extra ) != 1 )
    b1 = LIN_INCORECT;
  else if ( ok1 != out1 )
    b1 = REZ_INCORECT;
  else
    b1 = 0;

  // verifica a doua linie
  if ( fgets( linie, 1000000, fout ) == NULL )
    error3( b1, b2, b3 );
  if ( sscanf( linie, "%d%d %s", &out21, &out22, extra ) != 2 )
    b2 = LIN_INCORECT;
  else if ( ok21 != out21 && ok22 != out22 )
            b2 = REZ_INCORECT;
  else if ( ok21 == out21 && ok22 == out22 )
            b2 = 0;
  else      b2 = REZ_PARTIAL_B;

  // verifica a treia linie
  if ( fgets( linie, 1000000, fout ) == NULL )
    error3( b1, b2, b3 );
  if ( sscanf( linie, "%d %s", &out3, extra ) != 1 )
    b3 = LIN_INCORECT;
  else if ( ok3 != out3 )
    b3 = REZ_INCORECT;
  else
    b3 = 0;

  if ( b1 || b2 || b3 )
    error3( b1, b2, b3 );
  bun(10);

  return 0;
}
