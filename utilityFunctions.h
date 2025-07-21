#ifndef utilityFunctions
#define utilityFunctions
void DrawRedSquare(HDC hdc, int startX, int startY) {
    COLORREF red = RGB(255, 0, 0);  // Pure red color
    int size = 50;                  // Square size (50x50 pixels)
    
    for (int x = startX; x < startX + size; x++) {
        for (int y = startY; y < startY + size; y++) {
            SetPixel(hdc, x, y, red);  // Draw each pixel in the square
        }
    }
}
#endif