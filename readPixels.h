


/*
int showImage(HDC hdc ,char * path,int scaleX , int scaleY , int moveX , int moveY) {

    int width, height, channels;
    
    // Load the JPEG image (automatically converts to RGB)
    unsigned char *image = stbi_load(path, &width, &height, &channels, 0);
    
    if (!image) {
        printf("Error: Could not load image!\n");
        return 1;
    }

    // Print image info
    printf("Image loaded: %d x %d pixels, %d channels (RGB)\n", width, height, channels);

    // Loop through all pixels
    for (int y = 0 ; y < height ; y++) {
        for (int x = 0 ; x < width ; x++) {
            // Calculate the index for the current pixel
            int index = (y * width + x) * channels;      
            // Get RGB values
            unsigned char r = image[index];
            unsigned char g = image[index + 1];
            unsigned char b = image[index + 2];
			COLORREF color = RGB(r, g, b);
			float floX = x ;
			float floY = y ;
			floX = (floX/ width)*scaleX;
			floY = (floY/ height)*scaleY;
			//printf("(floX = %d , floY = %d )",(int)floX,(int)floY);
			

			SetPixel(
					hdc,
					moveX+(int)floX,
					moveY+(int)floY,
					color
					);
            // Print pixel coordinates and RGB values
            //printf("Pixel at (%d, %d): R=%3d, G=%3d, B=%3d\n", x, y, r, g, b);
        }
    }

    // Free the image memory when done
    stbi_image_free(image);
    return 0;
}
*/

int showImage(HDC hdc, char* path, int scaleX, int scaleY, int moveX, int moveY) {
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, STBI_rgb); // Force RGB format
    
    if (!image) return 1;

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;    // 24bpp RGB
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    
    // Convert image data to DIB format (BGR)
    BYTE* pDibBits = (BYTE*)pBits;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIdx = (y * width + x) * channels;
            int dstIdx = (y * width + x) * 3;
            
            // Handle different source formats
            if (channels >= 3) {
                // RGB(A) source - note Windows DIB expects BGR order
                pDibBits[dstIdx]     = image[srcIdx + 2]; // B
                pDibBits[dstIdx + 1] = image[srcIdx + 1]; // G
                pDibBits[dstIdx + 2] = image[srcIdx];     // R
            } else if (channels == 1) {
                // Grayscale - replicate to all channels
                pDibBits[dstIdx] = pDibBits[dstIdx + 1] = pDibBits[dstIdx + 2] = image[srcIdx];
            }
        }
    }

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hBitmap);
    
    // Use high-quality stretching if needed
    SetStretchBltMode(hdc, HALFTONE);
    StretchBlt(hdc, moveX, moveY, scaleX, scaleY, 
              hMemDC, 0, 0, width, height, SRCCOPY);

    // Cleanup
    SelectObject(hMemDC, hOldBmp);
    DeleteDC(hMemDC);
    DeleteObject(hBitmap);
    stbi_image_free(image);
    return 0;
}
