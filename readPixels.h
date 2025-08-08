#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>

int showImage(HDC hdc , int scaleX , int scaleY , int moveX , int moveY) {

    int width, height, channels;
    
    // Load the JPEG image (automatically converts to RGB)
    unsigned char *image = stbi_load("test.jpg", &width, &height, &channels, 0);
    
    if (!image) {
        printf("Error: Could not load image!\n");
        return 1;
    }

    // Print image info
    //printf("Image loaded: %d x %d pixels, %d channels (RGB)\n", width, height, channels);

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
//gcc read_jpeg_simple.c -o read_jpeg_simple.exe
