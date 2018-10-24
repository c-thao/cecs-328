#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

int  getSize(string);
void displayArray(int[], int );
void copyDynArr(int*, int*, int);
void InsertionSort(int[], int);
void QuickSortMOT(int*, int, int);
int  partition(int*, int, int, int);
void readIntsFromBinFile(int[], string);

int main() {

	auto startTime = high_resolution_clock::now();
	auto stopTime = high_resolution_clock::now();

	// sorted order
	// get original normal array
	int n = getSize("sorted.bin");
	cout << "\n\ninitializing array with size " << n;
	int* sNormInts = new int[n];
	readIntsFromBinFile(sNormInts, "sorted.bin");

	// make two copies of the array
	int* sNormInts1 = new int[n];
	int* sNormInts2 = new int[n];
	copyDynArr(sNormInts1, sNormInts, n);
	copyDynArr(sNormInts2, sNormInts, n);

	// display original in order array
	cout << "\noriginal sorted norm: ";
	displayArray(sNormInts, n);

	// times and displays the time for
	// insertion sorting an in order array
	startTime = high_resolution_clock::now();
	InsertionSort(sNormInts1, n);
	stopTime = high_resolution_clock::now();
	cout << "\ninsertion sort on sorted array took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// displays insertion sorted in order array
	cout << "\ninsertion sorted norm: ";
	displayArray(sNormInts1, n);

	// times and displays the time for
	// insertion sorting an in order array
	startTime = high_resolution_clock::now();
	QuickSortMOT(sNormInts2, 0, n-1);
	stopTime = high_resolution_clock::now();
	cout << "\nquick sort on sorted array took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// displays quick sorted in order array
	cout << "\nQuick sorted norm: ";
	displayArray(sNormInts2, n);

	delete[] sNormInts;
	delete[] sNormInts1;
	delete[] sNormInts2;
	

	// reverse order
	// get original reverse order array
	n = getSize("reverse.bin");
	cout << "\n\ninitializing array with size " << n;
	int* sRevInts = new int[n];
	readIntsFromBinFile(sRevInts, "reverse.bin");

	// make two copies of the reverse order array
	int* sRevInts1 = new int[n];
	int* sRevInts2 = new int[n];
	copyDynArr(sRevInts1, sRevInts, n);
	copyDynArr(sRevInts2, sRevInts, n);

	// displays original reverse order array
	cout << "\noriginal reverse norm: ";
	displayArray(sRevInts, n);

	// times and displays the time for
	// insertion sorting a reverse order array
	startTime = high_resolution_clock::now();
	InsertionSort(sRevInts1, n);
	stopTime = high_resolution_clock::now();
	cout << "\ninsertion sort on reverse array took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// displays insertion sorted reverse order array
	cout << "\ninsertion sorted reverse: ";
	displayArray(sRevInts1, n);

	// times and displays the time for
	// quick sorting a reverse order array
	startTime = high_resolution_clock::now();
	QuickSortMOT(sRevInts2, 0, n - 1);
	stopTime = high_resolution_clock::now();
	cout << "\nquick sort on reverse array took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// displays quick sorted reverse order array
	cout << "\nquick sorted reverse: ";
	displayArray(sRevInts2, n);

	delete[] sRevInts;
	delete[] sRevInts1;
	delete[] sRevInts2;
	
	
	// random array
	// get original random order array
	n = getSize("random.bin");
	cout << "\n\ninitializing array with size " << n;
	int* sRandInts = new int[n];
	readIntsFromBinFile(sRandInts, "random.bin");

	// make two copies of the random order array
	int* sRandInts1 = new int[n];
	int* sRandInts2 = new int[n];
	copyDynArr(sRandInts1, sRandInts, n);
	copyDynArr(sRandInts2, sRandInts, n);

	// displays orginal random order array
	cout << "\noriginal random norm: ";
	displayArray(sRandInts, n);

	// times and displays the time for
	// insertion sorting a random order array
	startTime = high_resolution_clock::now();
	InsertionSort(sRandInts1, n);
	stopTime = high_resolution_clock::now();
	cout << "\ninsertion sort on random array took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// display insertion sorted random order array
	cout << "\ninsertion sorted random: ";
	displayArray(sRandInts1, n);

	// times and displays the time for
	// quick sorting a random order array
	startTime = high_resolution_clock::now();
	QuickSortMOT(sRandInts2, 0, n - 1);
	stopTime = high_resolution_clock::now();
	cout << "\nquick sort on sorted random took ";
	cout << (duration_cast<milliseconds>(stopTime - startTime).count())
		<< " ms\n";

	// displays quick sorted random order array
	cout << "\nquick sorted random: ";
	displayArray(sRandInts2, n);

	delete[] sRandInts;
	delete[] sRandInts1;
	delete[] sRandInts2;
	
	return 0;
}

