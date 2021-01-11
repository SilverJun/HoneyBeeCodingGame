#pragma once
#include "Singleton.h"
#include "Graphics.hpp"
#include "GLGraphicsAPI.h"
class SceneManager;
class Interpolator;
class SoundManager;
struct GLFWwindow;

class GameApp : public Singleton<GameApp>
{
	SceneManager* _sceneManager;
	Interpolator* _interpolator;
	SoundManager* _soundManager;
	GLFWwindow* _window;

	bool _isExit;

public:
	int _width;
	int _height;
	bool _isClick = false;
	double _mouseX;
	double _mouseY;
    Graphics<GraphicsAPI::OpenGL> _graphics;

	GameApp();
	~GameApp();

	int GameLoop();

	void Init();
	void ProcessKey(int key, int scancode, int action, int mods);
	void Update();
	void Render();
	void Release();
};

