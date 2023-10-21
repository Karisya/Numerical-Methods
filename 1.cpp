#include <iostream>;
#include<algorithm>
#include<math.h>

using namespace std;

double firstStep(double array[3][3], const int, double[]);
double secondStep(double array[3][3], const int, double[]);
double thirdStep(double array[3][3], const int, double[], double[]);
double vF(double mA[3][3], double* cB, double* X, const int size, double[]);
double norma(double[], const int);
double display(double array[3][3], const int, double[]);
double bGauss(double arr[3][3], const int, double[], double[]);
double relativeError(double[], double[], const int);


int main() {
	const int size = 3;
	double X[size] = { 0 };
	double newB[size] = { 0 };
	double newX[size] = { 0 };
	double vectorF[size] = { 0 };
	double mA[size][size] = {
		{2.6,-4.50, -2 },
		{3,3,4.30},
		{-6,3.50,3}
	};
	double cB[size] = { 19.07, 3.21, -18.25 };

	cout << "Initial matrix:" << endl;
	display(mA, size, cB);


	firstStep(mA, size, cB);
	cout << "First matrix:" << endl;
	display(mA, size, cB);

	cout << "Second matrix:" << endl;

	secondStep(mA, size, cB);
	display(mA, size, cB);

	cout << "Solution:" << endl;
	thirdStep(mA, size, cB, X);

	cout << "vector F : " << endl;
	vF(mA, cB, X, size, vectorF);

	cout << "norma:" << endl;
	norma(vectorF, size);

	bGauss(mA, size, X, newB);
	firstStep(mA, size, newB);
	secondStep(mA, size, newB);
	thirdStep(mA, size, newB, newX);
	relativeError(X, newX, size);

}

double display(double mA[3][3], const int size, double* cB) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << mA[i][j] << "\t";
		}
		cout << "=\t" << cB[i];
		cout << "\n";
	}
	cout << endl;
	return 0;
};

double firstStep(double mA[3][3], const int size, double cB[]) {
	for (int i = 0; i < size; i++) {
		int maxIndex = i;
		double max = mA[i][i];
		for (int j = i + 1; j < size; j++) {
			if (abs(max) < abs(mA[j][i])) { //поиск максимального по модулю элемента
				maxIndex = j;
				max = mA[j][i];
			}
		}

		//перестановка строк местами

		if (i != maxIndex) {
			double root = cB[i];
			cB[i] = cB[maxIndex];
			cB[maxIndex] = root;
			for (int j = 0; j < size; j++) {
				double x = mA[i][j];
				mA[i][j] = mA[maxIndex][j];
				mA[maxIndex][j] = x;
			}
		}
	}

	return 0;
}

double secondStep(double mA[3][3], const int size, double* cB) {

	for (int i = 0; i < size; i++) 
	{
		double a = mA[i][i];
		for (int j = i; j < size; j++)
		{
			mA[i][j] /= a;
		}
		cB[i] /= a;
		for (int j = i + 1; j < size; j++)
		{
			double s = mA[j][i];
			for (int z = i; z < size; z++)
			{
				mA[j][z] -= s * mA[i][z];
			}
			cB[j] -= s * cB[i];
		}
	}
	return 0;
}

	double thirdStep(double mA[3][3], const int size, double* cB, double* X) {

		for (int k = size - 1; k >= 0; k--) 
		{
			X[k] = cB[k];
			for (int i = size - 1; i > k; i--)
			{
				X[k] -= mA[k][i] * X[i];
			}
		}
		for (int i = 0; i < size; i++) {
			cout << X[i] << "\t";
		}
		cout << endl;
	
	return 0;
}
double vF(double mA[3][3], double* cB, double* X, const int size, double* vectorF) {

	for (int i = 0; i < size; i++)
	{
		vectorF[i] = -cB[i];
		for (int j = 0; j < size; j++)
		{
			vectorF[i] += mA[i][j] * X[j];
		}
	}

	cout << *vectorF << endl;
	return 0;
}

double norma(double* vF, const int size) {
	double n = abs(vF[0]);
	for (int i = 0; i < size; i++) {
		n = max(vF[i], n);
	}
	cout << n;
	return 0;
}

double bGauss(double arr[3][3], const int size, double x[], double g[]) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			g[j] = arr[i][j] * x[j];
	}
	return 0;
}

double relativeError(double x1[], double x2[], const int size) {
	double res[3] = { 0 };
	cout << "relative error:" << endl;
	for (int i = 0; i < size; i++) {
		res[i] = (x2[i] - x1[i]) / x1[i];
		cout << res[i] << ' ';
	}

	return 0;
}
