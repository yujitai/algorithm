/*******************************************************************
 * Copyright (c) 2019 Zuoyebang.com, Inc. All Rights Reserved
 * 
 * @file heap.cpp
 * @author yujitai
 * @date 2019/10/28 19:15:48
 ******************************************************************/

#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
class MaxHeap {
public:
    MaxHeap(int capacity) {
        data = new T[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }

    MaxHeap(T arr[], int n) {
        data = new T[n + 1];
        capacity = n;
        for (int i = 0; i < n; i++)
            data[i + 1] = arr[i];
        count = n;

        for (int i = count/2; i >= 1; i--)
            ShiftDown(i);
    }

    ~MaxHeap() {
        delete[] data;
    }

    int Size() {
        return count;
    }

    bool Empty() {
        return count == 0;
    }

    void Insert(T item) {
        // TODO:容量不足,开辟新的空间
        assert(count+1 <= capacity);

        data[count + 1] = item;
        count++;
        ShiftUp(count);
    }

    T ExtractMax() {
        assert(count > 0);

        T ret = data[1];

        swap(data[1], data[count]);
        count--;
        ShiftDown(1);

        return ret;
    }

private:
    void ShiftUp(int k) {
        // 有索引一定要考虑数组越界
        while(k > 1 && data[k/2] < data[k]) {
            std::swap(data[k/2], data[k]);
            k /= 2;
        }
    }

    void ShiftDown(int k) {
        while (2 * k <= count) {
            int j = 2*k; // 在此轮循环中, data[k]和data[j]交换位置
            if (j+1 <= count && data[j+1] > data[j]) 
                j += 1;
            if (data[k] >= data[j]) 
                break;

            std::swap(data[k], data[j]);
            k = j;
        }
    }

    T* data;
    int count;
    int capacity;
};

void HeapSort(int arr[], int n) {
    MaxHeap<int> maxheap = MaxHeap<int>(n);

    for (int i = 0; i < n; i++) 
        maxheap.Insert(arr[i]);
    for (int i = n - 1 ; i >= 0; i--) 
        maxheap.ExtractMax();
}


int main() {
    MaxHeap<int> maxheap = MaxHeap<int>(100);
    // cout << maxheap.Size() << endl;

    srand(time(NULL));
    for (int i = 0; i < 15; i++)
        maxheap.Insert(rand() % 100);
    for (int i = 0; i < 15; i++)
        cout << maxheap.ExtractMax() << " ";
    cout << endl;


    return 0;
}












