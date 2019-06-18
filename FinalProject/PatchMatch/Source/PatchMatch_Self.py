import numpy as np
import cv2
import sys
import operator

### Compute the OSNR of two Patches
def psnr(ori, com, win):
	mse = 0
	for i in range(win):
		for j in range(win):
			arr  = (ori[i][j] - com[i][j]) ** 2 / (win ** 2)
			mse += np.sum(arr)
	return mse

### Check the Reliable of Patch
def chck(msk, win):
	cnt = 0
	for i in range(win):
		for j in range(win):
			if msk[i][j] < 128: cnt += 1
	return cnt

### Fill the unfilled Pixels via Similar Patch
def fill(pos, img, oriv, comv, win):
	res = np.copy(oriv[0])
	for i in range(win):
		for j in range(win):
			if oriv[1][i][j] < 128: continue
			if comv[1][i][j] > 128: continue
			res[i][j] = comv[0][i][j]
	img[pos[0]:pos[0] + win, pos[1]:pos[1] + win] = np.copy(res)
	return img


filename = sys.argv[1]

for k in range(10):
	img = cv2.imread('../../Defects/Defect_' + filename[:-4] + str(k) + '.jpg')
	msk = cv2.imread('../../Masks/Mask' + str(k) + '.jpg', 0)
	thr = 200
	rad = 20
	win = 41

	cnt = 0
	while True:
		### List all Patch
		mat = {}
		for i in range(256 - win + 1):
			for j in range(256 - win + 1):
				tmp_img = img[i:i+win, j:j+win]
				tmp_msk = msk[i:i+win, j:j+win]

				if chck(tmp_msk, win) == win ** 2: cnt += 1
				if chck(tmp_msk, win) < win ** 2 * 0.99: continue
				mat[(i,j)] = [tmp_img, tmp_msk]
		if cnt == (256 - win) ** 2: break
		print ("[DONE] Finish Listing all Patch", len(mat))

		### Compute PSNR
		for orik, oriv in mat.items():
			for comk, comv in mat.items():
				if orik == comk: continue
				
				if psnr(oriv[0], comv[0], win) > 300: continue
				img = fill(orik, img, oriv, comv, win)
				break
		print ("[DONE] Finish Computing PSNR")

	cv2.imwrite('../Results/PatchMatch_' + filename[:-4] + str(k) + '.jpg', img)
