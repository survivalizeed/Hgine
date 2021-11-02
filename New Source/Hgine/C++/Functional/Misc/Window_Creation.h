

#include "../../../Includes.h"

namespace sur
{

    namespace details
    {

        inline LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            switch (msg)
            {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                exit(0);
                break;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            return 0;
        }
    }

    inline void wndCreate(std::string_view name, int params)
    {
        auto win = [&](HWND* window_hwnd)
        {
            HINSTANCE hInstance = GetModuleHandle(0);
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            ULONG_PTR gdiplusToken;
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
            MSG Msg;
            _window_class.cbSize = sizeof(WNDCLASSEX);
            _window_class.style = 0;
            _window_class.lpfnWndProc = details::WndProc;
            _window_class.cbClsExtra = 0;
            _window_class.cbWndExtra = 0;
            _window_class.hInstance = hInstance;
            _window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            _window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
            _window_class.lpszMenuName = NULL;
            _window_class.lpszClassName = L"CLASS";
            _window_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
            RegisterClassEx(&_window_class);
            SetWindowLong(*window_hwnd, GWL_STYLE, GetWindowLong(*window_hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
            *window_hwnd = CreateWindowEx(
                WS_EX_CLIENTEDGE, L"CLASS", std::wstring(name.begin(), name.end()).c_str(), params, CW_USEDEFAULT, CW_USEDEFAULT,
                _window_size.x + 20, _window_size.y + 43, NULL, NULL, hInstance, NULL);
            ShowWindow(*window_hwnd, SW_SHOW);
            UpdateWindow(*window_hwnd);
            while (GetMessage(&Msg, NULL, 0, 0) > 0) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
            Gdiplus::GdiplusShutdown(gdiplusToken);
        };

        std::thread window_thread(win, &_window_hwnd);
        window_thread.detach();
        while (_window_hwnd == NULL) {
            Sleep(1);
        }
    }

}