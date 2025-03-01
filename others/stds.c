#include <stdio.h>
#include <stddef.h>


struct obj {
  char a:8;
  int b:32; /* bits */
};


[[deprecated]]
int add(int one, ...) {
  return one + 10;
}

 
int main(void) {
  static_assert(1, "Hello");

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
  static nullptr_t name = nullptr;
#endif

  struct obj o;
  o.a = 'A';
  o.b = 10; 
  printf("%c, %d\n", o.a, o.b);
  printf("%lld\n", sizeof(struct obj));

  return 0;
}
