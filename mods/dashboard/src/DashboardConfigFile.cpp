#include "DashboardConfigFile.hpp"

#include "vendor/yaml-cpp.hpp"

#include "core/File.hpp"


static constexpr char k_Name[] = "dashboard config";


DashboardConfigFile::DashboardConfigFile(Core::Path directory, const Core::Logger& logger)
    :
    m_FilePath(directory.Append("dashboard-config.yaml")),
    m_Logger(logger)
{
}

void DashboardConfigFile::Load()
{
    try
    {
        m_Logger.Info("Loading %s from file '%s' ...", k_Name, m_FilePath.GetPath());

        Core::File file(m_FilePath.GetPath(), Core::File::Mode::Read);
        YAML::Node yaml = YAML::Load(file.Read<std::string>());
        {
            if (yaml["AlwaysVisible"]) m_DashboardConfig.AlwaysVisible = yaml["AlwaysVisible"].as<bool>();
            if (yaml["MetricUnits"])   m_DashboardConfig.MetricUnits = yaml["MetricUnits"].as<bool>();
            if (yaml["Opacity"])       m_DashboardConfig.Opacity = yaml["Opacity"].as<float>();
            if (yaml["Scale"])         m_DashboardConfig.Scale = yaml["Scale"].as<float>();

            YAML::Node elementsNode = yaml["Elements"];
            if (elementsNode)
            {
                {
                    YAML::Node node = elementsNode["SpeedBackgroundTexture"];
                    if (node)
                    {
                        if (node["Enabled"]) m_DashboardConfig.Elements.SpeedBackgroundTexture.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])   m_DashboardConfig.Elements.SpeedBackgroundTexture.Color = node["Color"].as<uint32_t>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.SpeedBackgroundTexture.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.SpeedBackgroundTexture.Position.y = positionNode["Y"].as<float>();
                        }

                        YAML::Node sizeNode = node["Size"];
                        if (sizeNode)
                        {
                            if (sizeNode["X"]) m_DashboardConfig.Elements.SpeedBackgroundTexture.Size.x = sizeNode["X"].as<float>();
                            if (sizeNode["Y"]) m_DashboardConfig.Elements.SpeedBackgroundTexture.Size.y = sizeNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["SpeedDialTexture"];
                    if (node)
                    {
                        if (node["Enabled"]) m_DashboardConfig.Elements.SpeedDialTexture.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])   m_DashboardConfig.Elements.SpeedDialTexture.Color = node["Color"].as<uint32_t>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.SpeedDialTexture.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.SpeedDialTexture.Position.y = positionNode["Y"].as<float>();
                        }

                        YAML::Node sizeNode = node["Size"];
                        if (sizeNode)
                        {
                            if (sizeNode["X"]) m_DashboardConfig.Elements.SpeedDialTexture.Size.x = sizeNode["X"].as<float>();
                            if (sizeNode["Y"]) m_DashboardConfig.Elements.SpeedDialTexture.Size.y = sizeNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["RPMBackgroundTexture"];
                    if (node)
                    {
                        if (node["Enabled"]) m_DashboardConfig.Elements.RPMBackgroundTexture.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])   m_DashboardConfig.Elements.RPMBackgroundTexture.Color = node["Color"].as<uint32_t>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.RPMBackgroundTexture.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.RPMBackgroundTexture.Position.y = positionNode["Y"].as<float>();
                        }

                        YAML::Node sizeNode = node["Size"];
                        if (sizeNode)
                        {
                            if (sizeNode["X"]) m_DashboardConfig.Elements.RPMBackgroundTexture.Size.x = sizeNode["X"].as<float>();
                            if (sizeNode["Y"]) m_DashboardConfig.Elements.RPMBackgroundTexture.Size.y = sizeNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["RPMDialTexture"];
                    if (node)
                    {
                        if (node["Enabled"]) m_DashboardConfig.Elements.RPMDialTexture.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])   m_DashboardConfig.Elements.RPMDialTexture.Color = node["Color"].as<uint32_t>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.RPMDialTexture.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.RPMDialTexture.Position.y = positionNode["Y"].as<float>();
                        }

                        YAML::Node sizeNode = node["Size"];
                        if (sizeNode)
                        {
                            if (sizeNode["X"]) m_DashboardConfig.Elements.RPMDialTexture.Size.x = sizeNode["X"].as<float>();
                            if (sizeNode["Y"]) m_DashboardConfig.Elements.RPMDialTexture.Size.y = sizeNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["RPMNeedle"];
                    if (node)
                    {
                        if (node["Enabled"])     m_DashboardConfig.Elements.RPMNeedle.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])       m_DashboardConfig.Elements.RPMNeedle.Color = node["Color"].as<uint32_t>();
                        if (node["Thickness"])   m_DashboardConfig.Elements.RPMNeedle.Thickness = node["Thickness"].as<float>();
                        if (node["InnerRadius"]) m_DashboardConfig.Elements.RPMNeedle.InnerRadius = node["InnerRadius"].as<float>();
                        if (node["OuterRadius"]) m_DashboardConfig.Elements.RPMNeedle.OuterRadius = node["OuterRadius"].as<float>();
                        if (node["MinAngle"])    m_DashboardConfig.Elements.RPMNeedle.MinAngle = node["MinAngle"].as<float>();
                        if (node["MaxAngle"])    m_DashboardConfig.Elements.RPMNeedle.MaxAngle = node["MaxAngle"].as<float>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.RPMNeedle.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.RPMNeedle.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["SpeedNeedle"];
                    if (node)
                    {
                        if (node["Enabled"])     m_DashboardConfig.Elements.SpeedNeedle.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])       m_DashboardConfig.Elements.SpeedNeedle.Color = node["Color"].as<uint32_t>();
                        if (node["Thickness"])   m_DashboardConfig.Elements.SpeedNeedle.Thickness = node["Thickness"].as<float>();
                        if (node["InnerRadius"]) m_DashboardConfig.Elements.SpeedNeedle.InnerRadius = node["InnerRadius"].as<float>();
                        if (node["OuterRadius"]) m_DashboardConfig.Elements.SpeedNeedle.OuterRadius = node["OuterRadius"].as<float>();
                        if (node["MinAngle"])    m_DashboardConfig.Elements.SpeedNeedle.MinAngle = node["MinAngle"].as<float>();
                        if (node["MaxAngle"])    m_DashboardConfig.Elements.SpeedNeedle.MaxAngle = node["MaxAngle"].as<float>();

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.SpeedNeedle.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.SpeedNeedle.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["SpeedText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.SpeedText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.SpeedText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.SpeedText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.SpeedText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.SpeedText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.SpeedText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["TripMeterText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.TripMeterText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.TripMeterText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.TripMeterText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.TripMeterText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.TripMeterText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.TripMeterText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["OdometerText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.OdometerText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.OdometerText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.OdometerText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.OdometerText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.OdometerText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.OdometerText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["RPMText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.RPMText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.RPMText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.RPMText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.RPMText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.RPMText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.RPMText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["LocalTimeText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.LocalTimeText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.LocalTimeText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.LocalTimeText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.LocalTimeText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.LocalTimeText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.LocalTimeText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }

                {
                    YAML::Node node = elementsNode["CurrentGearText"];
                    if (node)
                    {
                        if (node["Enabled"])  m_DashboardConfig.Elements.CurrentGearText.Enabled = node["Enabled"].as<bool>();
                        if (node["Color"])    m_DashboardConfig.Elements.CurrentGearText.Color = node["Color"].as<uint32_t>();
                        if (node["TextSize"]) m_DashboardConfig.Elements.CurrentGearText.TextSize = node["TextSize"].as<float>();
                        if (node["Alignment"])
                        {
                            int32_t alignment = node["Alignment"].as<int32_t>();
                            if (alignment >= static_cast<int32_t>(TextAlignment::Left) && alignment <= static_cast<int32_t>(TextAlignment::Right))
                            {
                                m_DashboardConfig.Elements.CurrentGearText.Alignment = static_cast<TextAlignment>(alignment);
                            }
                        }

                        YAML::Node positionNode = node["Position"];
                        if (positionNode)
                        {
                            if (positionNode["X"]) m_DashboardConfig.Elements.CurrentGearText.Position.x = positionNode["X"].as<float>();
                            if (positionNode["Y"]) m_DashboardConfig.Elements.CurrentGearText.Position.y = positionNode["Y"].as<float>();
                        }
                    }
                }
            }
        }

        m_Logger.Info("Loaded %s.", k_Name);
    }
    catch (const std::exception& e)
    {
        m_Logger.Warning("Failed to load %s - %s", k_Name, e.what());
    }
}

