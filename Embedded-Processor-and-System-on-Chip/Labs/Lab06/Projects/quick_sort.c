#include <stdio.h>

void Swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int Partition(int* arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (arr[j] < pivot) {
      ++i;
      Swap(&arr[i], &arr[j]);
    }
  }
  
  Swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void QuickSort(int* arr, int low, int high) {
  if (low < high) {
    int pi = Partition(arr, low, high);
    QuickSort(arr, low, pi - 1);
    QuickSort(arr, pi + 1, high);
  }
}

void PrintArray(const int* arr, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  int data[] = {8, 7, 2, 1, 0, 9, 6};
  int size = sizeof(data) / sizeof(data[0]);

  printf("Unsorted: ");
  PrintArray(data, size);

  if (size > 0) {
    QuickSort(data, 0, size - 1);
  }

  printf("Sorted:   ");
  PrintArray(data, size);

  return 0;
}
