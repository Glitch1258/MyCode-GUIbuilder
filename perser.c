#include <windows.h>  // Include Windows API header for GUI programming
#include <stdio.h>
#include "utilityFunctions.h"
#include "FSM.h"
#include "readPixels.h"
// Global variables
HDC hdc;  // Handle to Device Context (used for drawing)
COLORREF currentColor = RGB(255, 0, 0); // Default pixel color (red)
int lastX = 0, lastY = 0; // Stores the last mouse position coordinates
BOOL isDragging = FALSE;   // Flag to track if mouse is being dragged

// Window procedure - handles all messages sent to our window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_LBUTTONDOWN: {  // Left mouse button pressed
            printf("Left mouse button pressed\n");
            // Get mouse coordinates from lParam
            lastX = LOWORD(lParam);  // X coordinate is in low word
            lastY = HIWORD(lParam);  // Y coordinate is in high word
            // Draw a pixel at clicked position with current color
            SetPixel(hdc, lastX, lastY, currentColor);
            // Request window redraw to make pixel visible
            InvalidateRect(hwnd, NULL, FALSE);
            break;
        }
        case WM_MOUSEMOVE: {  // Mouse movement detected
            int x = LOWORD(lParam);  // Current X position
            int y = HIWORD(lParam);  // Current Y position
			lastX = x;
            lastY = y;
            printf("Mouse movement detected (x,y) = (%d,%d) \n",lastX,lastY);
            if (wParam & MK_LBUTTON) { // Check if left button is held down (dragging)
                isDragging = TRUE;
                //int x = LOWORD(lParam);  // Current X position
                //int y = HIWORD(lParam);  // Current Y position
                // Draw pixel at current mouse position
                SetPixel(hdc, x, y, currentColor);
                InvalidateRect(hwnd, NULL, FALSE);
                // Play a beep sound during dragging (500Hz for 50ms)
                Beep(500, 50);
                // Update last position
            } else {
                isDragging = FALSE;
            }
            break;
        }
        case WM_MOUSEWHEEL: {  // Mouse wheel scrolled
            printf("Mouse wheel scrolled\n");
            // Get scroll direction and amount
            short delta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (delta > 0) {
                Beep(800, 50);  // High pitch beep for scrolling up
            } else {
                Beep(400, 50);  // Low pitch beep for scrolling down
            }
            break;
        }
        case WM_KEYDOWN: {  // Keyboard key pressed
			printf("Keyboard key Down\n");
            switch (wParam) {  // Check which key was pressed
                case 'R': currentColor = RGB(255, 0, 0); break; // Change to red
                case 'G': currentColor = RGB(0, 255, 0); break; // Change to green
                case 'B': currentColor = RGB(0, 0, 255); break; // Change to blue
            }
            break;
        }
        case WM_PAINT: {  // Window needs repainting
            PAINTSTRUCT ps;
            // Begin painting operation
            HDC hdcPaint = BeginPaint(hwnd, &ps);
            // Redraw the last pixel to ensure it persists
            SetPixel(hdcPaint, lastX, lastY, currentColor);
            // End painting operation
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:  // Window is being destroyed
            PostQuitMessage(0);  // Send quit message to application
            break;
        default:
            // Handle any messages we didn't process with default behavior
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry point for Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	runFSM();
    // Register window class - defines window properties
    WNDCLASS wc = {0};  // Initialize all fields to zero
    wc.lpfnWndProc = WndProc;  // Set our window procedure
    wc.hInstance = hInstance;  // Set application instance handle
    wc.lpszClassName = "PixelWindowClass";  // Set class name
    RegisterClass(&wc);  // Register the window class with Windows

    // Create actual window using our registered class
    HWND hwnd = CreateWindow(
        "PixelWindowClass",  // Class name
        "Pixel Drawer",      // Window title
        WS_OVERLAPPEDWINDOW, // Standard window style
        CW_USEDEFAULT,       // Default horizontal position
        CW_USEDEFAULT,       // Default vertical position
        800,                 // Width
        600,                // Height
        NULL,                // No parent window
        NULL,               // No menu
        hInstance,          // Application instance
        NULL);              // No additional data

    if (!hwnd) return 1;  // Exit if window creation failed

    // Get the device context for drawing operations
    hdc = GetDC(hwnd);
    // Make the window visible
    ShowWindow(hwnd, nCmdShow);

    // Main message loop - processes all messages for our application
	DrawRedSquare(hdc,boxes[1].positionX, boxes[1].positionY , boxes[1].width , boxes[1].length , boxes[1].R , boxes[1].G , boxes[1].B );
	showImage(hdc , 100 , 200 , 50 , 50);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // Translate virtual-key messages
        DispatchMessage(&msg);   // Send message to our WndProc
    }

    // Clean up: release the device context
    ReleaseDC(hwnd, hdc);
    // Return the exit code from the last message
    return (int)msg.wParam;
}
// gcc perser.c -o perser -lgdi32
