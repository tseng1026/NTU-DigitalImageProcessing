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
	file_o = fopen("B.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	unsigned char tmp[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	for (int i = 1; i < size - 1; i ++)
		for (int j = 1; j < size - 1; j ++){
			if (img[i][j] == 0) continue;

			if (img[i + 1][j + 1] != 255 || img[i + 1][j] != 255 || 
				img[i - 1][j + 1] != 255 || img[i - 1][j] != 255 ||
				img[i + 1][j - 1] != 255 || img[i][j - 1] != 255 ||
				img[i - 1][j - 1] != 255 || img[i][j + 1] != 255) tmp[i][j] = 255;
		}

	fwrite(tmp, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);
	return 0;
}