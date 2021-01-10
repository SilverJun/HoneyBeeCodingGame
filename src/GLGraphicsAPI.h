//
// Created by SilverJun on 2021-01-11.
//

#pragma once

#include "Graphics.h"

template<>
class Graphics<GraphicsAPI::OpenGL> final
{
public:
    Graphics() = default;
    virtual ~Graphics() = default;

    void Init(GLFWwindow* window);
    void PreRender();
    void Render();
    void PostRender();

private:
    GLFWwindow* _window;
};
