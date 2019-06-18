import numpy as np
import cv2
import sys

filename = sys.argv[1]

### Black Mask
for k in range(10):
	img = cv2.imread(filename)
	msk = cv2.imread('../Black/Mask' + str(k) + '.jpg')
	bad = cv2.addWeighted(img, 1, msk, 1, 0)
	cv2.imwrite('../Defects/Defect_' + filename[:-4] + str(k) + '.jpg', bad)

'''
### White Mask
for k in range(10):
	img = cv2.imread(filename)
	msk = cv2.imread('./White/Msk' + str(k) + '.jpg')
	bad = cv2.addWeighted(img, 1, msk, 1, -255)
	
	cv2.imwrite('../Defects/Defect_' + filename[:-4] + str(k) + '.jpg', bad)
'''