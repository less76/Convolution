#include "pch.h"
#include <iostream>
using namespace std;

#define x_dim 20
#define y_dim 20
#define fixed_x 0x5
#define fixed_y 0x5
#define len_x (fixed_x << 1) + (fixed_x >> 1) + (fixed_x >> 2) - (fixed_x % 4 == 0 )? fixed_x / 4: 0
#define len_y (fixed_y << 1) + (fixed_y >> 1) + (fixed_y >> 2) - (fixed_y % 4 == 0 )? fixed_y % 4: 0
#define x_arr ((fixed_x << 1) - (fixed_x >> 1))  //calculations
#define y_arr ((fixed_y << 1) - (fixed_y >> 1))
#define offset_x (fixed_x - 1 > 2) ? (fixed_x - 1): fixed_x & 0x3
#define offset_y (fixed_y - 1 > 2) ? (fixed_y - 1): fixed_y & 0x3

int **const arrange(int pointer[x_dim][y_dim]);
int **const convu(int **const pointer, int pointer1[x_dim][y_dim]);
void display(int pointer[x_dim][y_dim]);

int main()
{

	int x_1[x_dim][y_dim] = {
		{1,2,3,4,6},
		{5,6,7,8,6},
		{9,10,11,12,6},
		{13,14,15,16,6},
		{-13,-14,-15,-16,-6}
	};

	int y_1[x_dim][y_dim] = {
		{1,-1,-2,-5,9},
		{6,4,12,9,9},
		{6,7,-5,-9,9},
		{4,5,-1,-7,9},
		{7,8,9,1,2}
	};

	cout << "x" << endl;
	display(x_1);

	cout << "y" << endl;
	display(y_1);

	int **x = (arrange)(x_1);
	int **here = (convu)(x, y_1);

	return 0;
}

void display(int pointer[x_dim][y_dim]) {
	for (int i = 0; i < fixed_x; i++) {
		for (int j = 0; j < fixed_y; j++) {
			cout << "|" << pointer[i][j] << "|";
		}
		cout << " " << endl;
	}
}

int **const convu(int **const pointer, int pointer1[x_dim][y_dim]) {
	static int **data = new int*[x_dim];
	for (int i = 0; i < x_dim; i++) {
		data[i] = new int[y_dim];
	}

	for (int i = 0; i < x_dim; i++) {
		for (int j = 0; j < y_dim; j++) {
			data[i][j] = 0;
		}
	}

	for (int m = 0; m < len_x; m++) {
		for (int n = 0; n < len_y; n++) {
			int hold = 0;
			for (int i = 0; i < fixed_x; i++) {
				for (int j = 0; j < fixed_y; j++) {
					
					hold += (m >= (fixed_x - 1) && n >= (fixed_y - 1)) ? 
					pointer[i + n][j + m] * pointer1[(fixed_x - 1) - i][(fixed_y - 1) - j] : //data flipped on x axis
					-pointer[i + n][j + m] * pointer1[i][(fixed_x - 1) - j]; //default

				}
			}
			data[m][n] = hold;
		}
	}

	cout << "data" << endl;

	for (int i = offset_x; i < len_x; i++) {
		for (int j = offset_y; j < len_y; j++) {
			cout << "|" << data[j][i] << "|";
		}
		cout << " " << endl;
	}

	return (int**)data;
}

int **const arrange(int pointer[x_dim][y_dim]){
	
	static int **data = new int*[x_dim];
	for (int i = 0; i < x_dim; i++) {
		data[i] = new int[y_dim];
	}

	for (int i = 0; i < x_dim; i++) {
		for (int j = 0; j < y_dim; j++) {
			data[i][j] = 0;
		}
	}


	for (int i = 0; i < fixed_x; i++) {
		for (int j = 0; j < fixed_y; j++) {
			data[i + x_arr][j + y_arr] = pointer[i][j];
		}
	}

	return (int**)data;
}