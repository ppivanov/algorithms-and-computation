#include <iostream>
#include "TemplatedHeap.h"

using std::cout;
using std::endl;
using std::swap;

template <typename T>
TemplatedHeap<T>::TemplatedHeap() = default;

template <typename T>
TemplatedHeap<T>::~TemplatedHeap() = default;

template <typename T>
void TemplatedHeap<T>::insert(T toadd)
{
	heap.push_back(toadd);
	trickleUp();
}

template <typename T>
void TemplatedHeap<T>::remove()
{
	heap.erase(heap.begin());
}

template <typename T>
void TemplatedHeap<T>::trickleUp()
{
	int nodeIndex = heap.size()-1;
	while (nodeIndex > 0) {
		int parentIndex = (nodeIndex - 1) / 2;

		if (heap[nodeIndex] > heap[parentIndex]) {
			swap(heap[nodeIndex], heap[parentIndex]);
			nodeIndex = parentIndex;
		}
		else
			break;
	}
}

template <typename T>
void TemplatedHeap<T>::trickleDown(int heapSize)
{
	int nodeIndex = 0;
	while (nodeIndex < heapSize) {
		int leftChildIndex = 2 * nodeIndex + 1;
		int rightChildIndex = 2 * nodeIndex + 2;
		int indexToSwap = -1;

		bool leftChildInRange = leftChildIndex < heapSize;
		bool rightChildInRange = rightChildIndex < heapSize;

		if ((leftChildInRange && rightChildInRange)
				&& (heap[nodeIndex] < heap[leftChildIndex] 
				|| heap[nodeIndex] < heap[rightChildIndex])) {
			if (heap[leftChildIndex] < heap[rightChildIndex])				// if node has children on both branches then swap with the larger one
				indexToSwap = rightChildIndex;
			else 
				indexToSwap = leftChildIndex;
		}
		else if (leftChildInRange && heap[nodeIndex] < heap[leftChildIndex]) {
			indexToSwap = leftChildIndex;
		}
		else if (rightChildInRange && heap[nodeIndex] < heap[rightChildIndex]) {
			indexToSwap = rightChildIndex;
		}
		else
			break;												// node is in correct position in heap
		
		swap(heap[nodeIndex], heap[indexToSwap]);
		nodeIndex = indexToSwap;
	}
}

template <typename T>
void TemplatedHeap<T>::trickleUpRec()
{
	int nodeIndex = heap.size() - 1;
	trickleUpRec(nodeIndex);
}
template <typename T>
void TemplatedHeap<T>::trickleUpRec(int nodeIndex)
{
	if (nodeIndex < 1) return;
	int parentIndex = (nodeIndex - 1) / 2;

	if (heap[nodeIndex] > heap[parentIndex]) {
		swap(heap[nodeIndex], heap[parentIndex]);
		trickleUpRec(parentIndex);
	}
}

template <typename T>
void TemplatedHeap<T>::trickleDownRec(int heapSize)
{
	trickleDownRec(0, heapSize);
}
template <typename T>
void TemplatedHeap<T>::trickleDownRec(const int& nodeIndex, const int& heapSize)
{
	if (nodeIndex > heapSize) return;
	int leftChildIndex = 2 * nodeIndex + 1;
	int rightChildIndex = 2 * nodeIndex + 2;
	int indexToSwap = -1;

	bool leftChildInRange = leftChildIndex < heapSize;
	bool rightChildInRange = rightChildIndex < heapSize;

	if ((leftChildInRange && rightChildInRange)
		&& (heap[nodeIndex] < heap[leftChildIndex]
			|| heap[nodeIndex] < heap[rightChildIndex])) {
		if (heap[leftChildIndex] < heap[rightChildIndex])				// if node has children on both branches then swap with the larger one
			indexToSwap = rightChildIndex;
		else
			indexToSwap = leftChildIndex;
	}
	else if (leftChildInRange && heap[nodeIndex] < heap[leftChildIndex]) {
		indexToSwap = leftChildIndex;
	}
	else if (rightChildInRange && heap[nodeIndex] < heap[rightChildIndex]) {
		indexToSwap = rightChildIndex;
	}
	else
		return;												// node is in correct position in heap

	swap(heap[nodeIndex], heap[indexToSwap]);
	trickleDownRec(indexToSwap, heapSize);
}

template <typename T>
void TemplatedHeap<T>::heapSort() {
	int unsortedLength = heap.size();

	while (unsortedLength > 0) {
		swap(heap[0], heap[unsortedLength - 1]);
		unsortedLength--;
		trickleDown(unsortedLength);
	}
}

template <typename T>
void TemplatedHeap<T>::heapSortRec() {
	int unsortedLength = heap.size();

	while (unsortedLength > 0) {
		swap(heap[0], heap[unsortedLength - 1]);
		unsortedLength--;
		trickleDownRec(unsortedLength);
	}
}

template <typename T>
void TemplatedHeap<T>::display()
{
	int prevLevelWidth = 1;
	int levelWidth = prevLevelWidth;
	int childCounter = 2;
	for (int i = 0; i < heap.size(); i++)
	{
		cout << heap[i];
		levelWidth--;
		childCounter--;

		if (levelWidth <= 0) {
			cout << "\n";
			levelWidth = prevLevelWidth * 2;
			prevLevelWidth = levelWidth;
			childCounter = 2;
		}
		else {
			if (childCounter == 0) cout << "\t|";
			cout << "\t";
		}
	}
	cout << "\n\n";
}

template <typename T>
void TemplatedHeap<T>::displayAsArray()
{
	for (int i = 0; i < heap.size(); i++)
	{
		cout << heap[i] << "\t";
	}
	cout << "\n\n";
}
