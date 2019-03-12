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
	file_o[0] = fopen("L_D.raw", "w");
	file_o[1] = fopen("L_E.raw", "w");
	data_o = fopen("Problem1_e.csv", "w");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;	
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;	
	if (data_o == NULL) cout << "Cannot open the writing file!" << endl;	

	int pix[2][256] = {{0}};
	for (int k = 0; k < 2; k ++){
		unsigned char img[size][size];
		unsigned char tmp[size][size] = {{'\0'}};
		fread(img, sizeof(unsigned char), size * size, file_i[k]);
		fclose(file_i[k]);

		int win = 3;
		int hlf = win / 2;
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				int ara = 0, sum = 0;
				for (int m = i - hlf; m <= i + hlf; m ++)
					for (int n = j - hlf; n <= j + hlf; n ++){
						if (m < 0 || m > size - 1) continue;
						if (n < 0 || n > size - 1) continue;
						
						if (img[i][j] > img[m][n]) sum ++;
						ara ++;
					}
				tmp[i][j] = sum * 256 / ara;
			}

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				pix[k][tmp[i][j] - 1] += 1;

		fwrite(tmp, sizeof(unsigned char), size * size, file_o[k]);
		fclose(file_o[k]);
	}

	for (int n = 0; n < 256; n ++)
		fprintf(data_o, "%d,%d,%d\n", n + 1, pix[0][n], pix[1][n]);
	fclose(data_o);

	return 0;
}