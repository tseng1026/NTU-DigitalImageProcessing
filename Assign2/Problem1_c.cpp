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
	file_o[0] = fopen("E_3-1.raw", "wb");
	file_o[1] = fopen("E_3-2.raw", "wb");
	file_o[2] = fopen("E_3-3.raw", "wb");
	if (file_i[0] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[1] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_i[2] == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[2] == NULL) cout << "Cannot open the writing file!" << endl;

	int T_h = 15, T_l = 10;
	// scanf("%d%d", &T_h, &T_l);

	int hlf = 2;
	int flt[5][5] = {{2, 4, 5, 4, 2},
					{4, 9, 12, 9, 4},
					{5, 12, 15, 12, 5},
					{4, 9, 12, 9, 4},
					{2, 4, 5, 4, 2}};
	
	for (int k = 0; k < 3; k ++){
		unsigned char img[size][size];
		unsigned char tmp[size][size];
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

		int c = 2;
		int grad[size][size];
		for (int i = 1; i < size - 1; i ++)
			for (int j = 1; j < size - 1; j ++){
				double tmpi = 0;
				tmpi += (smo[i][j + 1] - smo[i][j - 1]) * c;
				tmpi += smo[i - 1][j + 1] - smo[i - 1][j - 1];
				tmpi += smo[i + 1][j + 1] - smo[i + 1][j - 1];
				tmpi /= c + 2;

				double tmpj = 0;
				tmpj += (smo[i + 1][j] - smo[i - 1][j]) * c;
				tmpj += smo[i + 1][j - 1] - smo[i - 1][j - 1];
				tmpj += smo[i + 1][j + 1] - smo[i - 1][j + 1];
				tmpj /= c + 2;

				grad[i][j] = sqrt(tmpi * tmpi + tmpj * tmpj);

				if (grad[i][j] < T_l) grad[i][j] = 0;
				if (grad[i][j] > T_h) grad[i][j] = 2;
				if (grad[i][j] <= T_h && grad[i][j] >= T_l) grad[i][j] = 1;
			}

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				if (grad[i][j] == 2) tmp[i][j] = 255;
				if (grad[i][j] == 0) tmp[i][j] = 0;
				if (grad[i][j] == 1){
					int flag = 0;
					for (int m = i - 1; m <= i + 1; m ++)
						for (int n = j - 1; n <= j + 1; n ++){
							if (m < 0 || m > size - 1) continue;
							if (n < 0 || n > size - 1) continue;
							
							if (grad[m][n] == 2) flag = 1;
						}

					if (flag == 1) tmp[i][j] = 255;
					if (flag == 0) tmp[i][j] = 0;
				}
			}

		fwrite(tmp, sizeof(unsigned char), size * size, file_o[k]);
		fclose(file_o[k]);
	}

	return 0;
}