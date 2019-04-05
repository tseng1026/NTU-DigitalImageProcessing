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
	file_i = fopen("H_1.raw", "rb");
	file_o = fopen("H_2.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	int flg = 1;
	int pos[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
	while (flg){
		flg = 0;
		for (int i = 1; i < size - 1; i ++)
			for (int j = 1; j < size - 1; j ++){
				if (img[i][j] != 0) continue;

				int nei = 0;
				for (int k = 0; k < 8; k ++)
					nei += img[i + pos[k][0]][j + pos[k][1]] / 255;

				if (nei <= 5) continue;
				img[i][j] = 255;
				flg = 1;
			}

		for (int i = 1; i < size - 1; i ++)
			for (int j = 1; j < size - 1; j ++){
				if (img[i][j] != 255) continue;

				int nei = 0;
				for (int k = 0; k < 8; k ++)
					nei += img[i + pos[k][0]][j + pos[k][1]] / 255;

				if (nei >= 4) continue;
				img[i][j] = 0;
				flg = 1;
			}
	}

	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}