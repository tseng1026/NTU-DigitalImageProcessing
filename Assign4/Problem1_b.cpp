#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>

#define size 256
#define pi 3.14159265

using namespace std;

int main(){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("E.raw", "rb");
	file_o = fopen("H_1.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	double sink[180];
	double cosk[180];
	for (int k = 0; k < 180; k ++){
		sink[k] = sin(k * pi / 180);
		cosk[k] = cos(k * pi / 180);
	}

	unsigned char img[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	unsigned char tmp[size * 4][180] = {{0}};
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			if (img[i][j] == 0) continue;

			for (int k = 0; k < 180; k ++){
				int value = int(i * sink[k] + j * cosk[k]);
				tmp[value + size * 2][k] ++;
			}
		}

	fwrite(tmp, sizeof(unsigned char), (size * 4) * 180, file_o);
	fclose(file_o);

	return 0;
}