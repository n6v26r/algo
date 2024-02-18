/*
 ██████╗██████╗       ███████╗██╗   ██╗ █████╗ ██╗     
██╔════╝██╔══██╗      ██╔════╝██║   ██║██╔══██╗██║     
██║     ██████╔╝█████╗█████╗  ██║   ██║███████║██║     
██║     ██╔═══╝ ╚════╝██╔══╝  ╚██╗ ██╔╝██╔══██║██║     
╚██████╗██║           ███████╗ ╚████╔╝ ██║  ██║███████╗
 ╚═════╝╚═╝           ╚══════╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝
*/

#include <errno.h>
# define OK "✓\0"
# define NOPE "✗\0"
# define SUCCESS_MESSAGE "\e[0;32m✓ Success!\0"
# define INCORRECT_MESSAGE "\e[0;31m✗ Incorrent!\0"
# define TLE_MESSAGE "\e[0;31m⧖ Time limit Exceded!\0"
# define MLE_MESSAGE "\e[0;31m~ Memory limit Exceded!\0"
# define NOFILE_MESSAGE "\033[0mNo file found! Skipping...\0"

#define MSG "%s (T:%f/%f M:%d/%d %s)\n"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

char buf[1000000];

bool verbose=false;
char* input="\0";
char* output="\0";
char* program="\0";
char* testsF="\0";
char* inputExt=".in\0";
char* outputExt=".out\0";
char* okExt=".ok\0";

char* testNamePrefix="\0";

int memoryLimit=INT_MAX;
int testCount=100;
float timeLimit=10000;

void printHelp(){
  printf("\
 Description: Evaluates a CP program against a series of inputs.\n\
 Use: [OPTIONS] ProgramPath TestsFolderPath\n\
\n\
 OPTIONAL:\
   -ie= --iext=       Input extension (default is .in)\n\
   -oe= --oext=       Output extension (default is .out)\n\
   -ok= --okay=       Test ok file extension (default is .ok)\n\
   -c= --count=       How many tests to run?\n\
   -t= --time=        Set a time limit (in seconds) for each test. Default is 10000\n\
   -m= --memory=      Set a memory limit (in kb) Default in 2**31-1\n\
   -v  --verbose      Show verbose information\n\
   -p= --prefix=      Testname prefix (tests are numbered 0 - x or 1 - x by default)\n\
   -h  --help         Print this message\n\
");
}

bool _strcmp(const char* a, const char* b){
  int i;
  for(i=0; a[i]!='\0'; i++){
    if(a[i]!=b[i])
      break;
  }
  return a[i-1]!='=';
}

char* GetValStart(char* arg){
  for(int i=0; arg[i]!='\0'; i++){
    if(arg[i]=='=')
      return arg+i+1;
  }
  return NULL;
}

void matchArg(int argc, char** argv){
  for(int i=1; i<argc; i++){
    if(strcmp(argv[i], "-h")==0 || strcmp(argv[i], "--help")==0){printHelp(); exit(0);}
    else if(strcmp(argv[i], "-v")==0 || strcmp(argv[i], "--verbose")==0){verbose=true;}
    else if(strcmp(argv[i], "-i")==0 || strcmp(argv[i], "--input")==0){input=GetValStart(argv[i]);}
    else if(strcmp(argv[i], "-o")==0 || strcmp(argv[i], "--output")==0){output=GetValStart(argv[i]);}
    else if(_strcmp(argv[i], "-t=")==0 || _strcmp(argv[i], "--time=")==0){timeLimit=strtof(GetValStart(argv[i]), NULL);}
    else if(_strcmp(argv[i], "-m=")==0 || _strcmp(argv[i], "--memory=")==0){memoryLimit=strtol(GetValStart(argv[i]), NULL, 10);}
    else if(_strcmp(argv[i], "-c=")==0 || _strcmp(argv[i], "--count=")==0){testCount=strtol(GetValStart(argv[i]), NULL, 10);}
    else if(_strcmp(argv[i], "-p=")==0 || _strcmp(argv[i], "--prefix=")==0){testNamePrefix=GetValStart(argv[i]);}
    else if(_strcmp(argv[i], "-ie=")==0 || _strcmp(argv[i], "--iext=")==0){inputExt=GetValStart(argv[i]);}
    else if(_strcmp(argv[i], "-oe=")==0 || _strcmp(argv[i], "--oext=")==0){outputExt=GetValStart(argv[i]);}
    else if(_strcmp(argv[i], "-ok=")==0 || _strcmp(argv[i], "--okay=")==0){okExt=GetValStart(argv[i]);}

    else if (i==argc-2){program = argv[i];}
    else if(i==argc-1){testsF=argv[i];}
    else {printf("Unkown argument: %s\n", argv[i]); printHelp(); exit(0);}
  }
}

bool openTestIn(FILE **f, int testIndex){
  *f = NULL;
  char testName[1000] = "";
  char testNumber[10]="";
  sprintf(testNumber, "%d", testIndex);
  strcat(testName, testsF);
  strcat(testName, testNamePrefix);
  strcat(testName, testNumber);
  strcat(testName, inputExt);
  *f = fopen(testName, "r");
  if(verbose)
    printf("Attempting to open file: %s\n", testName);
  if(*f == NULL){printf("%s (%s)\n", NOFILE_MESSAGE, testName); return false;}
  return true;
}

