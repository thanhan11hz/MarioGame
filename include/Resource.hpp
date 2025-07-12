#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>

class Resource {
    public:
        static std::unordered_map<std::string, Texture2D> textures;
        static std::unordered_map<std::string, Sound> sounds;
};