#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>

#define size 512

using namespace std;

int distant(unsigned char fea[9], int avg[9], int wei[9]){
	int tot = 0;
	for (int k = 0; k < 9; k ++)
		tot += (fea[k] - avg[k]) * (fea[k] - avg[k]) * wei[k];
	return int(sqrt(tot / 18));
}

int main(int argc, char **argv){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("sample2.raw", "rb");
	file_o = fopen("E.raw", "w");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;	

	unsigned char img[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int hlf = 1;
	int wei[9] = {1, 1, 1, 1, 10, 1, 1, 1, 1};
	int div[9] = {36, 12, 12, 12, 4, 4, 12, 4, 12};
	int flt[9][3][3] = {{{1, 2, 1}, {2, 4, 2}, {1, 2, 1}},
						{{1, 0, -1}, {2, 0, -2}, {1, 0, -1}},
						{{-1, 2, -1}, {-2, 4, -2}, {-1, 2, -1}},
						{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}},
						{{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}},
						{{-1, 2, -1}, {0, 0, 0}, {1, -2, 1}},
						{{-1, -2, -1}, {2, 4, 2}, {-1, -2, -1}},
						{{-1, 0, 1}, {2, 0, -2}, {-1, 0, 1}},
						{{1, -2, 1}, {-2, 4, -2}, {1, -2, 1}}};

	// convolution
	unsigned char tmp[size][size][9];
	for (int k = 0; k < 9; k ++)
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				int sum = 0;
				for (int m = i - hlf; m <= i + hlf; m ++)
					for (int n = j - hlf; n <= j + hlf; n ++){
						int tmpm = m;
						int tmpn = n;
						if (m < 0) tmpm = m * -1;
						if (n < 0) tmpn = n * -1;
						if (m > size - 1) tmpm = size - 1 - (m - size + 1);
						if (n > size - 1) tmpn = size - 1 - (n - size + 1);

						sum += img[tmpm][tmpn] * flt[k][m - i + hlf][n - j + hlf];
					}

				tmp[i][j][k] = sum / div[k];
			}

	// energy computation
	hlf = 18;
	// scanf("%d", &hlf);
	
	unsigned char res[size][size][9];
	for (int k = 0; k < 9; k ++){
		int max = 0;
		int min = 2147483647;
		int pos[size][size] = {{0}};
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){

				int sum = 0, ara = 0;
				for (int m = i - hlf; m <= i + hlf; m ++)
					for (int n = j - hlf; n <= j + hlf; n ++){
						int tmpm = m;
						int tmpn = n;
						if (m < 0) tmpm = m * -1;
						if (n < 0) tmpn = n * -1;
						if (m > size - 1) tmpm = size - (m - size);
						if (n > size - 1) tmpn = size - (n - size);
						
						sum += tmp[tmpm][tmpn][k] * tmp[tmpm][tmpn][k];
						ara ++;
					}
				pos[i][j] = sqrt(sum / ara);
				if (pos[i][j] > max) max = pos[i][j];
				if (pos[i][j] < min) min = pos[i][j];
			}

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				res[i][j][k] = (pos[i][j] - min) * 255 / (max - min);
	}

	// k-means k = 4
	int avg[4][9] = {{0}};
	copy(res[128][128], res[128][128] + 9, avg[0]);
	copy(res[128][385], res[128][385] + 9, avg[1]);
	copy(res[385][128], res[385][128] + 9, avg[2]);
	copy(res[385][385], res[385][385] + 9, avg[3]);

	int flg = 1;
	unsigned char grp[size][size];
	while (flg){
		flg = 0;
		int cal[4][9] = {{0}}, ara[4] = {0};
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				int ind = -1;
				int min = 2147483647;
				for (int n = 0; n < 4; n ++){
					int dis = distant(res[i][j], avg[n], wei);
					if (min > dis) min = dis, ind = n;
				}
				cal[ind][0] += res[i][j][0];
				cal[ind][1] += res[i][j][1];
				cal[ind][2] += res[i][j][2];
				cal[ind][3] += res[i][j][3];
				cal[ind][4] += res[i][j][4];
				cal[ind][5] += res[i][j][5];
				cal[ind][6] += res[i][j][6];
				cal[ind][7] += res[i][j][7];
				cal[ind][8] += res[i][j][8];
				ara[ind] += 1;

				if (grp[i][j] != ind) flg = 1;
				grp[i][j] = ind;
			}

		for (int n = 0; n < 4; n ++)
			for (int k = 0; k < 9; k ++)
				avg[n][k] = cal[n][k] / ara[n];

		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++)
				img[i][j] = grp[i][j] * 60;
	}

	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}