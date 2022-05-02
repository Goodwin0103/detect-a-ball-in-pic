#include "iostream"
#include "math.h"
 
using namespace std; 
 
//******************gauskern generator*************************
//gauss : a pointer to an array of 3 double types；
//size : size of a gausskernel ；
//sigma : the standard deviation of the convolution kernel
//*************************************************************
float ** GetGaussianKernel( const float sigma);
void convolve3x3(float **Img, float **ImgFilt, int kernel[3][3], int height, int width);
float padding(float **Img, char axis, int height, int width);

int main(int argc, char *argv[])  
{
	const int size = 3;
	// float **gauss = new float *[size];
	int gausskernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	float image1[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17};

	float **image = (float **)malloc(sizeof(float *) * 4);


	for (int i = 0; i < 4;i++){
		image[i] = image1[i];
	}

		convolve3x3(image, image, gausskernel, 4, 4); 
		// for(int i = 0; i < size; i++)
	// {
	// 	gauss[i] = new float[size]; 	
	// }
	// gauss = GetGaussianKernel(1);

	// for (int i = 0; i < size; i++)
	// {
	// 	for(int j = 0; j < size; j++)
	// 	{
	// 		gausskernel[i][j] = gauss[i][j];
	// 		cout << gauss[i][j] << "  ";
	// 	}
	// 	cout << endl << endl;
	// }
	// system("pause");
	// return 0;
}
 

float ** GetGaussianKernel(const float sigma)
{
	const float PI = 4.0*atan(1.0);
	const int size = 3;
	int center = size / 2;
	float sum = 0;
	float **gauss = new float *[size];

	for(int i = 0; i < size; i++)
	{
		gauss[i] = new float[size]; 
	}

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			gauss[i][j] = (1/(2*PI*sigma*sigma))*exp(-((i-center)*(i-center)+(j-center)*(j-center))/(2*sigma*sigma));
			sum += gauss[i][j];
		}
	}
 	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			gauss[i][j] /= sum;
		}
	}
	return  gauss;
}


void convolve3x3(float **Img, float **ImgFilt, int kernel[3][3], int height, int width){

	int y_kernel[3] = {kernel[0][0], kernel[0][1],  kernel[0][2]};
	int x_kernel[3] = {kernel[0][0] / kernel[0][0], kernel[0][1] / kernel[0][0], kernel[0][2] / kernel[0][0]};
	
	float x_padding_image[height][width + 2];
	float y_padding_image[height + 2][width];

		for (int i = 0; i < height ; i++) // padding the 1. and last rows
		{
			x_padding_image[i][0] = 0;
			x_padding_image[i][width + 1] = 0;
		}
		// filling padding_img with orig. image
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height ; j++) 
					{
						// printf("%3.0f", Img[i][j]);
						x_padding_image[i][j + 1] = Img[i][j];
					}
		}

		for (int j = 0; j < width; j++) // padding the 1. and last columns
		{
			y_padding_image[0][j] = 0;
			y_padding_image[height + 1][j] = 0;
		}
		// filling padding_img with orig. image
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height ; j++) 
					{
						y_padding_image[i + 1][j] = Img[i][j];
					}
		}	
	// x_padding_image[height][width + 2] = padding(Img, 'x', height, width);
	// y_padding_image[height + 2][width] = padding(Img, 'y', height, width);

	float x_out_image[height][width];
	float y_out_image[height][width];
	float out_image[height][width];


	//convolve with the x_kernel
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
		{
			float x_sum = 0;
			for (int k = 0; k < 3; k++){
				 x_sum = x_sum + (x_padding_image[i][j + k] * x_kernel[k]);
				 x_out_image[i][j] = x_sum;
			}
		}
	}

	//convolve with the y_kernel
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
		{
			float y_sum = 0;		
			for (int k = 0; k < 3; k++){
				y_sum = y_sum + (y_padding_image[i + k][j] * y_kernel[k]);
				y_out_image[i][j] = y_sum;
			}
		}
	}
   	// multiply matrix
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
		{
			float out_sum = 0;
			for (int k = 0; k < width; k++){
				out_sum = out_sum + x_out_image[i][k] * y_out_image[k][j];
				out_image[i][j] = out_sum;
			}
		}
	}

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
		{
			Img[i][j] = out_image[i][j];
		}
	}
}
