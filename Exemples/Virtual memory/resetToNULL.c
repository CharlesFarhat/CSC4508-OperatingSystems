/**********************/
/* resetToNULL.c */
/**********************/

/* This program illustrates the value of assigning a variable to NULL
   which contains a pointer to an unallocated buffer.
   Indeed, it makes a segmentation fault, which makes it possible to
   identify that we have executed an illegal operation. Using a
   debugger allows to understand the problem.
*/
/*                                                                    */
/* 1) Compile the program with the option -g                          */
/*    cc -g -o resetToNULL resetToNULL.c                              */
/* 2) ./resetToNULL                                                   */
/*    ==> Segmentation fault                                          */
/* 3) ulimit -c unlimited                                             */
/* 4) ./resetToNULL                                                   */
/*    ==> Segmentation fault (core dumped)                            */
/* 5) ddd ./resetToNULL core                                          */

#include <stdlib.h>
#include <assert.h>

void h(char *p){
  *p = 'a';
}

void g(char *p){
  h(p);
}

void f(char *p){
  g(p);
}

int main(){
  char *p = NULL;

  f(p);

  p = malloc(1);
  assert(p != NULL);

  f(p);

  free(p);
  p = NULL;

  f(p);

  return EXIT_SUCCESS;
}
