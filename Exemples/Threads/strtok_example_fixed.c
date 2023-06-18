#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void extract_path() {
  char* string = getenv("PATH");
  char* saveptr = NULL;
  printf("Parsing '%s'\n", string);

  
  for(char* token = strtok_r(string, ":", &saveptr) ;
      token ;
      token = strtok_r(NULL, ":", &saveptr) ){
    printf("\t %s contains: ", token);

    char* saveptr_word = NULL;
    for(char* word = strtok_r(token, "/ ", &saveptr_word) ;
	word ;
	word = strtok_r(NULL, "/", &saveptr_word) ){
      printf("%s ", word);
    }
    printf("\n");
  }
}

int main(int argc, char**argv) {
  extract_path();
  return 0;
}
