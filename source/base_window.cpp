#include "base_window.h"
#include <stdexcept>
#include <string>

BaseWindow::BaseWindow()
  : _hWnd(nullptr)
{ }

BaseWindow::BaseWindow(int width, int height, const std::string& classname)
  : _hWnd(nullptr)
{
  if(!createWindow(width, height, classname)) {
    throw std::runtime_error("Can't create window properly");
  }
}

BaseWindow::~BaseWindow() {
  destroyWindow();
}

void BaseWindow::destroyWindow() {}

LRESULT __stdcall BaseWindow::WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  BaseWindow* wptr = nullptr;

  if(msg == WM_NCDESTROY) {
    SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
    return DefWindowProc(hWnd, msg, wParam, lParam);
  } else if(msg == WM_NCCREATE) {
    const LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
    wptr = (BaseWindow*)cs->lpCreateParams;
    wptr->_hWnd = hWnd;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)wptr);
  } else {
    wptr = (BaseWindow*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
  }

  if(wptr) {
    return wptr->WindProc( msg, wParam, lParam );
  } else {
    return DefWindowProc( hWnd, msg, wParam, lParam );
  }
}

bool BaseWindow::createWindow(int W, int H, const std::string& classname) {
#if UNICODE
  const std::wstring clname(classname.begin(), classname.end());
#else
  const std::string clname(classname.begin(), classname.end());
#endif

	const WNDCLASS wc = { CS_OWNDC, WindProc, NULL, NULL, 0, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), NULL, NULL, clname.c_str() };
	RegisterClass(&wc);

	int height, width, left, top;
	width = W + ( (GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXEDGE) ) << 1) + 3;
	height = H + GetSystemMetrics(SM_CYCAPTION) + ( (GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CXEDGE) ) << 1) + 3;
	left = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
	top = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

	HWND hWnd = CreateWindow( clname.c_str(), NULL, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, left, top, width, height, NULL, NULL, 0, (void*)this );
  if( !hWnd ) {
    return false;
  }

	ShowWindow( hWnd, SW_SHOW );
  return (bool)hWnd;
}

LRESULT BaseWindow::WindProc(UINT msg, WPARAM wParam, LPARAM lParam) {
  switch(msg) {
    case WM_CREATE:      OnCreate();                                          break;
    case WM_DESTROY:     OnDestroy();                                         break;
    case WM_LBUTTONDOWN: OnMouseClick(LOWORD(lParam), HIWORD(lParam), true);  break;
    case WM_LBUTTONUP:   OnMouseClick(LOWORD(lParam), HIWORD(lParam), false); break;
    case WM_MOUSEMOVE:   OnMouseMove(LOWORD(lParam), HIWORD(lParam));         break;
    case WM_KEYDOWN:     OnKeyboard(static_cast<int>(wParam), true);          break;
    case WM_KEYUP:       OnKeyboard(static_cast<int>(wParam), false);         break;

    default: return DefWindowProc(_hWnd, msg, wParam, lParam);
  }
}
