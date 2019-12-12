#include "ShaderManager.h"
#include <GL/glew.h>
#include "LoadShaders.h"


ShaderManager::ShaderManager() : _shaders(ShaderNum)
{
	ShaderInfo shaders[ShaderNum][3] = {
		   {
			   {GL_VERTEX_SHADER, "../Assets/Shader/Sprite.vert"},
			   {GL_FRAGMENT_SHADER, "../Assets/Shader/Sprite.frag"},
			   {GL_NONE, NULL}
		   },
		   {
			   {GL_VERTEX_SHADER, "../Assets/Shader/phong.vert"},
			   {GL_FRAGMENT_SHADER, "../Assets/Shader/phong.frag"},
			   {GL_NONE, NULL}
		   }
	};

	for (int i = 0; i < _shaders.size(); ++i)
	{
		_shaders[i] = LoadShaders(shaders[i]);
	}
}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < _shaders.size(); ++i)
	{
		glDeleteProgram(_shaders[i]);
	}
	_shaders.clear();
}

int ShaderManager::GetShader(Shader shader)
{
	return _shaders[shader];
}
