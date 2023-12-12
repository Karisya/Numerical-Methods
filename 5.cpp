#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
int n = 4;
const double p = 2, r = 0.5;

double func(double x) {
	return sqrt(1 + 2 * pow(x, 3));
}

double func2(int i, int j)
{
	double a = 0, b = 4, c = 1, d = 2;
	double hx = (b-a) / (2 * n), hy = (d - c) / (2 * n);
	double x = a  + i * hx, y = c + j * hy;
	double F = pow(x, 2) / (1 + pow(y, 2));
	if (x > b && y > d)
		return 0;
	else
		return F;
}

void trapezoidFormula(double);
void SimpsonsFormula(double);
void SimpsonsCubatureFormula(double e);

int main() {
	setlocale(LC_ALL, "Russian");
	double a = 1.2, b = 2.471;
	double e1 = pow(10, -4), e2 = pow(10, -5);

	cout << "trapezoidFormula (e1): " << endl;
	trapezoidFormula(e1);
	cout << "trapezoidFormula (e2): " << endl;
	trapezoidFormula(e2);
	cout << "SimpsonsFormula (e1):" << endl;
	SimpsonsFormula(e1);
	cout << "SimpsonsFormula (e2):" << endl;
	SimpsonsFormula(e2);
	cout << "SimpsonsCubatureFormula(e1)" << endl;
	SimpsonsCubatureFormula(e1);
	cout << "SimpsonsCubatureFormula(e2)" << endl;
	SimpsonsCubatureFormula(e2);
	cout << endl;
}

void trapezoidFormula(double e) {
	double a = 1.2, b = 2.471;
	double I2 = 0, R = 0, x = a,h = (b - a) / n, I = 0;
	for (int i = 0; i < n - 1; i++)
	{
		x += h;
		I += 2 * func(x);
	}
	I = (I + func(a) + func(b)) * h / 2;

	while (abs(I - I2) > 3 * e) {
		n *= 2;
		h = (b - a) / n;
		I2 = I;
		I = func(a) + func(b);
		x = a;
		for (int i = 0; i < n - 1; i++)
		{
			x += h;
			I += 2 * func(x);
		}
		I = (I + func(a) + func(b)) * h / 2;
	}

	R =(-1)*(I2 - I) / (pow(r, p) - 1);
	cout << I << endl;
	cout << "calculation error: " << R << endl;

}

void SimpsonsFormula(double e) {
	double a = 1.2, b = 2.471;
	double h = (b - a) / n, I = 0, I2 = 0, x = a, R;
	for (int i = 0; i < n - 1; i += 2)
	{

		x += h;
		I += 4 * func(x);
		x += h;
		I += 2 * func(x);
	}
	I = (I + func(a) + func(b)) * (h / 3);

	while (abs(I - I2) > 15 * e)
	{
		n *= 2;
		h = (b - a) / n;
		I2 = I;
		I = func(a) + func(b);
		x = a;
		for (int i = 0; i < n - 1; i += 2)
		{
			x += h;
			I += 4 * func(x);
			x += h;
			I += 2 * func(x);
		}
		I *= h / 3;
	};

	R = (-1)*(I2 - I) / (pow(0.5, 4) - 1);
	cout << I << endl;
	cout << "calculation error: " << R << endl;
}

void SimpsonsCubatureFormula(double e)
{
	double a = 0, b = 4, c = 1, d = 2;
	int m = 4;
	double hx = abs(c - a) / (2 * n), hy = abs(d - b) / (2 * m), I = 0, I2 = 0;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m - 1; j++)
		{
			I += func2(2 * i, 2 * j) + 4 * func2(2 * i + 1, 2 * j) + func2(2 * i + 2, 2 * j)
				+ 4 * func2(2 * i, 2 * j + 1) + 16 * func2(2 * i + 1, 2 * j + 1) + 4 * func2(2 * i + 2, 2 * j + 1)
				+ func2(2 * i, 2 * j + 2) + 4 * func2(2 * i + 1, 2 * j + 2) + func2(2 * i + 2, 2 * j + 2);
		}
	}
	I *= (hx * hy) / 9;


		I2 = I;
	do 
	{
		n *= 2;
		m *= 2;
		hx = (b - a) / 2 * n;
		hy = (d - c) / 2 * m;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < m - 1; j++)
			{
				I += func2(2 * i, 2 * j) + 4 * func2(2 * i + 1, 2 * j) + func2(2 * i + 2, 2 * j)
					+ 4 * func2(2 * i, 2 * j + 1) + 16 * func2(2 * i + 1, 2 * j + 1) + 4 * func2(2 * i + 2, 2 * j + 1)
					+ func2(2 * i, 2 * j + 2) + 4 * func2(2 * i + 1, 2 * j + 2) + func2(2 * i + 2, 2 * j + 2);
			}
		}
		I *= hx * hy / 9;
	} while (abs(I2 - I) > 15 * e);

	cout << I << endl;
}