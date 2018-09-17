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


double F (double x)
{
	return 2 * x * sqrt(x);	
}

double F_obr (double nu)
{
	return pow(nu / 2.0, 2.0 / 3.0);
}

int main() {
	
	cout << "Enter n: ";
	int n;
	cin >> n;
	
	double C = pow(0.5, 2.0/3.0);
	
	srand( time(0) );
	
	double * mas_nu = new double[n]; 		// ћассив с.в. равномерно распределЄнных на [0,1]
	double * mas_x = new double[n];			// ћассив с.в. распределЄнных по данному закону распределени€ на [0, C]
	double * mas_F = new double[n];
	
	for (int i = 0; i < n; i++)
	{
		mas_nu[i] = DoubleRand(1.0, 0.0);
		mas_x[i] = F_obr(mas_nu[i]);
	}
	
	double M_t = pow(C, 2.5) * 3.0 / 2.5; 
	double D_t = pow(C, 3.5) * 3.0 / 3.5 - M_t * M_t; 
	
	double M_v = 0;        
	double D_v = 0;
	
	for (int i = 0; i < n; i++)
	{
		M_v += mas_x[i] / double(n);
	}
	for (int i = 0; i < n; i++)
	{
		D_v += (mas_x[i] - M_v) * (mas_x[i] - M_v) / double(n - 1);
	}
	
	cout << "M_t = " << M_t <<endl;
	cout << "D_t = " << D_t <<endl;
	
	cout << "M_v = " << M_v << endl; 
	cout << "D_v = " << D_v << endl; 
	
	double h = C / double(n);
	int * mas_n_j = new int[n];
	for (int i = 0; i < n; i++)
		mas_n_j[i] = 0;
	
	for(int i = 0; i < n; i++)
	{
		double cur = 0.0;
		
		for(int k = 0; k < n; k++)
		{
			cur += h;
			
			if(mas_x[i] <= cur) 
			{
				mas_n_j[k]++;
				break;
			}
		}
	}

	double * mas_p_j = new double[n];		//¬еро€тность попадани€ в j-тый интервал
	for(int i = 0; i < n; i++)
	{
		mas_p_j[i] = F(h * (i + 1)) - F(h * i);
	}
	
	double * mas_E_j = new double[n];		//ќжидаемое число попаданий в j-тый интервал
	for(int i = 0; i < n; i++)
	{
		mas_E_j[i] = n * mas_p_j[i];
	}
	
	double XI = 0.0;
	for(int i = 0; i < n; i++)
	{
	//	cout << mas_n_j[i] << endl;
		XI += (mas_n_j[i] - mas_E_j[i]) * (mas_n_j[i] - mas_E_j[i]) / mas_E_j[i];
	}
	cout <<"XI = " << XI <<endl;

	
	return 0;
}

