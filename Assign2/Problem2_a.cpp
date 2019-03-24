#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

int main(){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("sample4.raw", "rb");
	file_o = fopen("C.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	unsigned char low[size][size];
	unsigned char tmp[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int b = 8;
	// scanf("%d", &b);

	int hlf = 1;
	int flt[3][3] = {{0}};
	flt[0][0] = flt[0][2] = flt[2][0] = flt[2][2] = 1;
	flt[0][1] = flt[1][0] = flt[1][2] = flt[2][1] = b;
	flt[1][1] = b * b;

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			int ara = 0, sum = 0;
			for (int m = i - hlf; m <= i + hlf; m ++)
				for (int n = j - hlf; n <= j + hlf; n ++){
					if (m < 0 || m > size - 1) continue;
					if (n < 0 || n > size - 1) continue;

					sum += img[m][n] * flt[m - i + 1][n - j + 1];
					ara += flt[m - i + 1][n - j + 1];
				}

			low[i][j] = sum / ara;
		}

	double c = 0.65;
	// scanf("%lf", &c);

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			tmp[i][j] = img[i][j] * c - low[i][j] * (1 - c);
			tmp[i][j] = tmp[i][j] / (2 * c - 1);
		}

	fwrite(tmp, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}