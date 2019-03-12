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
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);

	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size / 2; j ++)
			swap(img[i][j], img[i][size - j - 1]);
	
	fwrite(img, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);
	return 0;
}