import cv2

# Load the two images
image1 = cv2.imread('/tmp/reference.png')
image2 = cv2.imread('/tmp/screenshot.png')

# Compute the absolute difference between the two images
diff = cv2.absdiff(image1, image2)

# Convert the difference image to grayscale
gray = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)

# Threshold the grayscale image to get a binary image
_, thresh = cv2.threshold(gray, 30, 255, cv2.THRESH_BINARY)

# Find contours in the binary image
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Draw contours on the original image
cv2.drawContours(image1, contours, -1, (0, 0, 255), 2)

# Display the result
cv2.imshow('Difference Image', image1)
cv2.waitKey(0)
