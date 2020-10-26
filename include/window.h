#pragma once

#include "base_window.h"

class Engine;

class WindowCallback {
public:
  WindowCallback();
  ~WindowCallback();

  void SetEngine(Engine* ptr);
  void OnCreate();
  void OnDestroy();
  void OnMouseClick(int x, int y, bool click);
  void OnMouseMove(int x, int y);
  void OnKeyboard(int key, bool press);

protected:
  Engine* _engine;

};

class Window final : public BaseWindow {
public:
  Window();
  ~Window();

  void SetCallback(WindowCallback* ptr);

  void OnCreate() override;
  void OnDestroy() override;
  void OnMouseClick(int x, int y, bool click) override;
  void OnMouseMove(int x, int y) override;
  void OnKeyboard(int key, bool press) override;
  
  HDC getDC() const noexcept { return _hDC; }
  HDC getMemDC() const noexcept { return _hMemDC; }
  HBITMAP getMemMap() const noexcept { return _hMemMap; }
  RECT getClientRect() const noexcept { return _clientRect; }
  HBRUSH getBrush() const noexcept { return _brush; }
  HPEN getPen() const noexcept { return _pen; }

private:
  WindowCallback* _cb;
  HDC             _hDC;
  HDC             _hMemDC;
  HBITMAP         _hMemMap;
  RECT            _clientRect;
  HBRUSH          _brush;
  HPEN            _pen;

};
