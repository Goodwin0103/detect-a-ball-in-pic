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
void test_convolve();


int gausskernel[3][3] = {{75, 123, 75}, {123, 200, 123}, {75, 123, 75}};

float image1[4][4] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

float **image = (float **)malloc(sizeof(float *) * 4);


int main(int argc, char *argv[])  
{
	test_convolve();
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			cout << image[i][j] << ' ';
		}
		cout << endl ;
	}
	system("pause");
	return 0;
}
 

void test_convolve(){

	for (int i = 0; i < 4;i++){
		image[i] = image1[i];
	}
	convolve3x3(image, image, gausskernel, 4, 4); 
	
}
void convolve3x3(float **Img, float **ImgFilt, int kernel[3][3], int height, int width){
	
	//kernel normalization
	int kernel_sum;
	double normalized_gausskernel[3][3];
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			kernel_sum = kernel_sum + kernel[i][j];
		}
	}

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			normalized_gausskernel[i][j] = (double)gausskernel[i][j] / kernel_sum;
		}
	}
	double y_kernel[3] = {normalized_gausskernel[0][0], normalized_gausskernel[0][1],  normalized_gausskernel[0][2]};
	double x_kernel[3] = {normalized_gausskernel[0][0] / normalized_gausskernel[0][0], normalized_gausskernel[0][1] / normalized_gausskernel[0][0], normalized_gausskernel[0][2] / normalized_gausskernel[0][0]};
	
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
						y_padding_image[i + 1][j] = x_out_image[i][j];
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
   	// // multiply matrixes
	// for (int i = 0; i < height; i++){
	// 	for (int j = 0; j < width; j++)
	// 	{
	// 		float out_sum = 0;
	// 		for (int k = 0; k < width; k++){
	// 			out_sum = out_sum + x_out_image[i][k] * y_out_image[k][j];
	// 			out_image[i][j] = out_sum;
	// 		}
	// 	}
	// }

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
		{
			// Img[i][j] = out_image[i][j] / kernel_sum;
			Img[i][j] = y_out_image[i][j];
		}
	}
}
