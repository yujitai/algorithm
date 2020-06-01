//
// Created by yujitai on 20200601
//
#include <iostream>
using namespace std;

template<typename T>
void insertion_sort(T arr[], int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--)	{
			if (arr[j] < arr[j-1]) {
				swap(arr[j], arr[j-1]);
			} else {
				break;
			}
		}
	}
}

template<typename T>
void insertion_sort2(T arr[], int n) {
	for (int i = 1; i < n; i++) 
		for (int j = i; j > 0 && arr[j] < arr[j-1]; j--)	
			swap(arr[j], arr[j-1]);
}

template<typename T>
void selection_sort(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		int min_index = i;
		for (int j = i+1; j < n; j++)
			if (arr[j] < arr[min_index])
				min_index = j;

		swap(arr[i], arr[min_index]);
	}
}

template<typename T>
void bubble_sort(T arr[], int n) {
	for (int i = 0; i < n-1; i++) 
		for (int j = 1; j < n - i; j++)
			if (arr[j] < arr[j-1])
				swap(arr[j], arr[j-1]);
}

int main() {
	int arr[10] = {5, 3, 2, 1, 6, 9, 8, 7, 4, 10};
	// insertion_sort2(arr, 10);
	// selection_sort(arr, 10);
	bubble_sort(arr, 10);
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	cout << endl;

	return 0;
}
