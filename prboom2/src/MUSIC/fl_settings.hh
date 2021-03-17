//
// Created by kyle on 3/17/21.
//

#pragma once

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBFLUIDSYNTH

#include <fluidsynth.h>

namespace fl
{

class FluidSynthSettings
{
    fluid_settings_t *m_ptr;

  public:
    [[nodiscard]] FluidSynthSettings() noexcept;
    ~FluidSynthSettings() noexcept;
    [[nodiscard]] FluidSynthSettings(FluidSynthSettings &&) noexcept;
    [[nodiscard]] FluidSynthSettings &operator=(FluidSynthSettings &&) noexcept;

    [[nodiscard]] const fluid_settings_t *get() const;
    [[nodiscard]] fluid_settings_t *get();
};

} // namespace fl

#endif
