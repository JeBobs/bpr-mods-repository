#pragma once


#include <cstdint>
#include <imgui.h>

struct Element
{
    bool Enabled = true;
    uint32_t Color = 0xFFFFFFFF;
    ImVec2 Position = ImVec2(0.0f, 0.0f);
};

struct TextElement : Element
{
    float TextSize = 29.0f;
};

struct NeedleElement : Element
{
    float Thickness = 3.0f;
    float InnerRadius = 68.0f;
    float OuterRadius = 103.0f;
    float MinAngle = -225.0f;
    float MaxAngle = 45.0f;
};

struct TextureElement : Element
{
    ImVec2 Size = ImVec2(256.0f, 256.0f);
};