#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

uint8_t shellcode[] = {0x55, // push %rbp
		       0x48, 0x89, 0xe5, // mov %rsp, %rbp
		       0xb8, 0x2a, 0x00, 0x00, 0x00, // mov $0x2a, %eax
		       0x5d, // pop %rbp
		       0xc3}; // retq

/* shellcode was obtained by compiling foo and extracting the
   generated instruction (see objdump -d )

   int foo() { return 42; }
*/

int main() {
  char cmd[1024];
  sprintf(cmd, "cat /proc/%d/maps", getpid());
  system(cmd);
  printf("\n");
  int* addr;
  printf("entrez une addresse\n");
  scanf("%p", &addr);

  printf("Accès en lecture:\n");
  printf("\t*addr = %d\n", *addr);

  printf("Accès en écriture:\n");
  memcpy(addr, shellcode, sizeof(shellcode));
  printf("\t OK\n");

  int (*function)() = (int (*)())addr;
  printf("Accès en exécution:\n");
  int n = function();
  printf("\tOK: foo returned %d\n", n);
	 
  return 0;
}
