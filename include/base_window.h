#pragma once

#include <windows.h>
#include <string>

class BaseWindowCallback {
public:
  BaseWindowCallback( ) = default;
  virtual ~BaseWindowCallback() { }

  virtual void OnCreate() = 0;
  virtual void OnDestroy() = 0;
  virtual void OnMouseClick(int x, int y, bool click) = 0;
  virtual void OnMouseMove(int x, int y) = 0;
  virtual void OnKeyboard(int key, bool press) = 0;
};

class BaseWindow : public BaseWindowCallback {
public:
  BaseWindow();
  BaseWindow(int width, int height, const std::string& classname);
  virtual ~BaseWindow();
  
  bool createWindow(int width, int height, const std::string& classname);
  void destroyWindow();

  HWND getHWND() const noexcept { return _hWnd; }

protected:
  HWND    _hWnd;

private:
  static LRESULT __stdcall WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  virtual LRESULT WindProc(UINT msg, WPARAM wParam, LPARAM lParam);

};
