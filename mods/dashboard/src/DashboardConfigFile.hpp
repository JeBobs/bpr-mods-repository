#pragma once


#include <cstdint>

#include "core/Path.hpp"
#include "core/Logger.hpp"

#include "DashboardElements.hpp"

struct DashboardConfig
{
    bool AlwaysVisible = false;
    bool MetricUnits = true;
    float Opacity = 78.0f;
    float Scale = 1.0f;
    struct
    {
        TextureElement SpeedBackgroundTexture =
        {
            SpeedBackgroundTexture.Enabled = true,
            SpeedBackgroundTexture.Color = 0xFFFFFFFF,
            SpeedBackgroundTexture.Position = ImVec2(-128.0f, 72.0f),
            SpeedBackgroundTexture.Size = ImVec2(256.0f, 256.0f)
        };
        TextureElement SpeedDialTexture =
        {
            SpeedDialTexture.Enabled = true,
            SpeedDialTexture.Color = 0xFFFCFF24,
            SpeedDialTexture.Position = ImVec2(-128.0f, 72.0f),
            SpeedDialTexture.Size = ImVec2(256.0f, 256.0f)
        };
        TextureElement RPMBackgroundTexture =
        {
            RPMBackgroundTexture.Enabled = true,
            RPMBackgroundTexture.Color = 0xFFFFFFFF,
            RPMBackgroundTexture.Position = ImVec2(128.0f, 72.0f),
            RPMBackgroundTexture.Size = ImVec2(256.0f, 256.0f)

        };
        TextureElement RPMDialTexture =
        {
            RPMDialTexture.Enabled = true,
            RPMDialTexture.Color = 0xFFFCFF24,
            RPMDialTexture.Position = ImVec2(128.0f, 72.0f),
            RPMDialTexture.Size = ImVec2(256.0f, 256.0f)
        };
        NeedleElement RPMNeedle =
        {
            SpeedNeedle.Enabled = true,
            SpeedNeedle.Color = 0xFF3426FF,
            SpeedNeedle.Position = ImVec2(-128.0f, 72.0f),
            SpeedNeedle.Thickness = 3.0f,
            SpeedNeedle.InnerRadius = 68.0f,
            SpeedNeedle.OuterRadius = 103.0f,
            SpeedNeedle.MinAngle = -225.0f,
            SpeedNeedle.MaxAngle = 45.0f
        };
        NeedleElement SpeedNeedle =
        {
            SpeedNeedle.Enabled = true,
            SpeedNeedle.Color = 0xFF3426FF,
            SpeedNeedle.Position = ImVec2(128.0f, 72.0f),
            SpeedNeedle.Thickness = 3.0f,
            SpeedNeedle.InnerRadius = 68.0f,
            SpeedNeedle.OuterRadius = 103.0f,
            SpeedNeedle.MinAngle = -225.0f,
            SpeedNeedle.MaxAngle = 45.0f
        };
        TextElement SpeedText =
        {
            SpeedText.Enabled = true,
            SpeedText.Color = 0xFFFCFF24,
            SpeedText.Position = ImVec2(-128.0f, 102.0f),
            SpeedText.TextSize = 29.0f
        };
        TextElement TripMeterText =
        {
            TripMeterText.Enabled = true,
            TripMeterText.Color = 0xFFFCFF24,
            TripMeterText.Position = ImVec2(-128.0f, 69.0f),
            TripMeterText.TextSize = 24.0f
        };
        TextElement OdometerText =
        {
            OdometerText.Enabled = true,
            OdometerText.Color = 0xFFFCFF24,
            OdometerText.Position = ImVec2(-128.0f, 42.0f),
            OdometerText.TextSize = 29.0f
        };
        TextElement RPMText =
        {
            TripMeterText.Enabled = true,
            TripMeterText.Color = 0xFFFCFF24,
            TripMeterText.Position = ImVec2(128.0f, 102.0f),
            TripMeterText.TextSize = 29.0f
        };
        TextElement LocalTimeText =
        {
            LocalTimeText.Enabled = true,
            LocalTimeText.Color = 0xFFFCFF24,
            LocalTimeText.Position = ImVec2(128.0f, 42.0f),
            LocalTimeText.TextSize = 29.0f
        };

        TextElement CurrentGearText =
        {
            CurrentGearText.Enabled = true,
            CurrentGearText.Color = 0xFFFCFF24,
            CurrentGearText.Position = ImVec2(128.0f, 70.0f),
            CurrentGearText.TextSize = 37.0f
        };
    } Elements;
};

class DashboardConfigFile
{
public:
    DashboardConfigFile(Core::Path directory, const Core::Logger& logger);

public:
    void Load();
    void Save() const;

    DashboardConfig& GetDashboardConfig();

private:
    Core::Path m_FilePath;
    const Core::Logger& m_Logger;

    DashboardConfig m_DashboardConfig;
};
