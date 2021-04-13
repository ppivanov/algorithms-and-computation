// Pavel Ivanov x00149863


// void merge( array_A[], array_B[] ) {											-- NOTE: assumes the arrays are sorted
//	leftIndex = 0
//	rightIndex = 0
//	tempArray [sizeof(array_A)]
// 
//	while(leftIndex < elements_in_A && rightIndex < sizeof(array_B))			-- start adding the smallest elements of each array
//	do
//		if array_A[leftIndex] < array_B[rightIndex] then
//			tempArray.add( array_A[leftIndex] )
//			leftIndex += 1														-- move left index since the value is already added
//		else
//			tempArray.add( array_B[rightIndex] )
//			rightIndex += 1														-- move right index since the value is already added
//		end if
//	end while
// 
//	while(leftIndex < elements_in_A)											-- add any remaining elements from array_A
//	do
//		tempArray.add( array_A[leftIndex] )
//		leftIndex += 1
//	end while
// 
//	while(rightIndex < sizeof(array_B))											-- add any remaining elements from array_B
//	do
//		tempArray.add( array_B[rightIndex] )
//		rightIndex += 1
//	end while
// 
//	for(int i = 0; i < sizeof(array_A); i++)
//	do
//		array_A[i] = tempArray[i]
//	end for
// 
//																				-- at this point array_A should contain the elements 
//																				-- of both array_A and array_B in sorted order
// }