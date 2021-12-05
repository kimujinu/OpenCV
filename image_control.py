import cv2

img_color = cv2.imread("ryan_transparent.png",cv2.IMREAD_COLOR)

cv2.namedWindow("Show Image")
cv2.imshow("show Image",img_color)

cv2.waitKey(0)

img_gray = cv2.cvtColor(img_color,cv2.COLOR_BGR2GRAY)

cv2.imshow('show grayimage',img_gray)
cv2.waitKey(0)

cv2.imwrite('save_img.png',img_gray)

cv2.destroyAllWindows()