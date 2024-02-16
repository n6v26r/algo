#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

// lungimea maxima a fisierului sursa - schimba aici pentru alte valori
#define MAX_SOURCE_SIZE 15360

#define OK 0
#define LIN_INCORECT 1
#define REZ_INCORECT 2
#define LIPSA 3
#define VECTORI 4
#define BUCLE 5
#define DECIZII 6
#define DECIZII_MASCATE 7

#define FTYPE_ERR 0
#define FTYPE_CPP 1
#define FTYPE_C 2
#define FTYPE_PAS 3
#define FTYPE_FPC 4

char *ext[] = { "", ".cpp", ".c", ".pas", ".fpc" };
char *erori[] = { "OK", "linie incorecta", "rezultat incorect", "lipsa",
                  "foloseste vectori", "foloseste cicluri",
                  "foloseste decizii",
                  "decizii mascate: abs/min/max/etc"
                };
char linie[1000001];
int lcorecta[1000000]; // vectorul de corectitudine a liniilor 0 = corect

void error(char msg[], int p) {
    fprintf(stderr, msg);
    printf("%d", p);
    exit(0);
}

void bun(int p) {
    fprintf( stderr, "OK\n" );
    printf("%d", p);
    exit(0);
}

// copiaza src in dest, inclusiv '\0', si returneaza lungimea
int cpstr( char *dest, char *src ) {
    int i = 0;
    do dest[i] = src[i];
    while ( src[i++] );
    return i-1;
}

// returneaza tipul sursei, vezi constantele definite mai sus
int openSource( char *name, FILE **dest ) {
    char newname[50];
    int len;

    len = cpstr( newname, name );

    cpstr( newname + len, ext[FTYPE_CPP] ); // incercam cpp
    if ( ((*dest) = fopen( newname, "r" )) )
        return FTYPE_CPP;

    cpstr( newname + len, ext[FTYPE_C] ); // incercam c
    if ( ((*dest) = fopen( newname, "r" )) )
        return FTYPE_C;

    cpstr( newname + len, ext[FTYPE_PAS] ); // incercam pas
    if ( ((*dest) = fopen( newname, "r" )) )
        return FTYPE_PAS;

    cpstr( newname + len, ext[FTYPE_FPC] ); // incercam pas
    if ( ((*dest) = fopen( newname, "r" )) )
        return FTYPE_FPC;

    return FTYPE_ERR; // n-am gasit nici un fisier sursa, eroare
}

// returneaza 1 daca sirul este fie NULL, fie contine doar whitespace
int sempty( char *s ) {
    if ( !s )
        return 1;
    while ( *s && isspace( *s ) )
        s++;
    return (*s) == '\0';
}

// copiaza primul cuvint din src in dest
// returneaza unde am ramas in src sau NULL daca nu am gasit cuvint
// ignora whitespace
char *sgetw( char *src, char *dest ) {
    while ( isspace( *src ) ) // ignoram spatii
        src++;
    if ( (*src) == '\0' ) // n-am gasit nici un cuvint
        return NULL;
    while ( *src && !isspace( *src ) )
        (*(dest++)) = (*(src++));
    *dest = '\0';
    return src;
}

// returneaza:
//   0 daca sint la fel (diff returneaza sirul vid)
//   1 daca difera
//   2 daca lipseste .out
//   3 daca lipseste .ok
int graderDiff( char *nout, char *nok, int lineLen ) {
    FILE *fout, *fok;
    char linout[lineLen], linok[lineLen];
    char wordout[lineLen], wordok[lineLen];
    char *lout, *lok;
    int nrlin = 0, error = 0;

    fout = fopen( nout, "r" );
    if( !fout )
        return 2;

    fok = fopen( nok, "r" );
    if( !fok )
        return 3;

    linout[lineLen-1] = '\0';
    lout = fgets( linout, lineLen, fout );
    lok = fgets( linok, lineLen, fok );
    while ( lok ) {
        if ( linout[lineLen-1] ) {
            error = lcorecta[nrlin] = 1; // incorecta
        } else {
            if ( lout && lok )
                do {
                    lout = sgetw( lout, wordout );
                    lok =  sgetw( lok, wordok );
                } while ( lout && lok && !strcmp( wordout, wordok ) );
            if ( !sempty(lout) || !sempty(lok)   // liniile sint diferite
                    || strcmp( wordout, wordok ) )
                error = lcorecta[nrlin] = 1;       // incorecta
        }
        linout[lineLen-1] = '\0';
        lout = fgets( linout, lineLen, fout ); // citim urmatoarele linii
        lok = fgets( linok, lineLen, fok );
        nrlin++;
    }
    if ( !sempty(lout) )
        error = lcorecta[nrlin] = 1; // fisierul contine linii in plus
    lout = fgets( linout, lineLen, fout ); // citim urmatoarele linii
    if ( lout )
        error = lcorecta[nrlin] = 1; // fisierul contine linii in plus
    fclose( fout );
    fclose( fok );

    return error;
}

