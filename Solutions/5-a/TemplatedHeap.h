#pragma once
#include <vector>

using std::vector;

template <typename T>
class TemplatedHeap
{
public:
	TemplatedHeap();
	~TemplatedHeap();

	void insert(T);
	void remove();

	void trickleUp();
	void trickleDown(int);

	void trickleUpRec();
	void trickleDownRec(int);

	void heapSort();
	void heapSortRec();

	void display();
	void displayAsArray();
private:

	void trickleUpRec(int);
	void trickleDownRec(const int&, const int&);

	vector<T> heap;

};

