//
// Created by SilverJun on 2021-01-11.
//

#pragma once

#include <vector>
#include <unordered_map>

#include "Graphics.hpp"

template<>
class Graphics<GraphicsAPI::OpenGL> final
{
public:
    Graphics() = default;
    virtual ~Graphics() = default;

    GraphicsAPI GetGraphicsType() const { return GraphicsAPI::OpenGL; }

    void Init(GLFWwindow* window);
    void PreRender();
    void Render();
    void PostRender();

    // Material
    void RegisterMaterial(Material&& material);

    // Texture
    void LoadTexture(Material& material);

    // Shader
    void LoadShaders(Material& material);

private:
    GLFWwindow* _window;

    std::unordered_map<std::string, Material> _material;
};
