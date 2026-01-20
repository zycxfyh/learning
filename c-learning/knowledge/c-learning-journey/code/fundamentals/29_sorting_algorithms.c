#include <stdio.h>
#include <stdlib.h>

// 函数声明
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void print_array(int arr[], int n);
void swap(int* a, int* b);

int main() {
    printf("=== C语言排序算法演示 ===\n\n");

    // 测试数据
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    int arr4[] = {64, 34, 25, 12, 22, 11, 90};
    int arr5[] = {64, 34, 25, 12, 22, 11, 90};

    int n = sizeof(arr1) / sizeof(arr1[0]);

    printf("原始数组: ");
    print_array(arr1, n);

    // 冒泡排序
    printf("\n1. 冒泡排序 (Bubble Sort):\n");
    bubble_sort(arr1, n);
    print_array(arr1, n);

    // 选择排序
    printf("\n2. 选择排序 (Selection Sort):\n");
    selection_sort(arr2, n);
    print_array(arr2, n);

    // 插入排序
    printf("\n3. 插入排序 (Insertion Sort):\n");
    insertion_sort(arr3, n);
    print_array(arr3, n);

    // 快速排序
    printf("\n4. 快速排序 (Quick Sort):\n");
    quick_sort(arr4, 0, n-1);
    print_array(arr4, n);

    // 归并排序
    printf("\n5. 归并排序 (Merge Sort):\n");
    merge_sort(arr5, 0, n-1);
    print_array(arr5, n);

    return 0;
}

// 冒泡排序 - O(n²)
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// 选择排序 - O(n²)
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

// 插入排序 - O(n²)
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 快速排序 - O(n log n)
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 归并排序 - O(n log n)
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// 辅助函数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}