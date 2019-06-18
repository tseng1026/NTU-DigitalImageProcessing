import numpy as np
import cv2
import sys

sze = 256
res = np.zeros((256 * 6, 256 * 10, 3))
filename = sys.argv[1]

img = cv2.imread(filename, 0)
for k in range(10):
	res[sze*0:sze*1, sze*k:sze*(k+1)] = cv2.imread('../../Defects/Defect_Gray_' + filename[:-4] + str(k) + '.jpg')
	res[sze*1:sze*2, sze*k:sze*(k+1)] = cv2.imread('../Results/PatchMatch_NS_Gray_' + filename[:-4] + str(k) + '.jpg')
	res[sze*2:sze*3, sze*k:sze*(k+1)] = cv2.imread('../Results/PatchMatch_TE_Gray_' + filename[:-4] + str(k) + '.jpg')
	
	res[sze*3:sze*4, sze*k:sze*(k+1)] = cv2.imread('../../Defects/Defect_' + filename[:-4] + str(k) + '.jpg')
	res[sze*4:sze*5, sze*k:sze*(k+1)] = cv2.imread('../Results/PatchMatch_NS_Color_' + filename[:-4] + str(k) + '.jpg')
	res[sze*5:sze*6, sze*k:sze*(k+1)] = cv2.imread('../Results/PatchMatch_TE_Color_' + filename[:-4] + str(k) + '.jpg')

cv2.imwrite('../Results/PatchMatch_' + filename[:-4] + '.jpg', res)