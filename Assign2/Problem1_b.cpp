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
	file_o[0] = fopen("E_2-1.raw", "wb");
	file_o[1] = fopen("E_2-2.raw", "wb");
	file_o[2] = fopen("E_2-3.raw", "wb");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[2] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[2] == NULL) cout << "Cannot open the writing file!" << endl;

	int T = 3;		// 3 is the best
	// scanf("%d", &T);

	int hlf = 2;
	int flt[5][5] = {{1, 4, 7, 4, 1},
					{4, 16, 26, 16, 4},
					{7, 26, 41, 26, 7},
					{4, 16, 26, 16, 4},
					{1, 4, 7, 4, 1}};


	for (int k = 0; k < 3; k ++){
		unsigned char img[size][size];
		unsigned char tmp[size][size] = {{0}};
		fread(img, sizeof(unsigned char), size * size, file_i[k]);
		fclose(file_i[k]);

		unsigned char smo[size][size];
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){

				int sum = 0, ara = 0;
				for (int m = i - hlf; m <= i + hlf; m ++)
					for (int n = j - hlf; n <= j + hlf; n ++){
						if (m < 0 || m > size - 1) continue;
						if (n < 0 || n > size - 1) continue;
						
						sum += img[m][n] * flt[m - i + hlf][n - j + hlf];
						ara += flt[m - i + hlf][n - j + hlf];
					}

				smo[i][j] = sum / ara;
			}

		int grad[size][size];
		for (int i = 1; i < size - 1; i ++)
			for (int j = 1; j < size - 1; j ++){
				grad[i][j] += smo[i][j] * 4;
				grad[i][j] += smo[i][j - 1] + smo[i - 1][j];
				grad[i][j] += smo[i][j + 1] + smo[i + 1][j];
				grad[i][j] += smo[i - 1][j - 1] * -2;
				grad[i][j] += smo[i - 1][j + 1] * -2;
				grad[i][j] += smo[i + 1][j - 1] * -2;
				grad[i][j] += smo[i + 1][j + 1] * -2;
				grad[i][j] /= 8;

				if (abs(grad[i][j]) < T) grad[i][j] = 0;
				if (abs(grad[i][j]) >= T) grad[i][j] = grad[i][j];
			}

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				if (grad[i][j] != 0) tmp[i][j] = 255;
				if (grad[i][j] == 0){
					int flag = 0;
					if (i + 2 < size - 1)
						if (grad[i][j] * grad[i + 2][j] < 0) flag = 1;
					
					if (j + 2 < size - 1)
						if (grad[i][j] * grad[i][j + 2] < 0) flag = 1;

					if (flag == 1) tmp[i][j] = 0;
					if (flag == 0) tmp[i][j] = 0;
				}
			}

		fwrite(tmp, sizeof(unsigned char), size * size, file_o[k]);
		fclose(file_o[k]);
	}

	return 0;
}