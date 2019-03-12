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
	file_i = fopen("sample2.raw", "rb");
	file_o = fopen("E.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;

	unsigned char img[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++)
			img[i][j] = img[i][j] / 3;
	
	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);
	return 0;
}