int main() {
    FILE *fsource, *fin;
    int ftype;
    size_t len;
    regex_t regvect, regwhile, regif, regifmasc;
    int reti;


    // deschidem si citim fisierul sursa in linie[]
    ftype = openSource( "datorii", &fsource );
    if ( ftype == FTYPE_ERR )
        error("Fisier sursa lipsa!", 0);
    len = fread( linie, sizeof(char), 1000000, fsource );
    if ( len == 0 )
        error("Fisier sursa necitibil!", 0);
    if ( len > MAX_SOURCE_SIZE )
        error("Sursa depaseste limita admisa", 0);
    fclose( fsource );
    linie[len] = '\0'; // ca sa fim siguri

    /*
    // foloseste vectori?
    reti = regcomp(&regvect, "\\\[.*]", REG_NOSUB );
    if ( reti )
      error( "Eroare compilare regex vectori.\n", 0 );
    reti = regexec(&regvect, linie, 0, NULL, 0);
    if( !reti )
      error(erori[VECTORI], 0);
    else if( reti != REG_NOMATCH )
      error("Executie esuata regex vectori", 0);

    // foloseste bucle?
    reti = regcomp(&regwhile, "([ \t\n;]while[ \t\n\(])|([ \t\n;]for[ \t\n\(])|([ \t\n;]goto[ \t\n])", REG_NOSUB | REG_EXTENDED );
    if ( reti )
      error( "Eroare compilare regex while.\n", 0 );
    reti = regexec(&regwhile, linie, 0, NULL, 0);
    if( !reti )
      error(erori[BUCLE], 0);
    else if( reti != REG_NOMATCH )
      error("Executie esuata regex while", 0);

    // foloseste decizii?
    reti = regcomp(&regif, "([ \t\n;]if[ \t\n\(])|(\\?)", REG_NOSUB | REG_EXTENDED );
    if ( reti )
      error( "Eroare compilare regex if.\n", 0 );
    reti = regexec(&regif, linie, 0, NULL, 0);
    if( !reti )
      error(erori[DECIZII], 0);
    else if( reti != REG_NOMATCH )
      error("Executie esuata regex if", 0);

    // foloseste decizii mascate?
    reti = regcomp(&regifmasc, "([ \t\n=]min[ \t\n]*\\()|([ \t\n=]max[ \t\n]*\\()|([ \t\n=]abs[ \t\n]*\\()|([<>!=]=)", REG_NOSUB | REG_EXTENDED );
    if ( reti )
      error( "Eroare compilare regex if mascat.\n", 0 );
    reti = regexec(&regifmasc, linie, 0, NULL, 0);
    if( !reti )
      error(erori[DECIZII_MASCATE], 0);
    else if( reti != REG_NOMATCH )
      error("Executie esuata regex if mascat", 0);
    */

    int punctaj = 0, n, m, cerinta, k;
    char msg[1000] = { 0 };
    fin = fopen( "datorii.in", "r" );
    if( !fin )
        error("Fisier intrare lipsa", 0);
    fscanf( fin, "%d%d", &cerinta, &n );
    fclose( fin );

    if ( cerinta == 1 && n == 4 )
      error( "Pomana (pentru ca un scor de 0p nu arata asa bine ca un scor de 10p)", 10 );

    switch ( graderDiff( "datorii.out", "datorii.ok", 1000000 ) ) {
    case 0:
        bun(5);
        break;
    case 1:
        /*
        // punctaje partiale daca este cazul
        if ( lcorecta[0] == 0 )
          punctaj += 3;
        if ( lcorecta[1] == 0 )
          punctaj += 3;
        if ( lcorecta[2] == 0 )
          punctaj += 4;
        sprintf( msg, "a) %s;   b) %s;   c) %s",
                 erori[lcorecta[0]], erori[lcorecta[1]], erori[lcorecta[2]] );
        error( msg, punctaj );
        */
        error( "Incorect", 0 );
        break;
    case 2:
        error("Fisier iesire lipsa", 0);
        break;
    case 3:
        error("Fisier intern .ok lipsa", 0);
        break;
    default:
        error("Eroare necunoscuta de diff", 0);
    }
    return 0;
}

