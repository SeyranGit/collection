#include <stdio.h>


typedef unsigned int ui32;


static void swap(int *array, ui32 i1, ui32 i2) {
  int temp = *(array + i1);
  *(array + i1) = *(array + i2);
  *(array + i2) = temp;
}


static void selection_sort(int *array, ui32 len) {
  ui32 smallest;
  for (ui32 i = 0; i < len - 1; i++) {
    smallest = i;
    for (ui32 j = i + 1; j < len; j++) {
      if (array[j] < array[smallest]) {
        smallest = j;
      }
    }
    if (smallest != i) {
      swap(array, i, smallest);
    }
  }
}


static void print_array(int *array, ui32 len) {
  for (ui32 i = 0; i < len; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}


int main(void) {
  int array[5] = { 3, 1, 2, 5, 4 };
  print_array(array, 5);
  selection_sort(array, 5);
  print_array(array, 5);
  return 0;
}
