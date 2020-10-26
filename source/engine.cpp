#include <iostream>
#include <time.h>
#include "engine.h"
#include "window.h"

Engine::Engine() { }
Engine::~Engine() { }

void Engine::initWindow( int width, int height ) {
  callback = std::make_unique<WindowCallback>( );
  callback->SetEngine( this );

  window = std::make_unique<Window>( );
  window->SetCallback( callback.get() );
  window->createWindow( width, height, "TheSurvivorGame" );
}

void Engine::mainLoop(void) {
  MSG msg = { 0 };

	while(true) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if(GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				return;
			}
		} else {
		  drawFrame();
    }
	}
}

void Engine::drawFrame() {
  const HDC  dc     = window->getDC( );
  const HDC  memdc  = window->getMemDC( );

  const RECT clientRect = window->getClientRect();
	FillRect(memdc, &clientRect, window->getBrush());

	BitBlt(dc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, SRCCOPY);
}

void Engine::closeApp() {
  callback->OnDestroy( );
}
