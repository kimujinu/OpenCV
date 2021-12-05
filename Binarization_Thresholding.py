# 이진화 : GrayScale 이미지를 흰색과 검은색으로 구성된 바이너리 이미지로 바꾸는 것
# 영상처리 알고리즘을 적용하기 전 전처리 단계로 사용됨.
# 이진화를 배경과 객체를 분리하는데 사용하는데 쓰일수 있음.

import cv2

def nothing(x):
    pass

cv2.namedWindow('Binary')
cv2.createTrackbar('threshold','Binary',0,255, nothing)
cv2.setTrackbarPos('threshold','Binary',127)

img_color = cv2.imread('LenaRGB.bmp',cv2.IMREAD_COLOR)

cv2.imshow('Color',img_color)
cv2.waitKey(0)

img_gray = cv2.cvtColor(img_color,cv2.COLOR_BGR2GRAY)

cv2.imshow('Gray',img_gray)
cv2.waitKey(0)

while True:
    low = cv2.getTrackbarPos('threshold','Binary')
    ret,img_binary = cv2.threshold(img_gray,low,255,cv2.THRESH_BINARY)

    cv2.imshow('Binary',img_binary)

    img_result = cv2.bitwise_and(img_color,img_color,mask=img_binary)

    cv2.imshow('Result',img_result)
    if cv2.waitKey(0)&0xFF == 27:
        break

cv2.destroyAllWindows()