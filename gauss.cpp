#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <math.h>
//#define See
#define File
using namespace std;

void show_array(double **const &syst, const int &rows, const int &cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << syst[i][j] << "\t";
		}
		cout << endl;
	}
}

void push_back(double **&syst, const int &rows, int &cols, double* const &b)
{
	cols++;
	double **newsyst = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		*(newsyst + i) = new double[cols];

		for (int j = 0; j < cols - 1; j++)
		{
			*(*(newsyst + i) + j) = *(*(syst + i) + j);
			//newsyst[i][j] = syst[i][j];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = cols - 1; j != cols; j++)
		{
			newsyst[i][j] = b[i];
		}

	}

	for (int i = 0; i < rows; i++)
		delete[] syst[i];
	delete[]syst;

	syst = newsyst;
}

bool test_0_rows(double** const &syst, const int &rows, const int &cols)
{
	for (int i = 0; i < rows;)
	{
		for (int j = 0; j < cols;)
		{
			if (syst[i][j])
			{
				if ((i == rows - 1) && (j == 0))
				{
					return true;
				}
				++i;
			}
			else
			{
				if (j == cols - 1)
				{
					return false;
				}
				++j;
			}
		}
	}
}

bool test_0_cols(double** const &syst, const int &rows, const int &cols)
{
	for (int j = 0; j < cols;)
	{
		for (int i = 0; i < rows;)
		{
			if (syst[i][j])
			{
				if ((j == cols - 1) && (i == 0))
				{
					return true;
				}
				++j;
			}
			else
			{
				if (i == rows - 1)
				{
					return false;
				}
				++i;
			}
		}
	}
}

bool test_0_dia(double** const &syst, const int &rows, const int &cols)
{
	for (int i = 0; i < rows; i++)
	{
		if (syst[i][i] == 0)
		{
			continue;
		}
		else
		{
			return true;
		}
	}
	if (syst[rows][rows] == 0)
		return false;
}


void trapeze(double **syst, const int &rows, const int &cols, const int &b)
{

	if (rows == 1 || cols == 1)
	{
		return;
	}

	if (syst[rows - 1][cols - 1] == 0)
	{
		double r;
		int i;
		for (i = 0; i < rows; i++) {
			if (syst[i][cols - 1] != 0) {
				break;
			}
		}
		if (i > rows - 2) {
			trapeze(syst, rows - 1, cols - 1, b);
			return;
		}
		for (int j = 0; j < cols; j++) {
			r = syst[rows - 1][j];
			syst[rows - 1][j] = syst[i][j];
			syst[i][j] = r;
		}
	}

	for (int i = 0; i < rows - 1; i++) {
		syst[i][b] -= syst[rows - 1][b] * syst[i][cols - 1] / syst[rows - 1][cols - 1];
		for (int j = 0; j < cols; j++) {
			syst[i][j] -= syst[rows - 1][j] * syst[i][cols - 1] / syst[rows - 1][cols - 1];
		}
	}

	trapeze(syst, rows - 1, cols - 1, b);
}

void solution(double **syst, const int &rows, const int &cols)
{
	double *x = new double[cols - 1];

	for (int i = 0; i < rows; i++)
	{
		double sum = 0;
		for (int j = 0; j < i; j++)
		{
			sum += syst[i][j] * x[j];
		}
		if (i == 0)
		{
			x[0] = syst[0][cols - 1] / syst[0][0];
		}
		else
		{
			x[i] = (syst[i][cols - 1] - sum) / syst[i][i];
		}
	}
	for (int i = 0; i < cols - 1; i++)
		cout << "x" << i + 1 << " = " << x[i] << endl;

#ifdef File
	ofstream fout;
	fout.open("xvector.txt", ofstream::app);
	for (int i = 0; i < cols - 1; i++)
		fout << "x" << i + 1 << " = " << x[i] << endl;
	fout.close();
#endif // File

	delete[]x;
	x = nullptr;

}


int main()
{
	SetConsoleOutputCP(1251);
	int rows, cols;
	cout << "Введите количество уравнений системы\t";
	cin >> rows;
	cout << "\nВведите количество переменных системы\t";
	cin >> cols;
	cout << endl;


	double **syst = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		syst[i] = new double[cols];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> syst[i][j];
		}
		cout << endl;
	}

	double *b = new double[rows];
	for (int i = 0; i < rows; i++)
	{
		cout << "b" << i + 1 << " = ";
		cin >> b[i];
		cout << endl;
	}


	ofstream fout1;
	fout1.open("xvector.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fout1 << "(" << syst[i][j] << ")*X" << j + 1;
			if (j != cols - 1)
				fout1 << " + ";
			else
			{
				fout1 << " = ";
			}
		}
		for (i; i < rows; i++)
		{
			fout1 << b[i];
			break;
		}
		fout1 << endl;
	}
	fout1 << endl;
	fout1.close();


#ifdef See
	show_array(syst, rows, cols);
	cout << endl;
#endif // See

	push_back(syst, rows, cols, b);

#ifdef See
	show_array(syst, rows, cols);
	cout << endl;
#endif // See

	if (test_0_cols(syst, rows, cols) && test_0_rows(syst, rows, cols) && test_0_dia(syst, rows, cols))
	{

		double *buf = new double[cols];
		double buf_b;
		for (int i = 0; i < rows - 1; i++)
		{
			for (int j = i + 1; j < cols; j++)
			{
				if (syst[j][i] > syst[i][i])
				{
					buf = syst[j];
					syst[j] = syst[i];
					syst[i] = buf;
				}
			}
		}
		delete[]buf;
		buf = nullptr;

		trapeze(syst, rows, cols - 1, cols - 1);

#ifdef See
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << syst[i][j] << "\t";
			}
			cout << endl;
		}
#endif // See
		solution(syst, rows, cols);
	}
	else
	{
		cout << "Система не имееет решений!\n";
	}

	for (int i = 0; i < rows; i++)
		delete[] syst[i];
	delete[]syst;
	syst = nullptr;

	delete[]b;
	b = nullptr;

	system("pause");
	return 0;
}
