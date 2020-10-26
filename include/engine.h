#pragma once

#include <memory>

class Window;
class WindowCallback;

class Engine {
private:
  std::unique_ptr<Window>         window;
  std::unique_ptr<WindowCallback> callback;

	bool debugMode;
	float timeFactor;

public:
	Engine();
  ~Engine();

	void initWindow(int width, int height);
	void mainLoop();
  void closeApp();

private:
	void drawFrame();

};
