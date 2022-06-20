#include "iostream"
#include "math.h"
 
using namespace std;

void ColorFilter(int a, float **R, float **G, float **B, float **Mask, int height, int width);


float image1[5][5] = {2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

float **image = (float **)malloc(sizeof(float *) * 5);


int main(int argc, char *argv[])  
{
    for (int i = 0; i < 5;i++){
		image[i] = image1[i];
	}

    ColorFilter(2, image, image, image, image, 5, 5);
    for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			cout << image[i][j] << ' ';
		}
		cout << endl ;
	}
	system("pause");
	return 0;
}
 

void ColorFilter ( int a , float ** R , float** G, float** B , float** Mask , int height , int width ) {

    // rgb wert von Gelb 255 255 0 

    for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if( pow((R[i][j] - 255), 2)+ pow((G[i][j] - 255), 2)+ pow((B[i][j] - 0), 2)> pow(a , 2) ){
                    Mask[i][j] = 0;
                }
                else Mask[i][j] = 255;

            }
        }
}
