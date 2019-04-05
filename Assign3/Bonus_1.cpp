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
	file_i = fopen("sample3.raw", "rb");
	file_o = fopen("H_1.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	int c = 2, T = 45;	// 2, 40 is the best
	// scanf("%d%d", &c, &T);

		unsigned char img[size][size];
		unsigned char tmp[size][size] = {{0}};
		fread(img, sizeof(unsigned char), size * size, file_i);
		fclose(file_i);

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

			}

		fwrite(tmp, sizeof(unsigned char), size * size, file_o);
		fclose(file_o);

	return 0;
}