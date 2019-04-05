#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

int col[8][3] = {
	{255, 250, 250},
	{255, 0, 0},
	{255, 153, 18}, 
	{255, 215, 0},
	{124, 252, 0}, 
	{135, 206, 235},
	{138, 43, 226},
	{255, 192, 203}};

unsigned char img[size][size];
unsigned char tmp[size][size];
unsigned char res[size][size][3];

void recursion(int lab, int i, int j){
	for (int m = -1; m <= 1; m ++)
		for (int n = -1; n <= 1; n ++){
			if (i + m < 0 || i + m > 255) continue;
			if (j + n < 0 || j + n > 255) continue;

			if (img[i + m][j + n] == 255 && tmp[i + m][j + n] == 0){
				tmp[i + m][j + n] = 255;
				res[i + m][j + n][0] = col[lab][0];
				res[i + m][j + n][1] = col[lab][1];
				res[i + m][j + n][2] = col[lab][2];

				recursion(lab, i + m, j + n);
			}
		}

	return;
}

int main(){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("sample1.raw", "rb");
	file_o = fopen("C.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int lab = 0;
	for (int i = 1; i < size - 1; i ++)
		for (int j = 1; j < size - 1; j ++){
			if (img[i][j] == 0) continue;		// black, no need to consider
			if (tmp[i][j] == 255) continue;		// white, already colored
			
			recursion(lab ++, i, j);
		}

	fwrite(res, sizeof(unsigned char), size * size * 3, file_o);
	fclose(file_o);
	return 0;
}