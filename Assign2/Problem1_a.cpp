#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

int main(){
	FILE *file_i[3];
	FILE *file_o[3];
	FILE *data_o;
	file_i[0] = fopen("sample1.raw", "rb");
	file_i[1] = fopen("sample2.raw", "rb");
	file_i[2] = fopen("sample3.raw", "rb");
	file_o[0] = fopen("E_1-1.raw", "wb");
	file_o[1] = fopen("E_1-2.raw", "wb");
	file_o[2] = fopen("E_1-3.raw", "wb");
	data_o = fopen("Problem1_a.csv", "wb");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[2] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[2] == NULL) cout << "Cannot open the writing file!" << endl;
	if (data_o == NULL) cout << "Cannot open the writing file!" << endl;

	int c = 2, T = 40;	// 2, 40 is the best
	// scanf("%d%d", &c, &T);

	int pix[3][256] = {{0}};
	for (int k = 0; k < 3; k ++){
		unsigned char img[size][size];
		unsigned char tmp[size][size] = {{0}};
		fread(img, sizeof(unsigned char), size * size, file_i[k]);
		fclose(file_i[k]);

		for (int i = 1; i < size - 1; i ++)
			for (int j = 1; j < size - 1; j ++){
				double tmpi = 0;
				tmpi += (img[i][j + 1] - img[i][j - 1]) * c;
				tmpi += img[i - 1][j + 1] - img[i - 1][j - 1];
				tmpi += img[i + 1][j + 1] - img[i + 1][j - 1];
				tmpi /= c + 2;

				double tmpj = 0;
				tmpj += (img[i + 1][j] - img[i - 1][j]) * c;
				tmpj += img[i + 1][j - 1] - img[i - 1][j - 1];
				tmpj += img[i + 1][j + 1] - img[i - 1][j + 1];
				tmpj /= c + 2;

				int grad = sqrt(tmpi * tmpi + tmpj * tmpj);
				if (grad > T) tmp[i][j] = 255;
				if (grad <= T) tmp[i][j] = 0;

				pix[k][grad] += 1;
			}

		fwrite(tmp, sizeof(unsigned char), size * size, file_o[k]);
		fclose(file_o[k]);

		// for (int n = 1; n < 256; n ++)
		// 	pix[k][n] += pix[k][n - 1];
	}

	for (int n = 0; n < 256; n ++)
		fprintf(data_o, "%d,%d,%d,%d\n", n + 1, pix[0][n], pix[1][n], pix[2][n]);
	fclose(data_o);
	return 0;
}