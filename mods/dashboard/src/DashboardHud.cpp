#include "DashboardHud.hpp"

#include <vector>
#include <algorithm>
#include <DirectXMath.h>

#include "core/File.hpp"


static ImVec2 GetAbsolutePosition(const ImVec2& position, float scale)
{
    ImGuiViewport* mainViewport = ImGui::GetMainViewport();

    float x = mainViewport->Pos.x + mainViewport->Size.x / 2.0f + position.x * scale;
    float y = mainViewport->Pos.y + mainViewport->Size.y - position.y * scale;

    return ImVec2(x, y);
}

static ImColor ApplyOpacityToColor(ImColor color, float opacity)
{
    color.Value.w *= opacity / 100.0f;
    return color;
}


DashboardHud::DashboardHud(DashboardConfigFile& dashboardConfigFile, const Core::Path& assetsDirectory, const Core::Logger& logger)
    :
    m_DashboardConfigFile(dashboardConfigFile),
    m_AssetsDirectory(assetsDirectory),
    m_Logger(logger)
{
}

void DashboardHud::LoadTexture()
{
    Core::Path filePath = Core::Path(m_AssetsDirectory).Append("texture.dds");

    m_Logger.Info("Loading texture from file '%s' ...", filePath.GetPath());
    
    Core::File file(filePath.GetPath(), Core::File::Mode::Read);
    std::vector<BYTE> textureData = file.Read<std::vector<BYTE>>();
    m_DashboardTexture.CreateTexture(textureData.data());

    m_Logger.Info("Loaded texture.");
}

void DashboardHud::LoadFont()
{
    Core::Path filePath = Core::Path(m_AssetsDirectory).Append("font.ttf");
    
    m_Logger.Info("Loading font from file '%s' ...", filePath.GetPath());
    
    ImGuiIO& io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF(filePath.GetPath());

    m_Logger.Info("Loaded font.");
}

void DashboardHud::OnProgressionAddDistanceDriven(
    Core::Pointer progressionManager, // BrnProgression::ProgressionManager*
    float distance, // In meters.
    int32_t vehicleType
)
{
    static constexpr ptrdiff_t offsets[] =
    {
        0x1EC,   // Distance driven online.
        0x1F8,   // Distance driven offline.
        0x29314, // Distance driven offline on BSI.
        0x29320, // Distance driven online on BSI.
    };
    
    float odometer = 0.0f;
    for (ptrdiff_t offset : offsets)
    {
        for (int i = 0; i < 3; ++i)
        {
            odometer += progressionManager.at(offset).as<float[3]>()[i];
        }
    }

    m_TripMeter += distance;
    m_Odometer = odometer + distance;
}

