//
// Created by kyle on 3/17/21.
//

#pragma once

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBFLUIDSYNTH

#include <fluidsynth.h>

#include "fl_settings.hh"

namespace fl
{

class FluidSynthObject
{
    fluid_synth_t *m_ptr;

  public:
    explicit FluidSynthObject(FluidSynthSettings *);
    ~FluidSynthObject();
    FluidSynthObject(FluidSynthObject &&);
    FluidSynthObject &operator=(FluidSynthObject &&);

    const fluid_synth_t *get() const;
    fluid_synth_t *get();
};

} // namespace fl

#endif
