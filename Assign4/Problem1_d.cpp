#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define size 256
#define pi 3.14159265

using namespace std;

int col[20][3] = {
	{255, 250, 250},
	{255, 0, 0},
	{255, 153, 18}, 
	{255, 215, 0},
	{124, 252, 0}, 
	{75, 113, 197},
	{135, 206, 235},
	{138, 43, 226},
	{255, 192, 203},
	{233, 46, 208}, 
	{128, 125, 125},
	{200, 0, 0},
	{128, 75, 10}, 
	{128, 105, 0},
	{75, 126, 0}, 
	{36, 55, 98},
	{68, 103, 106},
	{70, 21, 113},
	{128, 96, 100},
	{111, 25, 100}};

int main(){
	FILE *file_i;
	FILE *file_o[2];
	file_i = fopen("H_1.raw", "rb");
	// data_i = fopen("H_2.raw", "rb");
	file_o[0] = fopen("D_1.raw", "wb");
	file_o[1] = fopen("D_2.raw", "wb");
	if (file_i == NULL) cout << "Cannot open the reading file!" << endl;
	if (file_o[0] == NULL) cout << "Cannot open the writing file!" << endl;
	if (file_o[1] == NULL) cout << "Cannot open the writing file!" << endl;

	double sink[180];
	double cosk[180];
	for (int k = 0; k < 180; k ++){
		sink[k] = sin(k * pi / 180);
		cosk[k] = cos(k * pi / 180);
	}

	unsigned char img[size * 4][180];
	fread(img, sizeof(unsigned char), (size * 4) * 180, file_i);
	fclose(file_i);

	vector< pair <int,pair<int,int> > >vect;
	for (int i = 0; i < size * 4; i ++)
		for (int j = 0; j < 180; j ++)
			vect.push_back(make_pair(img[i][j], make_pair(i, j)));

	sort(vect.begin(), vect.end());
	reverse(vect.begin(), vect.end());

	for (int n = 0; n < 2; n ++){
		unsigned char tmp[size][size][3] = {{{0}}};
		for (int k = 0; k < 10 * (n + 1); k ++){
			int value = vect[k].second.first - size * 2;
			int theta = vect[k].second.second;

			for (int i = 0; i < size; i ++)
				for (int j = 0; j < size; j ++){
					if (tmp[i][j][0] + tmp[i][j][1] + tmp[i][j][2] != 0) continue;

					if (value == int(i * sink[theta] + j * cosk[theta])){
						tmp[i][j][0] = col[k][0];
						tmp[i][j][1] = col[k][1];
						tmp[i][j][2] = col[k][2];
					}
				}
		}

		fwrite(tmp, sizeof(unsigned char), size * size * 3, file_o[n]);
		fclose(file_o[n]);
	}

	return 0;
}