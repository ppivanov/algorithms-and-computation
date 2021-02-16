#include <iostream>
using std::cout;
using std::endl;
//Interchanges the values of variable1 and variable2.
//The assignment operator must work for the type T.
template < typename T>							// declaring a template 'T' that will be used by the function
void swapValues(T& variable1, T& variable2)		// variables 1 and 2 are of type 'T' and as pointed out on line 5, the assignment operator must work on both
{												// The template type limitations are dependent on the implementation where the template type is used.
	T temp;										// temp variable of template type
	temp = variable1;							// copy the value of 'variable1' to 'temp' -- in main -> temp == a
	variable1 = variable2;						// copy the value of variable 2 to 1 -- in main -> variable1 == b
	variable2 = temp;							// copy previous contents of variable 1 to 2 -- in main -> variable2 == a
}												// note - the parameters must be passed in by reference for the swap to work
int main()
{
	typedef int* ArrayPointer;	// define ArrayPointer type to be the same as int* (pointer to an int)
	ArrayPointer a, b, c;		// define 3 pointers
	a = new int[3];				// allocate 3 int memory locations to 'a' and 'b'
	b = new int[3];
	int i;
	for (i = 0; i < 3; i++)
	{
		a[i] = i;				// assign the iterator counter as the value of element at the iterator index
		b[i] = i * 100;			// same as above but times 100
	}
	c = a;						// have 'c' to point at the same starting location as 'a'
	cout << "a contains: ";
	for (i = 0; i < 3; i++)
		cout << a[i] << " ";	// outputs 0,1,2 as these were the values assigned via the loop iterator count
	cout << endl;
	cout << "b contains: ";
	for (i = 0; i < 3; i++)
		cout << b[i] << " ";	// outputs 0,100,200 as these were produced by multiplying the iterator count by 100
	cout << endl;
	cout << "c contains: ";
	for (i = 0; i < 3; i++)
		cout << c[i] << " ";	// this is more or less the same as looping over 'a'
	cout << endl;
	swapValues(a, b);			// see comments on the function -- simply swaps the value of the pointers to point to the other array
	b[0] = 42;					// set 42 as the first element of array 'b'
	cout << "After swapping a and b,\n"
		<< "and changing b:\n";
	cout << "a contains: ";
	for (i = 0; i < 3; i++)
		cout << a[i] << " ";	// now produces 0,100,200 as the pointers of 'a' and 'b' were swapped
	cout << endl;
	cout << "b contains: ";
	for (i = 0; i < 3; i++)
		cout << b[i] << " ";	// produces 42,1,2 as the first element was updated
	cout << endl;
	cout << "c contains: ";
	for (i = 0; i < 3; i++)
		cout << c[i] << " ";	// produces 42,1,2 since 'c' still points to the same array -> now 'b' and 'c' point to the same first element
	cout << endl;
	return 0;
}
