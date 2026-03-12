#pragma once


#include <cstdint>
#include <imgui.h>

struct Element
{
    bool Enabled = true;
    uint32_t Color = 0xFFFFFFFF;
    ImVec2 Position = ImVec2(0.0f, 0.0f);
};

enum class TextAlignment : int32_t
{
    Left = 0,
    Center = 1,
    Right = 2
};

struct TextElement : Element
{
    float TextSize = 29.0f;
    TextAlignment Alignment = TextAlignment::Center;
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
