#ifndef utilityFunctions
#define utilityFunctions
void DrawColorBlock(HDC hdc, int startX, int startY, int width, int height, int R, int G, int B) {
    // Create a DIB section for the block
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;    // 32bpp for faster processing
    bmi.bmiHeader.biCompression = BI_RGB;

    // Calculate the color value in 32-bit format (0xAARRGGBB)
    COLORREF color = RGB(R, G, B);
    DWORD dwColor = 0xFF000000 | (GetRValue(color) << 16) | (GetGValue(color) << 8) | GetBValue(color);

    // Create DIB section and fill with the color
    void* pBits;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    
    if (pBits) {
        // Fill the entire bitmap with our color
        DWORD* pPixels = (DWORD*)pBits;
        for (int i = 0; i < width * height; i++) {
            pPixels[i] = dwColor;
        }

        // Create memory DC and select our bitmap
        HDC hMemDC = CreateCompatibleDC(hdc);
        HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hBitmap);
        
        // Blit to the destination
        BitBlt(hdc, startX, startY, width, height, hMemDC, 0, 0, SRCCOPY);

        // Cleanup
        SelectObject(hMemDC, hOldBmp);
        DeleteDC(hMemDC);
    }
    
    DeleteObject(hBitmap);
}
#endif