/*
displays an input array numArray
*/
void displayArray(int numArray[], int n) {
	int i = 0;
	while (i < n) {
		cout << (numArray[i++]) << " ";
	}
}

/*
get length of all strings in a file
*/
int getSize(string fileName) {
	ifstream input(fileName, ios::in | ios::binary);
	input.seekg(0, ios::beg);
	int n = 0;
	input.read((char*)&n, sizeof(int));
	return n;
}

/*
creates copy of a dynamic array
*/
void copyDynArr(int* arr1, int* arr2, int size) {
	for (int c = 0; c < size; c++) {
		*(arr1++) = *(arr2++);
	}
}

/*
Performs insertion sort on an input array a
*/
void InsertionSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		int j, temp = a[i];
		for (j = i - 1; j >= 0; j--) {
			if (a[j] > temp) {
				a[j + 1] = a[j];
			}
			else {
				break;
			}
		}
		a[j + 1] = temp;
	}
}

/*
Performs quicksort on an input array numArray
*/
void QuickSortMOT(int* numArray, int left, int right) {
	if ((right - left) <= 4 && (right - left) > 0) {
		InsertionSort(numArray, right + 1);
	}
	else if ((right - left) > 4) {
		int pIndex = left;
		if (numArray[left] < numArray[right]) {
			if (numArray[left] > numArray[((right - left) / 2) + left]) {
				pIndex = left;
			}
			else if (numArray[((right - left) / 2) + left] < numArray[right]) {
				pIndex = ((right - left) / 2) + left;
			}
			else {
				pIndex = right;
			}
		}
		else {
			if (numArray[right] > numArray[((right - left) / 2) + left]) {
				pIndex = right;
			}
			else if (numArray[((right - left) / 2) + left] < numArray[left]) {
				pIndex = ((right - left) / 2) + left;
			}
			else {
				pIndex = left;
			}
		}
		int m = partition(numArray, left, right, pIndex);
		QuickSortMOT(numArray, m + 1, right);
		QuickSortMOT(numArray, left, m);
	}
}

/*
performs partitioning on a input array a to determine a
pivot index, helper function for quicksort
*/
int partition(int* a, int left, int right, int pivotIndex) {
	int pivotValue = *(a + pivotIndex);
	swap(*(a + pivotIndex), *(a + right));

	int store = left;
	for (int i = left; i < right; i++) {
		if (a[i] < pivotValue) {
			swap(*(a + store),*(a + i));
			store++;
		}
	}
	swap(*(a + right), *(a + store));
	return store;
}

// read in binary mode integers
void readIntsFromBinFile(int sIntArray[], string fileName) {
	ifstream input(fileName, ios::in | ios::binary);
	
	// obtains size of file
	input.seekg(0, ios::end);
	streampos size = input.tellg();
	int mem = 0;
	int byFour = 4;

	// gets ints
	while (byFour < size) {
		input.seekg(byFour, ios::beg);
		input.read((char*)&mem, sizeof(int));
		(sIntArray[(byFour/4)-1]) = mem;
		byFour = byFour + 4;
	}
	input.close();
}