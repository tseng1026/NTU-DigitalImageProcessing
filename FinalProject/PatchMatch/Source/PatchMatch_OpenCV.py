import numpy as np
import cv2
import sys

filename = sys.argv[1]

for k in range(10):
	img = cv2.imread('../../' + filename, 0)					### color scale (RGB)
	msk = cv2.imread('../../Masks/Mask' + str(k) + '.jpg', 0)	### gray scale

	resNS = cv2.inpaint(img, msk, 10, cv2.INPAINT_NS)
	resTE = cv2.inpaint(img, msk, 10, cv2.INPAINT_TELEA)

	cv2.imwrite('../Results/Gray_PatchMatch_NS_' + filename[:-4] + str(k) + '.jpg', resNS)
	cv2.imwrite('../Results/Gray_PatchMatch_TE_' + filename[:-4] + str(k) + '.jpg', resTE)
	cv2.destroyAllWindows()