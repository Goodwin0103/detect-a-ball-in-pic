#include "iostream"
#include "math.h"
 
using namespace std;

void EdgeDetection ( float **ColorMask , int **EdgeMask , int height , int width , int threshold );

int EdgeMask1[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

float image1[12][12] =   {0,0,0,0,0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,0,0,0,0,
                          0,0,0,255,255,255,255,255,255,0,0,0,
                          0,0,0,255,255,255,255,255,255,0,0,0,
                          0,0,0,255,255,255,255,255,255,0,0,0, 
                          0,0,0,255,255,255,255,255,255,0,0,0,
                          0,0,0,255,255,255,255,255,255,0,0,0,
                          0,0,0,255,255,255,255,255,255,0,0,0,
                          0,0,0,0,0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,0,0,0,0 };
// float image1[4][4] =   {255,255,255,255,
//                             255,255,255,255,
//                             0,0,0,0,
//                             0,0,0,0
//                             };

float **image = (float **)malloc(sizeof(float *) * 12);
int **EdgeMask = (int **)malloc(sizeof(int *) * 3);

int main(int argc, char *argv[])  
{
    for (int i = 0; i < 12;i++){
		image[i] = image1[i];
	}
    for (int i = 0; i < 3;i++){
		EdgeMask[i] = EdgeMask1[i];
	}

    EdgeDetection(image, EdgeMask, 12, 12, 1000);
    
    for (int i = 0; i < 12; i++){
		for (int j = 0; j < 12; j++){
			cout << image[i][j] << ' ';
		}
		cout << endl ;
	}
	system("pause");
	return 0;
}
 


void EdgeDetection ( float **ColorMask , int **EdgeMask , int height , int width , int threshold )
{

	
	float padding_image[height+2][width + 2];

		for (int i = 0; i < height+2 ; i++) // padding the 1. and last rows
		{
			padding_image[i][0] = 0;
			padding_image[i][width + 1] = 0;
		}
        for (int i = 0; i < width+2 ; i++) // padding the 1. and last column
		{
			padding_image[0][i] = 0;
			padding_image[height + 1][i] = 0;
		}
		// filling padding_img with orig. image
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height ; j++) 
					{
						// printf("%3.0f", Img[i][j]);
						padding_image[i + 1][j + 1] = ColorMask[i][j];
					}
		}

	float x_edge[height][width];
	float y_edge[height][width];
	//convolve for horizon edge
	for (int i = 0; i < height ; i++){
		for (int j = 0; j < width ; j++)
		{   
            //convolve for horizon edge
            int x_sum = 0;
			for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    x_sum = x_sum + (padding_image[i + k][j + l] * EdgeMask[k][l]);
                }
			}
            if(abs(x_sum) > threshold){
                x_edge[i][j] = 255;
            }
            else  x_edge[i][j] = 0;

            //convolve for vertical edge
            int y_sum = 0;
			for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    y_sum = y_sum + (padding_image[i + k][j + l] * EdgeMask[l][k]);
                }
			}
            if(abs(y_sum) > threshold){
            y_edge[i][j] = 255;
            }
            else  y_edge[i][j] = 0;
		}
	}
    	for (int i = 0; i < height ; i++){
		for (int j = 0; j < width ; j++)
		{   
            if(x_edge[i][j] !=0 ||y_edge[i][j] !=0){
                ColorMask[i][j] = 255;
            }
            else ColorMask[i][j] = 0;
		}
	}

}
