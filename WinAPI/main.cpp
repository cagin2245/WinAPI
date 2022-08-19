
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
    case WM_CREATE:
    {
        PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
    1,                     // version number 
    PFD_DRAW_TO_WINDOW |   // support window 
    PFD_SUPPORT_OPENGL |   // support OpenGL 
    PFD_DOUBLEBUFFER,      // double buffered 
    PFD_TYPE_RGBA,         // RGBA type 
    24,                    // 24-bit color depth 
    0, 0, 0, 0, 0, 0,      // color bits ignored 
    0,                     // no alpha buffer 
    0,                     // shift bit ignored 
    0,                     // no accumulation buffer 
    0, 0, 0, 0,            // accum bits ignored 
    32,                    // 32-bit z-buffer     
    0,                     // no stencil buffer 
    0,                     // no auxiliary buffer 
    PFD_MAIN_PLANE,        // main layer 
    0,                     // reserved 
    0, 0, 0                // layer masks ignored 
        };
        device_context = GetDC(window);
        int  pf = ChoosePixelFormat(device_context, &pfd); //pixel_format
        SetPixelFormat(device_context, pf, &pfd);
        rendering_context = wglCreateContext(device_context);
        wglMakeCurrent(device_context, rendering_context);
        gladLoadGL();
        glViewport(0, 0, 640, 480);
        //MessageBoxA(0, glGetString(GL_VERSION), "OPENGL VERSION", 0);
        return 0;

    }break;/*
    case WM_CLOSE:
    {
        globalRun = 0;
    }break;
    */
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
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapBuffers(device_context);
        
    }
        return 0;
}
