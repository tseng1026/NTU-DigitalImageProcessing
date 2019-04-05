#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>

#define size 512

using namespace std;

int main(int argc, char **argv){
	FILE *file_i;
	FILE *file_o;
	file_i = fopen("E.raw", "rb");
	file_o = fopen("G.raw", "w");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o == NULL) cout << "Cannot open the writing file!" << endl;	

	unsigned char img[size][size];
	unsigned char tmp[size][size];
	fread(img, sizeof(unsigned char), size * size, file_i);
	fclose(file_i);
	
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++){
			if (img[i][j] == 60) tmp[i][j] = 40;
			if (img[i][j] == 60 && i % 16 == 0) tmp[i][j] = 80; 
			if (img[i][j] == 60 && j % 16 == 1) tmp[i][j] = 80; 

			if (img[i][j] == 120) tmp[i][j] = 100;
			if (img[i][j] == 120 && i / 16 % 2 + j / 16 % 2 == 1) tmp[i][j] = 135;

			if (img[i][j] == 180 && (i + j) / 16 % 2 == 0) tmp[i][j] = 160;
			if (img[i][j] == 180 && (i + j) / 16 % 2 == 1) tmp[i][j] = 225;
		}

	fwrite(tmp, sizeof(unsigned char), size * size, file_o);
	fclose(file_o);

	return 0;
}