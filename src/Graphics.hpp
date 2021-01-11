//
// Created by SilverJun on 2021-01-11.
//
#pragma once

#include <GLFW/glfw3.h>

#include "Material.h"

enum class GraphicsAPI
{
    OpenGL,
    Vulkan,
    DX11,
};

template<GraphicsAPI T>
class Graphics final
{
public:
    Graphics() = default;
    virtual ~Graphics() = default;

    GraphicsAPI GetGraphicsType() const { return T; }

    void Init(GLFWwindow* window) = 0;
    void PreRender() = 0;
    void Render() = 0;
    void PostRender() = 0;

    // Material
    void RegisterMaterial(Material&& material) = 0;

    // Texture
    void LoadTexture(Material& material) = 0;

    // Shader
    void LoadShaders(Material& material) = 0;

private:
    GLFWwindow* _window;
};
