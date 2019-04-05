#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256

using namespace std;

unsigned char img[size][size];

void background(int i, int j){
	for (int m = -1; m <= 1; m ++)
		for (int n = -1; n <= 1; n ++){
			if (m * n != 0) continue; 
			if (i + m < 0 || i + m > 255) continue;
			if (j + n < 0 || j + n > 255) continue;

			if (img[i + m][j + n] == 0){
				img[i + m][j + n] = 255;
				background(i + m, j + n);
			}
		}

	return;
}

void calculate(int i, int j){
	for (int m = -1; m <= 1; m ++)
		for (int n = -1; n <= 1; n ++){
			if (m * n != 0) continue; 
			if (i + m < 0 || i + m > 255) continue;
			if (j + n < 0 || j + n > 255) continue;

			if (img[i + m][j + n] == 0){
				img[i + m][j + n] = 255;
				calculate(i + m, j + n);
			}
		}

	return;
}

int main(){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("H_2.raw", "rb");
	file_o = fopen("H_3.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int flg = 1;
	int pos[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
	while (flg){
		flg = 0;
		unsigned char tmp[size][size] = {{0}};

		for (int step = 0; step < 2; step ++){
			int chg = 0;

			for (int i = 1; i < size - 1; i ++)
				for (int j = 1; j < size - 1; j ++){
					if (img[i][j] != 255) continue;

					int nei = 0;
					int num = 0, pre = img[i + pos[7][0]][j + pos[7][1]];
					int fir[2] = {1, 1};
					int sec[2] = {1, 1};
					for (int k = 0; k < 8; k ++){
						int pix = img[i + pos[k][0]][j + pos[k][1]];
						if (pix != 255) pix = 0;
						if (pix == 255 && pre == 0) num ++;
						pre = pix;

						nei += pix / 255;
						if (k == 0 || k == 2 || k == 4) fir[0] *= pix / 255;
						if (k == 2 || k == 4 || k == 6) sec[0] *= pix / 255;
						if (k == 0 || k == 2 || k == 6) fir[1] *= pix / 255;
						if (k == 0 || k == 4 || k == 6) sec[1] *= pix / 255;
					}

					if (num != 1) continue;
					if (nei <= 2 || nei >= 7) continue;
					if (fir[step] != 0 || sec[step] != 0) continue;
					tmp[i][j] = 1;
					flg = chg = 1;
				}

			if (chg != 0)
				for (int i = 0; i < size; i ++)
					for (int j = 0; j < size; j ++)
						if (tmp[i][j] == 1) img[i][j] = 0;
		}
	}

	img[206][103] = 0;
	background(0, 0);

	flg = 1;
	int cnt = 0;
	while (flg){
		flg = 0;
		for (int i = 0; i < size; i ++)
			for (int j = 0; j < size; j ++){
				if (img[i][j] != 0) continue;

				calculate(i, j);
				flg = 1;
				cnt ++;
			}
	}
	printf("There are %d berries in the image!\n", cnt);

	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);
	return 0;
}