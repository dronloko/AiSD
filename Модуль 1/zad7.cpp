// Copyright 2013 <DronLoko>

#include <iostream>

struct MinHeap {
    int* heap;
    int size;

    void BuildHeap( int*& arr, int size );
    void Heapify(int i);
    void Add( int element );
    int ExtractMin();
    int ReadMin();
};

void MinHeap::BuildHeap( int*& arr, int n ) {
    size = n;
    heap = arr;
    for ( int i = (n / 2 - 1); i >= 0; --i )
        MinHeap::Heapify(i);
}

void MinHeap::Heapify( int i ) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //Ищем меньшего сына
    int smallest = i;
    if ( left < size && heap[left] < heap[i] )
        smallest = left;
    if ( right < size && heap[right] < heap[smallest] )
        smallest = right;

    //Если есть меньший сын ...
    if ( smallest != i ) {
        std::swap( heap[smallest], heap[i] );
        MinHeap::Heapify( smallest );
    }
}

int MinHeap::ReadMin() {
    return heap[0];
}

int MinHeap::ExtractMin() {
    if ( size == 0 ) return 0;

    int result = heap[0];
    heap[0] = heap[--size];
    if ( size > 1 ) Heapify(0);
    return result;
}

void MinHeap::Add( int element ) {
    heap[size] = element;
    ++size;

    int i = size - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if ( heap[i] >= heap[parent] )
            return;
        std::swap( heap[i], heap[parent] );
        i = parent;
    }
}

int fastSum(MinHeap heap) {
    if ( heap.size <= 1 ) return 0;

    int result = 0;

    while ( heap.size > 1 ) {
        int min1 = heap.ExtractMin();
        int min2 = heap.ExtractMin();
        int sum = min1 + min2;
        result += sum;
        heap.Add( sum );
    }
    return result;
}

int main()
{
    int n = 0;
    std::cin >> n;
    
    int* arr = new int[n];
    
    for ( int i = 0; i < n; ++i )
        std::cin >> arr[i];
    
    MinHeap heap;
    heap.BuildHeap( arr, n );
    
    std::cout << fastSum( heap ) << std::endl;

    delete[] arr;
    return 0;
}

