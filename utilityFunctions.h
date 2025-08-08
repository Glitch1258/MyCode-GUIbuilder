#ifndef utilityFunctions
#define utilityFunctions
void DrawRedSquare(HDC hdc, int startX, int startY , int width , int height , int R , int G , int B) {
    COLORREF color = RGB(R, G, B);   
    for (int x = 0+startX; x < width+startX ; x++) {
        for (int y = 0+startY; y < height+startY; y++) {
            SetPixel(hdc, x, y, color); 
        }
    }
}
#endif
