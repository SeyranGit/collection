int printf(char const* const _Format, ...);


typedef char i8;
static i8 heap[1];


static void *malloc(unsigned long long size) {
  printf("%zu\n", sizeof(heap));
  printf("%zu\n", size);
  return &heap[0];
}


int main(void) {
  typedef struct test {
		int a;
		int b;
		int c;
		int d;
		int a1;
		int b1;
		int c1;
		int d1;
		int a2;
		int b2;
		int c2;
		int d2;
		int _a;
		int _b;
		int _c;
		int _d;
		int _a1;
		int _b1;
		int _c1;
		int _d1;
		int _a2;
		int _b2;
		int _c2;
		int _d2;
	} TestStruct;

  /* Как это работает? */
  TestStruct *foo = malloc(sizeof(TestStruct)); /* (void*)&heap[0]; */
  foo->a = 1000000;
  foo->b = 1000000;
  foo->c = 1000000;
  foo->d = 1000000;
	foo->a1 = 1000000;
  foo->b1 = 1000000;
	foo->c1 = 1000000;
	foo->d1 = 1000000;
	foo->a2 = 1000000;
	foo->b2 = 1000000;
	foo->c2 = 1000000;
	foo->d2 = 1000000;
  foo->_a = 1000000;
  foo->_b = 1000000;
  foo->_c = 1000000;
  foo->_d = 1000000;
  foo->_a1 = 1000000;
  foo->_b1 = 1000000;
  foo->_c1 = 1000000;
  foo->_d1 = 1000000;
  foo->_a2 = 1000000;
  foo->_b2 = 1000000;
  foo->_c2 = 1000000;
  foo->_d2 = 1000000;

  printf("%d\n", foo->a);
  printf("%d\n", foo->b);
  printf("%d\n", foo->c);
  printf("%d\n", foo->d);
  printf("%d\n", foo->a1);
  printf("%d\n", foo->b1);
  printf("%d\n", foo->c1);
  printf("%d\n", foo->d1);
  printf("%d\n", foo->a2);
  printf("%d\n", foo->b2);
  printf("%d\n", foo->c2);
  printf("%d\n", foo->d2);
  printf("%d\n", foo->_a);
  printf("%d\n", foo->_b);
  printf("%d\n", foo->_c);
  printf("%d\n", foo->_d);
  printf("%d\n", foo->_a1);
  printf("%d\n", foo->_b1);
  printf("%d\n", foo->_c1);
  printf("%d\n", foo->_d1);
  printf("%d\n", foo->_a2);
  printf("%d\n", foo->_b2);
  printf("%d\n", foo->_c2);
  printf("%d\n", foo->_d2);
  return 0;
}
