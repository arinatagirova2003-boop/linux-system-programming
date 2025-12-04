#include "sort.h"

void bubbleSort(int* array, int size, bool order) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            bool cond = order ? (array[j] > array[j + 1]) : (array[j] < array[j + 1]);
            if (cond) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}
