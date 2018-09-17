#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <ctime>

using namespace std;

double DoubleRand(double _max, double _min)                 //с.з. равномерное распределенной на [_min, _max] с.в. 
{
	return _min + double(rand()) / RAND_MAX * (_max - _min); 
}


void create_mas_A (int* mas_A, int n) 
{
	for (int i = 0; i < n; i++)
	{
		mas_A[i] = i;
	}
}

void create_mas_P (double* mas_P, int n, double p) 
{
	double q = 1 - p;
	mas_P[0] = p;
	for (int i = 1; i < n; i++)
	{
		mas_P[i] = mas_P[i - 1] * q;
	}
}

int main() {
	
	cout << "Enter n: ";
	int n;
	cin >> n;
	cout << "Enter p: ";
	double p;
	cin >> p;
	
	int * mas_A = new int[n]; // Массив возможных значений с.в. a_k
	create_mas_A(mas_A, n);
	double * mas_P = new double[n];
	create_mas_P(mas_P, n, p);
	
	
	srand( time(0) );
	
	
	int * mas_AA = new int[n]; // Массив с.в. в выборке
	
	int * mas_n_j = new int[n]; //Массив, содержащий кол-во попаданий в определённый интверал
	for (int i = 0; i < n; i++) 
		mas_n_j[i] = 0;
		
	for (int i = 0; i < n; i++)
	{
		  double YFL = DoubleRand(1.0, 0.0); 
		  for(int k = 0; k < n; k++)
		  {
		  	YFL -= mas_P[k];
		  	
		  	if(YFL <= 0.0) 
		  	{
		  		mas_AA[i] = mas_A[k];
		  		mas_n_j[mas_AA[i]]++;
				break; 		
			}
		  }
	}
	
	double M_t = 0, M_v = 0;            // Теоретическое и выборочное мат. ожидание
	double D_t = 0, D_v = 0;            // Теоретическая и выборочная дисперсия
	
	for (int i = 0; i < n; i++)
	{
		M_t += mas_A[i] * mas_P[i];
		M_v += mas_AA[i] / double(n);
		D_t += mas_A[i] * mas_A[i] * mas_P[i];
	}
	for (int i = 0; i < n; i++)
	{
		D_v += (mas_AA[i] - M_v) * (mas_AA[i] - M_v) / double(n - 1);
	}
	
	D_t -= M_t * M_t;
	
	cout << "M_t = " << M_t <<endl;
	cout << "D_t = " << D_t <<endl;
	
	cout << "M_v = " << M_v << endl; 
	cout << "D_v = " << D_v << endl; 
	
	
	double * mas_E_j = new double[n]; // Массив ожидаемых чисел попаданий в i-й интервал
	for(int i = 0; i < n; i++)
		mas_E_j[i] = n * mas_P[i];
	
	double XI = 0.0;
	for(int i = 0; i < n; i++)
	{
	//	cout << mas_n_j[i] << endl;
		XI += (mas_n_j[i] - mas_E_j[i]) * (mas_n_j[i] - mas_E_j[i]) / mas_E_j[i];
	}
	cout <<"XI = " << XI <<endl;
	
	
	return 0;
}