void DashboardConfigFile::Save() const
{
    try
    {
        m_Logger.Info("Saving %s to file '%s' ...", k_Name, m_FilePath.GetPath());

        Core::File file(m_FilePath.GetPath(), Core::File::Mode::Write);
        YAML::Node yaml;
        {
            yaml["AlwaysVisible"] = m_DashboardConfig.AlwaysVisible;
            yaml["MetricUnits"] = m_DashboardConfig.MetricUnits;
            yaml["Opacity"] = m_DashboardConfig.Opacity;
            yaml["Scale"] = m_DashboardConfig.Scale;

            YAML::Node elementsNode;

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Enabled;
                node["Color"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Color;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Position.y;
                node["Position"] = positionNode;

                YAML::Node sizeNode;
                sizeNode["X"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Size.x;
                sizeNode["Y"] = m_DashboardConfig.Elements.SpeedBackgroundTexture.Size.y;
                node["Size"] = sizeNode;

                elementsNode["SpeedBackgroundTexture"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.SpeedDialTexture.Enabled;
                node["Color"] = m_DashboardConfig.Elements.SpeedDialTexture.Color;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.SpeedDialTexture.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.SpeedDialTexture.Position.y;
                node["Position"] = positionNode;

                YAML::Node sizeNode;
                sizeNode["X"] = m_DashboardConfig.Elements.SpeedDialTexture.Size.x;
                sizeNode["Y"] = m_DashboardConfig.Elements.SpeedDialTexture.Size.y;
                node["Size"] = sizeNode;

                elementsNode["SpeedDialTexture"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Enabled;
                node["Color"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Color;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Position.y;
                node["Position"] = positionNode;

                YAML::Node sizeNode;
                sizeNode["X"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Size.x;
                sizeNode["Y"] = m_DashboardConfig.Elements.RPMBackgroundTexture.Size.y;
                node["Size"] = sizeNode;

                elementsNode["RPMBackgroundTexture"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.RPMDialTexture.Enabled;
                node["Color"] = m_DashboardConfig.Elements.RPMDialTexture.Color;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.RPMDialTexture.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.RPMDialTexture.Position.y;
                node["Position"] = positionNode;

                YAML::Node sizeNode;
                sizeNode["X"] = m_DashboardConfig.Elements.RPMDialTexture.Size.x;
                sizeNode["Y"] = m_DashboardConfig.Elements.RPMDialTexture.Size.y;
                node["Size"] = sizeNode;

                elementsNode["RPMDialTexture"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.RPMNeedle.Enabled;
                node["Color"] = m_DashboardConfig.Elements.RPMNeedle.Color;
                node["Thickness"] = m_DashboardConfig.Elements.RPMNeedle.Thickness;
                node["InnerRadius"] = m_DashboardConfig.Elements.RPMNeedle.InnerRadius;
                node["OuterRadius"] = m_DashboardConfig.Elements.RPMNeedle.OuterRadius;
                node["MinAngle"] = m_DashboardConfig.Elements.RPMNeedle.MinAngle;
                node["MaxAngle"] = m_DashboardConfig.Elements.RPMNeedle.MaxAngle;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.RPMNeedle.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.RPMNeedle.Position.y;
                node["Position"] = positionNode;

                elementsNode["RPMNeedle"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.SpeedNeedle.Enabled;
                node["Color"] = m_DashboardConfig.Elements.SpeedNeedle.Color;
                node["Thickness"] = m_DashboardConfig.Elements.SpeedNeedle.Thickness;
                node["InnerRadius"] = m_DashboardConfig.Elements.SpeedNeedle.InnerRadius;
                node["OuterRadius"] = m_DashboardConfig.Elements.SpeedNeedle.OuterRadius;
                node["MinAngle"] = m_DashboardConfig.Elements.SpeedNeedle.MinAngle;
                node["MaxAngle"] = m_DashboardConfig.Elements.SpeedNeedle.MaxAngle;

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.SpeedNeedle.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.SpeedNeedle.Position.y;
                node["Position"] = positionNode;

                elementsNode["SpeedNeedle"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.SpeedText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.SpeedText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.SpeedText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.SpeedText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.SpeedText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.SpeedText.Position.y;
                node["Position"] = positionNode;

                elementsNode["SpeedText"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.TripMeterText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.TripMeterText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.TripMeterText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.TripMeterText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.TripMeterText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.TripMeterText.Position.y;
                node["Position"] = positionNode;

                elementsNode["TripMeterText"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.OdometerText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.OdometerText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.OdometerText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.OdometerText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.OdometerText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.OdometerText.Position.y;
                node["Position"] = positionNode;

                elementsNode["OdometerText"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.RPMText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.RPMText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.RPMText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.RPMText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.RPMText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.RPMText.Position.y;
                node["Position"] = positionNode;

                elementsNode["RPMText"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.LocalTimeText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.LocalTimeText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.LocalTimeText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.LocalTimeText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.LocalTimeText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.LocalTimeText.Position.y;
                node["Position"] = positionNode;

                elementsNode["LocalTimeText"] = node;
            }

            {
                YAML::Node node;
                node["Enabled"] = m_DashboardConfig.Elements.CurrentGearText.Enabled;
                node["Color"] = m_DashboardConfig.Elements.CurrentGearText.Color;
                node["TextSize"] = m_DashboardConfig.Elements.CurrentGearText.TextSize;
                node["Alignment"] = static_cast<int32_t>(m_DashboardConfig.Elements.CurrentGearText.Alignment);

                YAML::Node positionNode;
                positionNode["X"] = m_DashboardConfig.Elements.CurrentGearText.Position.x;
                positionNode["Y"] = m_DashboardConfig.Elements.CurrentGearText.Position.y;
                node["Position"] = positionNode;

                elementsNode["CurrentGearText"] = node;
            }

            yaml["Elements"] = elementsNode;
        }
        file.Write(YAML::Dump(yaml));

        m_Logger.Info("Saved %s.", k_Name);
    }
    catch (const std::exception& e)
    {
        m_Logger.Warning("Failed to save %s - %s", k_Name, e.what());
    }
}

DashboardConfig& DashboardConfigFile::GetDashboardConfig()
{
    return m_DashboardConfig;
}
