// Created by yujtiai

#include <iostream>
using namespace std;

template<typename T>
class MaxHeap {
public:
	MaxHeap(int capacity) {
		_capacity = capacity;
		_data = new T[capacity+1];
		_size = 0;
	}

	// Heapify
	MaxHeap(T arr[], int n) {
		_capacity = n;
		_data = new T[n+1];

		for (int i = 0; i < n; i++)
			_data[i+1] = arr[i];
		_size = n;

		for (int i = _size/2; i >=1; i-- )
			shift_down(i);
	}

	~MaxHeap() {
		delete[] _data;
	}

	int size() {
		return _size;
	}

	bool is_empty() {
		return _size == 0;
	}

	void insert(T item) {
		assert(_size + 1 <= _capacity);
		_data[_size+1] = item;
		shift_up(_size+1);
		_size++;
	}

	T extract_max() {
		assert(_size > 0);
		T max = _data[1];
		
		swap(_data[1], _data[_size]);
		_size--;
		shift_down(1);

		return max;
	}

	T get_max() {
		assert(_size > 0);
		return _data[1];
	}

private:
	void shift_up(int i) {
		while (i > 1 && _data[i] > _data[i/2]) {
			swap(_data[i], _data[i/2]);
			i /= 2;
		}
	}

	void shift_down(int i) {
		// 左孩子存在
		while (2*i <= _size) {
			int j = 2*i;
			// 右孩子存在且大于左孩子
			if (j+1 <= _size && _data[j+1] > _data[j])
				j++;

			if (_data[i] >= _data[j])
				break;
	
			swap(_data[i], _data[j]);
			i = j;
		}
	}

	T*  _data;
	int _size;
	int _capacity;
};


template<typename T>
void heap_sort2(T arr[], int n){

    MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    for( int i = n-1 ; i >= 0 ; i-- )
        arr[i] = maxheap.extract_max();

}


template<typename T>
void heap_sort1(T arr[], int n){

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for( int i = 0 ; i < n ; i ++ )
        maxheap.insert(arr[i]);

    for( int i = n-1 ; i >= 0 ; i-- )
        arr[i] = maxheap.extract_max();

}

template<typename T>
void __shift_down(T arr[], int n, int i) {
	// 左孩子存在
	while (2*i+1 < n) {
		int j = 2*i+1;
		// 右孩子存在且大于左孩子
		if (j+1 < n && arr[j+1] > arr[j])
				j++;

		if (arr[i] >= arr[j])
				break;

		swap(arr[i], arr[j]);
		i = j;
	}
}

template<typename T>
void heap_sort(T arr[], int n) {
	for (int i = (n-1)/2; i >= 0; i--)
		__shift_down(arr, n, i);

	for (int i = n-1; i > 0; i--) {
		swap(arr[0], arr[i]);
		__shift_down(arr, i, 0);
	}
}

int main() {
	MaxHeap<int> maxheap = MaxHeap<int>(100);

    srand(time(NULL));
    for( int i = 0 ; i < 10 ; i ++ ){
        maxheap.insert( rand()%100 );
    }

	cout << "maxheap size: " << maxheap.size() << endl;
	cout << "max: " << maxheap.get_max() << endl;

    while( !maxheap.is_empty() )
        cout<<maxheap.extract_max()<<" ";
    cout<<endl;
	cout << "maxheap size: " << maxheap.size() << endl;

	int arr[10] = {10, 9, 7, 8, 1, 3, 2, 6, 5, 4};
	// heap_sort1(arr, 10);
	// heap_sort2(arr, 10);
	heap_sort(arr, 10);
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	cout << endl;

	return 0;
}
