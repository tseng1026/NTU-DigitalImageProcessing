#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

int main(){
	FILE *file_i[3];
	FILE *data_o;
	file_i[0] = fopen("sample2.raw", "rb");
	file_i[1] = fopen("D.raw", "rb");
	file_i[2] = fopen("E.raw", "rb");
	data_o = fopen("Problem1_c.csv", "w");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[2] == NULL) cout << "Cannot open the reading file!" << endl;
	if (data_o == NULL) cout << "Cannot open the writing file!" << endl;	

	int pix[3][256] = {{0}};
	for (int k = 0; k < 3; k ++){
		unsigned char img[size][size];
		fread(img, sizeof(unsigned char), size * size, file_i[k]);
		fclose(file_i[k]);

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				pix[k][img[i][j] - 1] ++;
	}

	for (int n = 0; n < 256; n ++)
		fprintf(data_o, "%d,%d,%d,%d\n", n + 1, pix[0][n], pix[1][n], pix[2][n]);
	fclose(data_o);

	return 0;
}