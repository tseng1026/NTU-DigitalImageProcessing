#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256
#define pi 3.141592653589793238463

using namespace std;

int main(){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("C.raw", "rb");
	file_o = fopen("D.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	unsigned char tmp[size][size];
	unsigned char res[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			double tmpi = i - 127.5;
			double tmpj = j - 127.5;
			if (tmpi * tmpi + tmpj * tmpj >= 128 * 128) continue;

			double dim = 0;
			if (abs(tmpi) > abs(tmpj)) dim = tmpi / sqrt(tmpi * tmpi + tmpj * tmpj);
			if (abs(tmpi) <= abs(tmpj)) dim = tmpj / sqrt(tmpi * tmpi + tmpj * tmpj);

			tmpi = tmpi / abs(dim) + 127.5;
			tmpj = tmpj / abs(dim) + 127.5;

			tmp[i][j] = img[int(tmpi)][int(tmpj)];
		}

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			double tmpi = i - 127.5;
			double tmpj = j - 127.5;
			if (tmpi * tmpi + tmpj * tmpj >= 128 * 128) continue;

			double theta = 0.5 * pi * (1 - sqrt(tmpi * tmpi + tmpj * tmpj) / 128);

			double resi = tmpi * cos(theta) - tmpj * sin(theta) + 127.5;
			double resj = tmpi * sin(theta) + tmpj * cos(theta) + 127.5;

			res[i][j] = tmp[int(resi)][int(resj)];
		}

	fwrite(res, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}