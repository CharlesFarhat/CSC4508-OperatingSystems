#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void extract_path() {
  char* string = getenv("PATH");
  printf("Parsing '%s'\n", string);

  
  for(char* token = strtok(string, ":") ;
      token ;
      token = strtok(NULL, ":") ){
    printf("\t %s\n", token);
  }
}

int main(int argc, char**argv) {
  extract_path();
  return 0;
}
