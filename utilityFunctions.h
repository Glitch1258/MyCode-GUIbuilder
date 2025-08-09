#ifndef utilityFunctions
#define utilityFunctions
void DrawRedSquare(HDC hdc, int startX, int startY , int width , int height , int R , int G , int B) {
    COLORREF color = RGB(R, G, B);  // Pure red color
    //int size = 50;                  // Square size (50x50 pixels)
    
    for (int x = 0+startX; x < width+startX ; x++) {
        for (int y = 0+startY; y < height+startY; y++) {
            SetPixel(hdc, x, y, color);  // Draw each pixel in the square
        }
    }
}
#endif
