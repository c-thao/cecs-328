#include <iostream>
#include <random>
#include <chrono>
#include "four_algorithms.h"
using namespace std;
using namespace chrono;

int* obtainRandomArray(int, int);
int numInput();

int main() {
	int discont = 0, seed = 0, inSize = 0;
	while (discont != 1) {
		int userInput = 0;
		while (userInput < 1 || userInput > 5) {
			cout << "1. Quit the program.\n2. Time Freddy's algorithm.\n"
				<< "3. Time Susie's algorithm\n4. Time Johnny's algorithm\n"
				<< "5. Time Sally's algorithm\n";
			userInput = numInput();
		}
		if (userInput == 1) {
			discont = 1;
			cout << "\nquitting program now";
		}
		else {
			cout << "Please enter a seed value\n";
			seed = numInput();
			cout << "Now enter an input size\n";
			inSize = numInput();
			cout << "\n";

			int *randArray = obtainRandomArray(seed, inSize);
			/*for (int s = 0; s < inSize; s++) { // print array elements
				cout << randArray[s] << "\n";
			}*/

			auto startTime = high_resolution_clock::now();
			auto stopTime = high_resolution_clock::now();

			if (userInput == 2) {
				startTime = high_resolution_clock::now();
				cout << "maxSum is " << freddysAlgorithm(randArray, inSize) << endl;
				//freddysAlgorithm(randArray, inSize);
				stopTime = high_resolution_clock::now();
				cout << "freddysAlgorithm() took ";
			}
			else if (userInput == 3) {
				startTime = high_resolution_clock::now();
				cout << "maxSum is " << susiesAlgorithm(randArray, inSize) << endl;
				//susiesAlgorithm(randArray, inSize);
				stopTime = high_resolution_clock::now();
				cout << "susiesAlgorithm() took ";
			}
			else if (userInput == 4) {
				startTime = high_resolution_clock::now();
				cout << "maxSum is " << johnnysAlgorithm(randArray, 0, (inSize - 1)) << endl;
				//johnnysAlgorithm(randArray, 0, (inSize - 1));
				stopTime = high_resolution_clock::now();
				cout << "johnnysAlgorithm() took ";
			}
			else {
				startTime = high_resolution_clock::now();
				cout << "maxSum is " << sallysAlgorithm(randArray, inSize) << endl;
				//sallysAlgorithm(randArray, inSize);
				stopTime = high_resolution_clock::now();
				cout << "sallysAlgorithm() took ";

			}

			cout << (duration_cast<milliseconds>(stopTime - startTime).count())
				<< " ms" << endl;

			delete randArray;
		}
	}

	return 0;
}

// checks if input is a valid integer
int numInput() {
	int num = 0;
	cin >> num;
	while (!cin) {
		//cout << "checking if cin is flagged" << (!cin);
		cin.clear(); //clear bad input flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
		cout << "\nInvalid input please re-enter.\n";
		cin >> num;
	}
	return num;
}

// generates an array of a user defined size with random integers
int* obtainRandomArray(int seed, int size) {
	int *array = new int[size];

	default_random_engine generator;
	generator.seed(seed);
	uniform_int_distribution<int> distribution(-100, 100);

	for (int i = 0; i < size; i++) {
		array[i] = distribution(generator);
	}
	return array;
}