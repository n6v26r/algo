#include <stdio.h>
#include <string.h>

char s[3];

int main(){
  int n;
  scanf("%d\n", &n);
  while(n>0){
    s[0] = fgetc(stdin);
    s[1] = fgetc(stdin);
    s[2] = fgetc(stdin);
    if(!strcmp(s, "abc") || !strcmp(s, "acb") || !strcmp(s, "bac") || !strcmp(s, "cba")) printf("YES\n");
    else printf("NO\n");
    fgetc(stdin);
    n--;
  }
    return 0;
}
