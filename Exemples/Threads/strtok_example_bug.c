#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void extract_path() {
  char* string = getenv("PATH");
  printf("Parsing '%s'\n", string);
  // string should contain a list of directories separated with :
  // eg. /usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
  
  // Extract the directories
  // eg. /usr/local/bin, /usr/bin, /bin, /usr/local/games, /usr/games
  for(char* token = strtok(string, ":") ;
      token ;
      token = strtok(NULL, ":") ){
    // token contains a directory (eg. /usr/local/bin)
    printf("\t %s contains: ", token);
    
    // Extract the subdirectories
    // eg. usr, local, bin
    for(char* word = strtok(token, "/ ") ;
	word ;
	word = strtok(NULL, "/") ){
      printf("%s ", word);
    }
    printf("\n");
  }
}

int main(int argc, char**argv) {
  extract_path();
  return 0;
}
