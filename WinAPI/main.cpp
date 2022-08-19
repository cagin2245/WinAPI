
#include <windows.h>
#include <iostream>
#include <glad.h>


int globalRun = 1;

HDC device_context;
HGLRC rendering_context;

LRESULT CALLBACK WindowProc(
    HWND window,
    UINT message,
    WPARAM wParam,
    LPARAM lParam) {
    LRESULT result;
    switch (message)
    {   
    case WM_CLOSE:
    {
        globalRun = 0;
    }break;
    
    case WM_DESTROY:
    {
        ReleaseDC(window, device_context);
        wglDeleteContext(rendering_context);
        PostQuitMessage(0);
        return 0;
    } break;
    default:
    {
        result = DefWindowProc(window, message, wParam, lParam);
    }break;
    }
    return result;
}

INT WINAPI wWinMain(HINSTANCE _In_ instance, HINSTANCE _In_opt_ hPrevInstance, PWSTR _In_ cmdArgs, INT _In_ cmdShow)
{
    WNDCLASS window_class = { 0 };
    wchar_t CLASS_NAME[] = L"Window Class";
    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = CLASS_NAME;

    RegisterClass(&window_class);

    HWND window =  CreateWindowEx( 0,CLASS_NAME,L"Window",WS_OVERLAPPEDWINDOW|WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,instance, 0);
    MSG message;
    while (globalRun)
    {   
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
       
        
    }
        return 0;
}
