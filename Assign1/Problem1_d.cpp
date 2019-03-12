#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

int main(){
	FILE *file_i[2];
	FILE *file_o[2];
	FILE *data_o;
	file_i[0] = fopen("D.raw", "rb");
	file_i[1] = fopen("E.raw", "rb");
	file_o[0] = fopen("H_D.raw", "w");
	file_o[1] = fopen("H_E.raw", "w");
	data_o = fopen("Problem1_d.csv", "w");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;	
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;	
	if (data_o == NULL) cout << "Cannot open the writing file!" << endl;	

	int pix[2][256] = {{0}};
	for (int k = 0; k < 2; k ++){
		unsigned char img[size][size];
		fread(img, sizeof(unsigned char), size * size, file_i[k]);
		fclose(file_i[k]);

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				pix[k][img[i][j] - 1] += 1;

		for (int n = 1; n < 256; n ++)
			pix[k][n] += pix[k][n - 1];

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				img[i][j] = pix[k][img[i][j]] / 256;

		for (int n = 0; n < 256; n ++)
			pix[k][n] = 0;

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				pix[k][img[i][j] - 1] += 1;

		fwrite(img, sizeof(unsigned char), size * size, file_o[k]);
		fclose(file_o[k]);
	}

	for (int n = 0; n < 256; n ++)
		fprintf(data_o, "%d,%d,%d\n", n + 1, pix[0][n], pix[1][n]);
	fclose(data_o);

	return 0;
}