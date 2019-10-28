/*******************************************************************
 * Copyright (c) 2019 Zuoyebang.com, Inc. All Rights Reserved
 * 
 * @file sort.cpp
 * @author yujitai
 * @date 2019/10/20 15:13:16
 ******************************************************************/

#include <iostream>
#include <algorithm>

// 选择最小的值依次放在第1 2 3...个位置
void SelectionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        // 寻找[i, n)区间里的最小值
        int min_index = i;
        for (int j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_index]) 
                min_index = j;
        std::swap(arr[i], arr[min_index]);
    }
}

#if 0
void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        // 寻找元素arr[i]合适的插入位置
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1])
                std::swap(arr[j], arr[j-1]);
            else 
                break;
        }
    }
}

void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        // 寻找元素arr[i]合适的插入位置
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) 
            std::swap(arr[j], arr[j-1]);
    }
}
#endif

void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        // 寻找元素arr[i]合适的插入位置
        int e = arr[i];
        int j; // 保存元素e应该插入的位置
        for (j = i; j > 0 && e < arr[j-1]; j--) 
            arr[j] = arr[j-1];
        arr[j] = e;
    }
}

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
void __merge(int arr[], int l, int mid, int r) {
    int aux[r-l+1];
    for(int i = l; i <= r; i++)
        aux[i-l] = arr[i];

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = aux[j -l];
            j++;
        } else if (j > r) {
            arr[k] = aux[i -l];
            i++;
        } else if (aux[i -l] < aux[j - l]) {
            arr[k] = aux[i -l];
            i++;
        } else {
            arr[k] = aux[j -l];
            j++;
        }
    }
}

#if 0
// 递归使用归并排序, 对arr[l...r]的范围进行排序
void __mergeSort(int arr[], int l, int r) {
    if (l >= r) 
        return;

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    __merge(arr, l, mid, r);
}

void __mergeSort(int arr[], int l, int r) {
    if (l >= r) 
        return;

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    // 优化1(对于近乎有序的数组)
    if (arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}
#endif

// 对arr[l...r]范围的数组进行插入排序
template<typename T>
void InsertionSort(T arr[], int l, int r){

    for( int i = l+1 ; i <= r ; i ++ ) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j-1] > e; j--)
            arr[j] = arr[j-1];
        arr[j] = e;
    }

    return;
}

void __mergeSort(int arr[], int l, int r) {
    // 优化2
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    // 优化(对于近乎有序的数组)
    if (arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}

void MergeSort(int arr[], int n) {
    __mergeSort(arr, 0, n-1);
}

# if 0
// 要进行数组越界检查
void MergeSortBU(int arr[], int n) {
    for (int sz = 1; sz <= n; sz += sz)
        for (int i = 0; i + sz < n; i += sz + sz)
            // 对arr[i...i+sz-1]和arr[i+sz...i+2*sz-1]进行归并
            __merge(arr, i, i+sz-1, std::min(i+sz+sz-1, n-1));
}
#endif

void MergeSortBU(int arr[], int n) {
    for (int sz = 1; sz <= n; sz += sz)
        for (int i = 0; i < n; i += sz + sz)
            // 对arr[i...i+sz-1]和arr[i+sz...i+2*sz-1]进行归并
            __merge(arr, i, i+sz-1, i+sz+sz-1);
}

// 对arr[l..r]部分进行partition操作
// 返回p,使得arr[l...p-1]<arr[p];arr[p+1...r]>arr[p]
int __partition(int arr[], int l, int r) {
    // 优化2
    std::swap(arr[l], arr[rand()%(r-l+1)+l]);

    int v = arr[l];

    // arr[l+1...j]<v; arr[j+1...i)>v
    int j = l;
    for(int i = l + 1; i <= r; i++) {
        if (arr[i] < v) {
            std::swap(arr[j+1], arr[i]);
            // swap(arr[++j], arr[i]);
            j++;
        }
    }

    std::swap(arr[l], arr[j]);

    return j;
}

// 优化3
int __partition2(int arr[], int l, int r) {
    std::swap(arr[l], arr[rand()%(r-l+1)+l]);
    int v = arr[l];

    // arr[l+1...i] <= v; arr[j...r]>=v
    int i = l+1, j = r;
    while (true) {
        while (i <= r && arr[i] < v) i++;
        while (j >= l+1 && arr[j] > v) j--;
        if (i > j) break;
        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }

    std::swap(arr[l], arr[j]);
    return j;
}


// 对arr[l..r]部分进行快速排序
void __quickSort(int arr[], int l, int r) {

    //if (l >= r) 
    //    return;
    // 优化1
    if (r -l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    //int p = __partition(arr, l, r);
    int p = __partition2(arr, l, r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);
}

// 三路快速排序处理arr[l...r]
// 将arr[l...r]分为 <v;==v;>v 三部分
// 之后递归对<v;>v两部分继续进行三路快速排序
void __quickSort3Ways(int arr[], int l, int r) {

    if (r -l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    // partition
    std::swap(arr[l], arr[rand()%(r-l+1)+l]);
    int v = arr[l];

    // 满足我们定义的性质,初始时数组都是空的,保证逻辑有一个正确的开始
    int lt = l; // arr[l+1...lt] < v
    int gt = r+1; // arr[gt...r] > v
    int i =l + 1; // arr[lt+1...i) == v

    while(i < gt) {
        if (arr[i] < v) {
            std::swap(arr[i], arr[lt+1]);
            lt++;
            i++;
        } else if (arr[i] > v) {
            std::swap(arr[i], arr[gt-1]);
            gt--;
        } else { // arr[i] == v
            i++;
        }
    }
    std::swap(arr[l], arr[lt]);

    __quickSort3Ways(arr, l, lt-1);
    __quickSort3Ways(arr, gt, r);
}

void QuickSort(int arr[], int n) {
    srand(time(NULL));

    //__quickSort(arr, 0, n-1);
    __quickSort3Ways(arr, 0, n-1);
}

int main() {

    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // SelectionSort(a, 10);
    // InsertionSort(a, 10);
    // MergeSort(a, 10);
    // MergeSortBU(a, 10);
    QuickSort(a, 10);

    for( int i = 0 ; i < 10 ; i ++ )
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;

    return 0;
}

