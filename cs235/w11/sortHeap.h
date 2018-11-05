/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

template <class T>
class Heap
{
public:
	Heap() : array(NULL), size(0) {};
	Heap(T rhs[], int num);
	~Heap() { delete array; }

	T getMax() { return array[1]; }
	void deleteMax();
	void percolateDown(int i, int n);
	void heapify(int n);
	void sort();

	T& operator[] (const int index) { return array[index]; }
	T& operator[] (const int index) const { return array[index]; }

private:
	T* array;
	int size;
};

template<class T>
Heap<T>::Heap(T rhs[], int num)
{
	array = new T[num + 1];
	//fill first position with dummy value
	array[0] = T();
	//fill heap with rhs's values starting at [1]
	for (int i = 1; i <= num; i++)
		array[i] = rhs[i - 1];

	// set size equal to rhs size
	size = num;
}

template<class T>
void Heap<T>::deleteMax()
{
	// set last item in array equal to first
	array[1] = array[size];
	// decrement size
	size--;

	// fix the heap from the top down
	percolateDown(1, size);
}

template<class T>
void Heap<T>::percolateDown(int top, int bottom)
{
	int child;
	T temp;
	temp = array[top];
	child = 2 * top;
	while (child <= bottom)
	{
		if (child < bottom && array[child + 1] > array[child])
			child = child + 1;
		if (temp > array[child])
			break;
		else if (temp <= array[child])
		{
			array[child / 2] = array[child];
			child = 2 * child;
		}
	}
	array[child / 2] = temp;
}

template<class T>
void Heap<T>::heapify(int size)
{
	int i;
	for (i = size / 2; i >= 1; i--)
	{
		percolateDown(i, size);
	}
}

template<class T>
void Heap<T>::sort()
{
	for (int i = size - 1; i > 1; i--)
	{
		T temp = array[i];
		array[i] = array[1];
		array[1] = temp;

		percolateDown(1, i - 1);
	}
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
	Heap<T> heap(array, num);
	heap.heapify(num);

	for (int i = num - 1; i >= 0; i--)
	{
		array[i] = heap.getMax();
		heap.deleteMax();
	}
}

#endif // SORT_HEAP_H
