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
	file_o = fopen("D_1.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int num = 3;
	// scanf("%d", &num);

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

					// 4 conditions
					int nei = 0;
					int num = 0, pre = img[i + pos[7][0]][j + pos[7][1]];
					int fir[2] = {1, 1};
					int sec[2] = {1, 1};
					for (int k = 0; k < 8; k ++){
						int pix = img[i + pos[k][0]][j + pos[k][1]];
						if (pix == 255 && pre == 0) num ++;
						pre = pix;

						nei += pix / 255;
						if (k == 0 || k == 2 || k == 4) fir[0] *= pix / 255;
						if (k == 2 || k == 4 || k == 6) sec[0] *= pix / 255;
						if (k == 0 || k == 2 || k == 6) fir[1] *= pix / 255;
						if (k == 0 || k == 4 || k == 6) sec[1] *= pix / 255;
					}

					// mark the potential pixel
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
		num --;
		if (num == 0) break;
	}

	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);
	return 0;
}