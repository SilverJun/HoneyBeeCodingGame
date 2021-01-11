//
// Created by SilverJun on 2021-01-11.
//

#pragma once

#include <string>
#include <utility>

struct Material
{
    Material(std::string materialName, std::string vertexShaderPath, std::string fragmentShaderPath, std::string texturePath)
        : MaterialName(std::move(materialName))
        , VertexShaderPath(std::move(vertexShaderPath))
        , FragmentShaderPath(std::move(fragmentShaderPath))
        , TexturePath(std::move(texturePath))
    {
    }

    std::string MaterialName;
    std::string VertexShaderPath;
    std::string FragmentShaderPath;
    std::string TexturePath;
};