import cv2
import numpy as np


def green_contours(image_path):
    image = cv2.imread(image_path)
    image=cv2.resize(image,(500,414))
    if image is None:
        print("Error: Could not open or find the image.")
        return 0

    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    lower_green = np.array([35, 50, 50])
    upper_green = np.array([85, 205, 205])

    mask = cv2.inRange(hsv_image, lower_green, upper_green)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    centroids = []

    for contour in contours:

        M = cv2.moments(contour)
        if M["m00"] != 0:
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])
            centroids.append((cX, cY))

            cv2.circle(image, (cX, cY), 5, (0,0,0), -1)

    cv2.imshow("Image with Centroids", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    return centroids


image_path = 'd:/4.jpg'

centroids = green_contours(image_path)
print("Green block centroids:", centroids)

#该代码应该可以识别严格的绿色，但在识别的同时还会标出一些无用的黑点，不知道如何去除
