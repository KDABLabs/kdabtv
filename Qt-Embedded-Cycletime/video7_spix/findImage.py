import cv2
import numpy as np

# Load the main image and the screenshot image
main_image = cv2.imread('/tmp/reference.png')
screenshot_image = cv2.imread('/tmp/slider.png')

main_gray = cv2.cvtColor(main_image, cv2.COLOR_BGR2GRAY)
screenshot_gray = cv2.cvtColor(screenshot_image, cv2.COLOR_BGR2GRAY)

# Find the screenshot within the main image
result = cv2.matchTemplate(main_gray, screenshot_gray, cv2.TM_CCOEFF_NORMED)
in_val, max_val, min_loc, max_loc = cv2.minMaxLoc(result)

# Get the coordinates of the screenshot within the main image
top_left = max_loc
bottom_right = (top_left[0] + screenshot_image.shape[1], top_left[1] + screenshot_image.shape[0])

# Draw a rectangle around the screenshot in the main image
cv2.rectangle(main_image, top_left, bottom_right, (0, 0, 255), 2)

# Display the result
cv2.imshow('Result', main_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