void DashboardHud::OnRenderMenu()
{
    if (ImGui::CollapsingHeader("Config"))
    {
        {
            if (ImGui::Button("Save##dashboard-config-file"))
            {
                m_DashboardConfigFile.Save();
            }

            ImGui::SameLine();

            if (ImGui::Button("Load##dashboard-config-file"))
            {
                m_DashboardConfigFile.Load();
            }

            ImGui::SameLine();

            if (ImGui::Button("Reload Texture##dashboard-texture"))
            {
                LoadTexture();
            }
        }

        ImGui::Separator();

        {
            DashboardConfig& config = m_DashboardConfigFile.GetDashboardConfig();
            
            ImGui::Checkbox("Always Visible", &config.AlwaysVisible);
            ImGui::Checkbox("Metric Units", &config.MetricUnits);
            ImGui::SliderFloat("Opacity", &config.Opacity, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::SliderFloat("Scale", &config.Scale, 0.1f, 5.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);

            auto renderColorEdit = [](const char* label, uint32_t& colorValue)
            {
                ImVec4 color = ImGui::ColorConvertU32ToFloat4(colorValue);
                if (ImGui::ColorEdit4(label, reinterpret_cast<float*>(&color)))
                {
                    colorValue = ImGui::ColorConvertFloat4ToU32(color);
                }
            };

            auto renderElementEditor = [&](Element& element)
            {
                ImGui::Checkbox("Enabled", &element.Enabled);
                renderColorEdit("Color", element.Color);
                ImGui::DragFloat2("Position", reinterpret_cast<float*>(&element.Position), 1.0f);
            };

            auto renderTextureElementEditor = [&](const char* label, TextureElement& element)
            {
                if (ImGui::TreeNode(label))
                {
                    renderElementEditor(element);
                    ImGui::DragFloat2("Size", reinterpret_cast<float*>(&element.Size), 1.0f, 1.0f, 1024.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::TreePop();
                }
            };

            auto renderTextElementEditor = [&](const char* label, TextElement& element)
            {
                if (ImGui::TreeNode(label))
                {
                    renderElementEditor(element);
                    ImGui::DragFloat("Text Size", &element.TextSize, 0.1f, 1.0f, 200.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);

                    static const char* textAlignmentNames[] = { "Left", "Center", "Right" };
                    int textAlignment = static_cast<int>(element.Alignment);
                    if (ImGui::Combo("Alignment", &textAlignment, textAlignmentNames, IM_ARRAYSIZE(textAlignmentNames)))
                    {
                        element.Alignment = static_cast<TextAlignment>(textAlignment);
                    }

                    ImGui::TreePop();
                }
            };

            auto renderNeedleElementEditor = [&](const char* label, NeedleElement& element)
            {
                if (ImGui::TreeNode(label))
                {
                    renderElementEditor(element);
                    ImGui::DragFloat("Thickness", &element.Thickness, 0.1f, 0.1f, 50.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::DragFloat("Inner Radius", &element.InnerRadius, 0.1f, 0.0f, 500.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::DragFloat("Outer Radius", &element.OuterRadius, 0.1f, 0.0f, 500.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::DragFloat("Min Angle", &element.MinAngle, 0.1f, -360.0f, 360.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::DragFloat("Max Angle", &element.MaxAngle, 0.1f, -360.0f, 360.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::TreePop();
                }
            };

            ImGui::SeparatorText("Elements");
            renderTextureElementEditor("Speed Background Texture", config.Elements.SpeedBackgroundTexture);
            renderTextureElementEditor("Speed Dial Texture", config.Elements.SpeedDialTexture);
            renderNeedleElementEditor("Speed Needle", config.Elements.SpeedNeedle);
            renderTextElementEditor("Speed Text", config.Elements.SpeedText);
            renderTextElementEditor("Trip Meter Text", config.Elements.TripMeterText);
            renderTextElementEditor("Odometer Text", config.Elements.OdometerText);

            renderTextureElementEditor("RPM Background Texture", config.Elements.RPMBackgroundTexture);
            renderTextureElementEditor("RPM Dial Texture", config.Elements.RPMDialTexture);
            renderNeedleElementEditor("RPM Needle", config.Elements.RPMNeedle);
            renderTextElementEditor("RPM Text", config.Elements.RPMText);
            renderTextElementEditor("Current Gear Text", config.Elements.CurrentGearText);
            renderTextElementEditor("Local Time Text", config.Elements.LocalTimeText);
        }
    }
}

void DashboardHud::OnRenderOverlay()
{
    const DashboardConfig& config = m_DashboardConfigFile.GetDashboardConfig();
    
    Core::Pointer guiPlayerInfo = Core::Pointer(0x013FC8E0).deref().at(0x8EFEC0); // BrnGui::GuiPlayerInfo*
    Core::Pointer raceMainHudState = Core::Pointer(0x013FC8E0).deref().at(0x7FABBC).as<void*>(); // BrnGui::RaceMainHudState*
    
    if (!config.AlwaysVisible)
    {
        bool inRaceHud = raceMainHudState.at(0x14C).as<bool>();
        int32_t engineState = guiPlayerInfo.at(0x48).as<int32_t>();
        if (!inRaceHud || engineState == 0) // BrnGui::GuiPlayerEngineEvent::EEngineState::E_ENGINE_OFF
        {
            return;
        }
    }

    // Speed
    {
        int32_t speed = abs(guiPlayerInfo.at(0x30).as<int32_t>());
        if (config.MetricUnits)
        {
            speed = static_cast<int32_t>(roundf(speed * 1.609f));
        }
        
        char speedText[8] = {};
        sprintf_s(speedText, "%d", speed);

        if (config.Elements.SpeedBackgroundTexture.Enabled)
        {
            RenderTextureSegment(config.Elements.SpeedBackgroundTexture, DashboardTexture::TextureSegment::Background);
        }
        if (config.Elements.SpeedDialTexture.Enabled)
        {
            RenderTextureSegment(config.Elements.SpeedDialTexture, config.MetricUnits ? DashboardTexture::TextureSegment::KMH : DashboardTexture::TextureSegment::MPH);
        }
        
        if (config.Elements.SpeedText.Enabled)
        {
            RenderText(config.Elements.SpeedText, speedText);
        }
        if (config.Elements.SpeedNeedle.Enabled)
        {
            RenderNeedle(config.Elements.SpeedNeedle, static_cast<float>(speed), 0.0f, config.MetricUnits ? 360.0f : 240.0f);
        }
    }

    // Trip meter
    {
        float tripMeter = config.MetricUnits ? (m_TripMeter / 1000.0f) : (m_TripMeter / 1609.0f);

        char tripMeterText[16] = {};
        sprintf_s(tripMeterText, "%.1f", tripMeter);

        if (config.Elements.TripMeterText.Enabled)
        {
            RenderText(config.Elements.TripMeterText, tripMeterText);
        }
    }

    // Odometer
    {
        int32_t odometer = static_cast<int32_t>(config.MetricUnits ? (m_Odometer / 1000.0f) : (m_Odometer / 1609.0f));

        char odometerText[16] = {};
        sprintf_s(odometerText, "%06d", odometer);

        if (config.Elements.OdometerText.Enabled)
        {
            RenderText(config.Elements.OdometerText, odometerText);
        }
    }

    // RPM
    {
        int32_t rpm = guiPlayerInfo.at(0x34).as<int32_t>();

        char rpmText[8] = {};
        sprintf_s(rpmText, "%d", rpm);

        if (config.Elements.RPMBackgroundTexture.Enabled)
        {
            RenderTextureSegment(config.Elements.RPMBackgroundTexture, DashboardTexture::TextureSegment::Background);
        }
        if (config.Elements.RPMDialTexture.Enabled)
        {
            RenderTextureSegment(config.Elements.RPMDialTexture, DashboardTexture::TextureSegment::RPM);
        }

        if (config.Elements.RPMText.Enabled)
        {
            RenderText(config.Elements.RPMText, rpmText);
        }
        if (config.Elements.RPMNeedle.Enabled)
        {
            RenderNeedle(config.Elements.RPMNeedle, static_cast<float>(rpm), 0.0f, 12000.0f);
        }
    }

    // Gear
    {
        int32_t gear = guiPlayerInfo.at(0x38).as<int32_t>();

        static constexpr char gears[][2] = { "R", "1", "2", "3", "4", "5" };

        if (config.Elements.CurrentGearText.Enabled)
        {
            RenderText(config.Elements.CurrentGearText, gears[gear]);
        }
    }

    // Local Time
    {
        SYSTEMTIME localTime = {};
        GetLocalTime(&localTime);

        char localTimeText[8] = {};
        sprintf_s(localTimeText, "%02d:%02d", localTime.wHour, localTime.wMinute);

        if (config.Elements.LocalTimeText.Enabled)
        {
            RenderText(config.Elements.LocalTimeText, localTimeText);
        }
    }
}

void DashboardHud::RenderTextureSegment(const TextureElement& properties, DashboardTexture::TextureSegment textureSegment) const
{
    const DashboardConfig& config = m_DashboardConfigFile.GetDashboardConfig();
    
    ImVec2 segmentSize = ImVec2(properties.Size.x * config.Scale, properties.Size.y * config.Scale);
    ImColor color = ApplyOpacityToColor(properties.Color, config.Opacity);

    DashboardTexture::TextureSegmentUVs uv = m_DashboardTexture.GetTextureSegmentUVs(textureSegment);

    ImVec2 absolutePosition = GetAbsolutePosition(properties.Position, config.Scale);
    float l = absolutePosition.x - segmentSize.x / 2.0f;
    float r = absolutePosition.x + segmentSize.x / 2.0f;
    float t = absolutePosition.y - segmentSize.y / 2.0f;
    float b = absolutePosition.y + segmentSize.y / 2.0f;
    
    ImDrawList* foregroundDrawList = ImGui::GetForegroundDrawList();
    foregroundDrawList->AddImage(reinterpret_cast<ImTextureID>(m_DashboardTexture.GetTextureView()), ImVec2(l, t), ImVec2(r, b), ImVec2(uv.Left, uv.Top), ImVec2(uv.Right, uv.Bottom), color);
}

void DashboardHud::RenderText(const TextElement& properties, const char* text) const
{
    const DashboardConfig& config = m_DashboardConfigFile.GetDashboardConfig();
    
    float fontSize = properties.TextSize * config.Scale;
    ImColor color = ApplyOpacityToColor(properties.Color, config.Opacity);

    ImVec2 textSize = m_Font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
    
    ImVec2 absolutePosition = GetAbsolutePosition(properties.Position, config.Scale);
    float x = absolutePosition.x;
    switch (properties.Alignment)
    {
        case TextAlignment::Left:
            break;
        case TextAlignment::Right:
            x -= textSize.x;
            break;
        case TextAlignment::Center:
        default:
            x -= textSize.x / 2.0f;
            break;
    }
    float y = absolutePosition.y - textSize.y / 2.0f;

    ImDrawList* foregroundDrawList = ImGui::GetForegroundDrawList();
    foregroundDrawList->AddText(m_Font, fontSize, ImVec2(x, y), color, text);
}

void DashboardHud::RenderNeedle(const NeedleElement& properties, float value, float minValue, float maxValue) const
{
    const DashboardConfig& config = m_DashboardConfigFile.GetDashboardConfig();
    
    float minAngle = DirectX::XMConvertToRadians(properties.MinAngle);
    float maxAngle = DirectX::XMConvertToRadians(properties.MaxAngle);
    float thickness = properties.Thickness * config.Scale;
    float innerRadius = properties.InnerRadius * config.Scale;
    float outerRadius = properties.OuterRadius * config.Scale;
    ImColor color = ApplyOpacityToColor(properties.Color, config.Opacity);

    value = std::clamp(value, minValue, maxValue);
    float angle = minAngle + (maxAngle - minAngle) * ((value - minValue) / (maxValue - minValue));
    float angleSin = 0.0f, angleCos = 0.0f;
    DirectX::XMScalarSinCos(&angleSin, &angleCos, angle);

    ImVec2 absolutePosition = GetAbsolutePosition(properties.Position, config.Scale);
    float x1 = absolutePosition.x + angleCos * innerRadius;
    float y1 = absolutePosition.y + angleSin * innerRadius;
    float x2 = absolutePosition.x + angleCos * outerRadius;
    float y2 = absolutePosition.y + angleSin * outerRadius;

    ImDrawList* foregroundDrawList = ImGui::GetForegroundDrawList();
    foregroundDrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}
