#ifndef FOUR_ALGORITHMS_INCLUDE
#define FOUR_ALGORITHMS_INCLUDE

//#include <iostream>
//using namespace std;

int freddysAlgorithm(int a[], int n) {
	int maxSum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int thisSum = 0;
			//cout << "\nnew current sum";
			for (int k = i; k <= j; k++) {
				thisSum += a[k];
				//cout << "\nadding " << a[k] << " to current sum";
			}
			//cout << "\ncurrent thisSum  is " << thisSum;
			if (thisSum > maxSum) {
				//cout << "\nmaxSum is now " << thisSum;
				maxSum = thisSum;
			}
		}
	}
	//cout << "\nmaxSum is " << maxSum;
	return maxSum;
}

int susiesAlgorithm(int a[], int n) {
	int maxSum = 0;
	for (int i = 0; i < n; i++) {
		int thisSum = 0;

		for (int j = i; j < n; j++) {
			thisSum += a[j];

			if (thisSum > maxSum) {
				//cout << "\nmaxSum is now " << thisSum;
				maxSum = thisSum;
			}
		}
	}
	//cout << "\nmaxSum is " << maxSum;
	return maxSum;
}

int max3(int one, int two, int three) {
	if (one > two) {
		if (one > three)
			return one;
		else
			return three;
	}
	else {
		if (two > three)
			return two;
		else
			return three;
	}
}

int johnnysAlgorithm(int a[], int left, int right) {
	if (left == right) {
		if (left == 0)
			return 0;
		else if (a[left] > 0)
			return a[left];
		else
			return 0;
	}

	// split the array in 2 and find each half's max sum
	int center = (left + right) / 2;
	int maxLeftSum = johnnysAlgorithm(a, left, center);
	int maxRightSum = johnnysAlgorithm(a, center + 1, right);

	// find the max sum starting at center and moving left
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for (int i = center; i >= left; i--) {
		leftBorderSum += a[i];
		if (leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}

	// find the max sum starting at center and moving right
	int maxRightBorderSum = 0, rightBorderSum = 0;
	for (int i = center + 1; i <= right; i++) {
		rightBorderSum += a[i];
		if (rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}
	//cout << "\nmaxSum is " << max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int sallysAlgorithm(int a[], int n) {
	int maxSum = 0, thisSum = 0;
	for (int i = 0; i < n; i++) {
		thisSum += a[i];
		if (thisSum > maxSum) {
			//cout << "\nmaxSum is now " << thisSum;
			maxSum = thisSum;
		}
		else if (thisSum < 0)
			thisSum = 0;
	}
	//cout << "\nmaxSum is " << maxSum;
	return maxSum;
}


#endif
