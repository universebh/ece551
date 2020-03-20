//Code starts

#include <stdio.h>
#include <stdlib.h>

struct array_tag {
  int * array;
  size_t size;
  size_t max_seq;
};
typedef struct array_tag array_t;

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t ans) {
  if (maxSeq(array, n) != ans) {
    printf("It failed when the test case was:\n");
    printf("array = {");
    for (size_t i = 0; i < n; i++) {
      printf("%d", array[i]);
      if (i < n - 1) {
        printf(", ");
      }
    }
    printf("}\n");
    printf("max_sequence = %zu\n", ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array2[] = {-5, -9, -10, -12, 9, 1, 3, 6, 7, 10};
  int array3[] = {0};
  int * array4 = NULL;
  int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int array6[] = {1, 1, 2, 8, 8, 8, 9, 10, 11, 15};
  int array7[] = {0xFFFFFFFF, 1, 2, 3};
  array_t test_array1 = {array1, 10, 4};
  array_t test_array2 = {array2, 10, 5};
  array_t test_array3 = {array3, 1, 1};
  array_t test_array4 = {array4, 0, 0};
  array_t test_array5 = {array5, 10, 1};
  array_t test_array6 = {array6, 10, 5};
  array_t test_array7 = {array7, 4, 4};
  run_check(test_array1.array, test_array1.size, test_array1.max_seq);
  run_check(test_array2.array, test_array2.size, test_array2.max_seq);
  run_check(test_array3.array, test_array3.size, test_array3.max_seq);
  run_check(test_array4.array, test_array4.size, test_array4.max_seq);
  run_check(test_array5.array, test_array5.size, test_array5.max_seq);
  run_check(test_array6.array, test_array6.size, test_array6.max_seq);
  run_check(test_array7.array, test_array7.size, test_array7.max_seq);

  return EXIT_SUCCESS;
}

//Code ends