bool openTestOk(FILE **f, int testIndex){
  *f = NULL;
  char testName[1000] = "";
  char testNumber[10]="";
  sprintf(testNumber, "%d", testIndex);
  strcat(testName, testsF);
  strcat(testName, testNamePrefix);
  strcat(testName, testNumber);
  strcat(testName, okExt);
  *f = fopen(testName, "r");
  if(verbose)
    printf("Attempting to open file: %s\n", testName);
  if(*f == NULL){printf("%s (%s)\n", NOFILE_MESSAGE, testName); return false;}
  return true;
}

bool openFileIn(FILE **f){
  *f = NULL;
  char fileName[1000] = "";
  strcat(fileName, program);
  strcat(fileName, inputExt);
  *f = fopen(fileName, "w");
  if(verbose)
    printf("Attempting to open file: %s\n", fileName);
  if(*f == NULL){printf("%s (%s)\n", NOFILE_MESSAGE, fileName); return false;}
  return true;
}

bool openFileOut(FILE **f){
  *f = NULL;
  char fileName[1000] = "";
  strcat(fileName, program);
  strcat(fileName, outputExt);
  *f = fopen(fileName, "r");
  if(verbose)
    printf("Attempting to open file: %s\n", fileName);
  if(*f == NULL){printf("%s (%s)\n", NOFILE_MESSAGE, fileName); return false;}
  return true;
}

int main(int argc, char** argv){
  if(argc<2){
    printf("Not enougth arguments!\n");
    printHelp();
    return 0;
  }
  matchArg(argc, argv);

  FILE *tin, *tok, *fin, *fout;
  for(int i=0; i<testCount; i++){
    printf("\033[0m%d. ", i);
    if(!openTestIn(&tin, i)){continue;}
    if(!openTestOk(&tok, i)){continue;}
    if(!openFileIn(&fin)){continue;}
    
    if(verbose) printf("All files opened!\n");

    {
      // Copy content from tin to fin
      char c = fgetc(tin);
      while (c!=EOF){
        fputc(c, fin);
        c=fgetc(tin);
      }
      fputc(EOF, fin);
    }
    
    fclose(fin); // flush file
    if(verbose) printf("Copied test input into program input file!\n");
    // Execute programTime
    //
    if(verbose) printf("Running the program to check time usage\n");
    double programTime;
    { // get memory usage
      char exec[10000] = "";
      strcat(exec, "bash -c \"/usr/bin/time -v ");
      strcat(exec, program);
      strcat(exec, " |& grep \\\"System time (seconds):\\\" | awk \'{print \\$NF}\'\"");
      FILE *fp = popen(exec,"r");
      if(fp == NULL){printf("Could not read memory usage!\n");}
      else{
        fscanf(fp, "%lf", &programTime); 
      }
      pclose(fp);
    }


    if(verbose) printf("First execution complete! Running the program again to check mem usage\n");
    int memoryUsage;
    { // get memory usage
      char exec[10000] = "";
      strcat(exec, "bash -c \"/usr/bin/time -v ");
      strcat(exec, program);
      strcat(exec, " |& grep \\\"Maximum resident set size (kbytes):\\\" | awk \'{print \\$NF}\'\"");
      FILE *fp = popen(exec,"r");
      if(fp == NULL){printf("Could not read memory usage!\n");}
      else{
        fscanf(fp, "%d", &memoryUsage); 
      }
      pclose(fp);
    }

    if(verbose) printf("Executed program!\n");
    
    // open fout
    if(!openFileOut(&fout)){continue;} 
    char cout = fgetc(fout);
    char cok = fgetc(tok);
    while(cok!=EOF){
      if(cout!=cok){
        if(cok=='\n' && cout==' '){ // allows a space before newline
          cout = fgetc(fout);
          if(cout == '\n'){
            cout = fgetc(fout);
            cok = fgetc(tok);
          }
          break;
        }
        break;
      }
      cout = fgetc(fout);
      cok = fgetc(tok);
    }
    fclose(tok);
    fclose(fout);
    if(cok == EOF && (cout==EOF || (cout == '\n' && fgetc(fout)==EOF))){
      if(programTime<timeLimit && memoryUsage<memoryLimit)
        printf(MSG, SUCCESS_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, OK);
      else if(programTime<timeLimit)
        printf(MSG, MLE_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, OK);
      else
       printf(MSG, TLE_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, OK);
    } else {
      if(programTime<timeLimit && memoryUsage<memoryLimit)
        printf(MSG, INCORRECT_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, NOPE);
      else if(programTime<timeLimit)
        printf(MSG, MLE_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, NOPE);
      else
       printf(MSG, TLE_MESSAGE, programTime, timeLimit, memoryUsage, memoryLimit, NOPE);
    }    
    fclose(tin);
  }
  return 0;
}

