import numpy as np
import cv2
import sys

from skimage import data
from skimage.restoration import inpaint

filename = sys.argv[1]

for k in range(10):
	img = cv2.imread('../../Defects/Defect_' + filename + str(k) + '.jpg')
	msk = cv2.imread('../../Masks/Mask' + str(k) + '.jpg', 0)

	res = inpaint.inpaint_biharmonic(img, msk, multichannel=True)
	cv2.imwrite('../Results/PatchMatch_' + filename[:-4] + str(k) + '.jpg', res)
	cv2.destroyAllWindows()
