from skimage import io
from skimage.metrics import structural_similarity as ssim

# Load the two screenshots
screenshot1 = io.imread('/tmp/reference.png', as_gray=True)
screenshot2 = io.imread('/tmp/screenshot.png', as_gray=True)

# Calculate the SSIM index between the two screenshots
ssim_index = ssim(screenshot1, screenshot2, data_range=screenshot1.max() - screenshot1.min())

# Define a threshold value for similarity
threshold = 0.95

# Compare the SSIM index with the threshold
if ssim_index == 1.0: 
    print("The screenshots are identical, similarity: " + str(ssim_index * 100) + "%")
elif ssim_index >= threshold:
    print("The screenshots are similar, similarity: " + str(ssim_index * 100) + "%")
else:
    print("The screenshots are not similar at all, similarity: " + str(ssim_index * 100) + "%")
