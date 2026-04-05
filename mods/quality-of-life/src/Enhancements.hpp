#pragma once


#include "core/Logger.hpp"
#include "core/Patch.hpp"

#include "FeaturesFile.hpp"


class Enhancements
{
public:
    Enhancements(const Core::Logger& logger, EnhancementsFeatures& enhancementsFeatures);

public:
    void Load();
    void Unload();

private:
    const Core::Logger& m_Logger;
    EnhancementsFeatures& m_EnhancementsFeatures;

    Core::Patch m_PatchAnyVehicleTypeOnline[2];
    Core::Patch m_PatchDisableInfiniteGears;
};
