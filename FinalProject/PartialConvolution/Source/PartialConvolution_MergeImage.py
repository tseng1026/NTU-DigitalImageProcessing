import numpy as np
import cv2
import sys

sze = 256
res = np.zeros((256 * 6, 256 * 10, 3))
filename = sys.argv[1]

img = cv2.imread(filename, 0)
for k in range(10):
	res[sze*0:sze*1, sze*k:sze*(k+1)] = cv2.imread('../../Defects/Defect_' + filename[:-4] + str(k) + '.jpg')
	res[sze*1:sze*2, sze*k:sze*(k+1)] = cv2.imread('../Results/PartialConvolution_Iter10_'    + filename[:-4] + str(k) + '.jpg')
	res[sze*2:sze*3, sze*k:sze*(k+1)] = cv2.imread('../Results/PartialConvolution_Iter100_'   + filename[:-4] + str(k) + '.jpg')
	res[sze*3:sze*4, sze*k:sze*(k+1)] = cv2.imread('../Results/PartialConvolution_Iter1000_'  + filename[:-4] + str(k) + '.jpg')
	res[sze*4:sze*5, sze*k:sze*(k+1)] = cv2.imread('../Results/PartialConvolution_Iter10000_' + filename[:-4] + str(k) + '.jpg')
	res[sze*5:sze*6, sze*k:sze*(k+1)] = cv2.imread('../Results/PartialConvolution_Iter50000_' + filename[:-4] + str(k) + '.jpg')

cv2.imwrite('../Results/PartialConvolution_' + filename[:-4] + '.jpg', res)