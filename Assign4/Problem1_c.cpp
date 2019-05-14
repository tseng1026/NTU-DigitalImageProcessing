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

	unsigned char img[size * 4][180];
	fread(img, sizeof(unsigned char), (size * 4) * 180, file_i);
	fclose(file_i);

	int pix[size] = {0};
	for (int i = 0; i < size * 4; i ++)
		for (int j = 0; j < 180; j ++)
			pix[img[i][j] - 1] += 1;

	for (int n = 1; n < 256; n ++)
		pix[n] += pix[n - 1];

	for (int i = 0; i < size * 4; i ++)
		for (int j = 0; j < 180; j ++)
			img[i][j] = pix[img[i][j]] / 256;

	fwrite(img, sizeof(unsigned char), (size * 4) * 180, file_o);
	fclose(file_o);

	return 0;
}