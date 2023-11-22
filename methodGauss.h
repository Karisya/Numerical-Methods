#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
const int m = 3;


double* methodGauss(double mA[m + 1][m + 1], double* cB)
{
	const int n = m + 1;
	double X[n] = { 0 };
	for (int i = 0; i < n; i++) {
		int maxIndex = i;
		double max = mA[i][i];
		for (int j = i + 1; j < n; j++) {
			if (abs(max) < abs(mA[j][i])) {
				maxIndex = j;
				max = mA[j][i];
			}
		}
		if (i != maxIndex) {
			double root = cB[i];
			cB[i] = cB[maxIndex];
			cB[maxIndex] = root;
			for (int j = 0; j < n; j++) {
				double x = mA[i][j];
				mA[i][j] = mA[maxIndex][j];
				mA[maxIndex][j] = x;
			}
		}
		double a = mA[i][i];
		for (int j = i; j < n; j++)
		{
			mA[i][j] /= a;
		}
		cB[i] /= a;
		for (int j = i + 1; j < n; j++)
		{
			double s = mA[j][i];
			for (int k = i; k < n; k++)
			{
				mA[j][k] -= s * mA[i][k];
			}
			cB[j] -= s * cB[i];
		}
	}

	for (int k = n - 1; k >= 0; k--)
	{
		X[k] = cB[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= mA[k][i] * X[i];
		}
	}
	cout << endl;
	return X;
}