#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct plop {
  int a;
  char b;
  int c;
};

struct plop_packed {
  int a;
  char b;
  int c;
} __attribute__((packed));


int main(void) {

  struct plop p1;
  struct plop_packed p2;
  printf("struct plop -- size: %lu bytes, address: %p\n",
	 sizeof(struct plop), &p1);
  printf("\t.a -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p1.a), &p1.a, offsetof(struct plop, a));
  printf("\t.b -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p1.b), &p1.b, offsetof(struct plop, b));
  printf("\t.c -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p1.c), &p1.c, offsetof(struct plop, c));
  printf("\n");

  printf("struct plop_packed -- size: %lu bytes, address: %p\n",
	 sizeof(struct plop_packed), &p2);
  printf("\t.a -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p2.a), &p2.a, offsetof(struct plop_packed, a));
  printf("\t.b -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p2.b), &p2.b, offsetof(struct plop_packed, b));
  printf("\t.c -- size: %lu bytes, address: %p, offset: %lu\n",
	 sizeof(p2.c), &p2.c, offsetof(struct plop_packed, c));
  printf("\n");
  return 0;
}
