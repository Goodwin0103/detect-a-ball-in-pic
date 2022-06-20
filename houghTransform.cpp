#include "iostream"
#include "math.h"
 
using namespace std;

int HoughTransform ( int R , unsigned char **EdgeMask , unsigned char **AccuGrid , int height , int width , int &x_found , int &y_found );


int main(int argc, char *argv[])  
{
    for (int i = 0; i < 12;i++){
		image[i] = image1[i];
	}
    for (int i = 0; i < 3;i++){
		EdgeMask[i] = EdgeMask1[i];
	}

    
    for (int i = 0; i < 12; i++){
		for (int j = 0; j < 12; j++){
			cout << image[i][j] << ' ';
		}
		cout << endl ;
	}
	system("pause");
	return 0;
}
 

int HoughTransform ( int R , unsigned char **EdgeMask , unsigned char **AccuGrid , int height , int width , int &x_found , int &y_found ) {

    for (int i = 0; i < height ; i++){
		for (int j = 0; j < width ; j++)
		{   
            if(EdgeMask[i][j] !=0 ){
                accumulateCircles(AccuGrid, R, i, j);
            }
		}
	}
    int max = 0;
    for (int i = 0; i < height + 2*R ; i++){
		for (int j = 0; j < width + 2*R ; j++)
		{   
            if(AccuGrid[i][j] > max){
                max = AccuGrid[i][j];
                x_found = i;
                y_found = j;
            }
		}
	}
    return max;

}
