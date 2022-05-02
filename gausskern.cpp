#include "iostream"
#include "math.h"
 
using namespace std; 
 
//******************gauskern generator*************************
//gauss : a pointer to an array of 3 double types；
//size : size of a gausskernel ；
//sigma : the standard deviation of the convolution kernel
//*************************************************************
void GetGaussianKernel(double **gaus, const int size,const double sigma);
 
int main(int argc, char *argv[])  
{
	int size = 3; 
	double **gaus = new double *[size];
	for(int i = 0; i < size; i++)
	{
		gaus[i] = new double[size]; 
	}
	cout << "siye = 3*3, Sigma = 1, gausskernel is :" <<endl;
	GetGaussianKernel(gaus, 3, 1); 	
	// cout<<"size = 5*5, Sigma = 10, gausskernel is :" <<endl;
	// GetGaussianKernel(gaus, 5, 10); 	
	system("pause");
	return 0;
}
 

void GetGaussianKernel(double **gaus, const int size, const double sigma)
{
	const double PI = 4.0*atan(1.0); 
	int center = size / 2;
	double sum = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			gaus[i][j] = (1/(2*PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
			sum += gaus[i][j];
		}
	}
 
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			gaus[i][j] /= sum;
			cout << gaus[i][j] << "  ";
		}
		cout << endl << endl;
	}
	return ;
}