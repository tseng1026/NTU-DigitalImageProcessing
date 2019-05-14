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
	file_i = fopen("sample1.raw", "rb");
	file_o = fopen("E.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	int T_h = 48, T_l = 45;
	// scanf("%d%d", &T_h, &T_l);

	int hlf = 1;
	int flt[3][3] = {{1, 3, 1},
					 {3, 9, 3},
					 {1, 3, 1}};
	
	unsigned char img[size][size];
	unsigned char tmp[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	unsigned char smth[size][size];
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

			smth[i][j] = sum / ara;
		}

	int c = 2;
	double grad[size][size];
	for (int i = 1; i < size - 1; i ++)
		for (int j = 1; j < size - 1; j ++){
			double tmpi = 0;
			tmpi += (smth[i][j + 1] - smth[i][j - 1]) * c;
			tmpi += smth[i - 1][j + 1] - smth[i - 1][j - 1];
			tmpi += smth[i + 1][j + 1] - smth[i + 1][j - 1];
			tmpi /= c + 2;

			double tmpj = 0;
			tmpj += (smth[i + 1][j] - smth[i - 1][j]) * c;
			tmpj += smth[i + 1][j - 1] - smth[i - 1][j - 1];
			tmpj += smth[i + 1][j + 1] - smth[i - 1][j + 1];
			tmpj /= c + 2;

			grad[i][j] = sqrt(tmpi * tmpi + tmpj * tmpj);
		}

	int dir[8][4] = {{1, 1, -1, -1}, {1, 0, -1, 0}, {1, -1, -1, 1}, {0, 1, 0, -1}, 
					 {-1, 1, 1, -1}, {-1, 0, 1, 0}, {-1, -1, 1, 1}, {0, -1, 0, 1}};
	
	double nmax[size][size] = {{0}};
	for (int i = 1; i < size - 1; i ++)
		for (int j = 1; j < size - 1; j ++)
			for (int k = 0; k < 8; k ++){
				double tmp1 = grad[i + dir[k][0]][j + dir[k][1]] - grad[i][j];
				double tmp2 = grad[i + dir[k][2]][j + dir[k][3]] - grad[i][j];
				if (tmp1 * tmp2 > 0) nmax[i][j] = grad[i][j];
			}

	for (int i = 1; i < size - 1; i ++)
		for (int j = 1; j < size - 1; j ++){
			if (nmax[i][j] < T_l) nmax[i][j] = 0;
			if (nmax[i][j] > T_h) nmax[i][j] = 2;
			if (nmax[i][j] <= T_h && nmax[i][j] >= T_l) nmax[i][j] = 1;
		}

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			if (nmax[i][j] == 2) tmp[i][j] = 255;
			if (nmax[i][j] == 0) tmp[i][j] = 0;
			if (nmax[i][j] == 1){
				int flag = 0;
				for (int m = i - 1; m <= i + 1; m ++)
					for (int n = j - 1; n <= j + 1; n ++){
						if (m < 0 || m > size - 1) continue;
						if (n < 0 || n > size - 1) continue;
						
						if (nmax[m][n] == 2) flag = 1;
					}

				if (flag == 1) tmp[i][j] = 255;
				if (flag == 0) tmp[i][j] = 0;
			}
		}

	fwrite(tmp, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}