//
// Created by kyle on 3/17/21.
//

#include "fl_settings.hh"
fl::FluidSynthSettings::FluidSynthSettings() noexcept
{
    m_ptr = new_fluid_settings();
}
fl::FluidSynthSettings::~FluidSynthSettings() noexcept
{
    if (m_ptr != nullptr)
    {
        delete_fluid_settings(m_ptr);
    }
}
fl::FluidSynthSettings::FluidSynthSettings(fl::FluidSynthSettings &&other) noexcept
    : m_ptr(other.m_ptr)
{
    other.m_ptr = nullptr;
}
fl::FluidSynthSettings &fl::FluidSynthSettings::operator=(
    fl::FluidSynthSettings &&other) noexcept
{
    if (&other != this)
    {
        if (m_ptr != nullptr)
        {
            delete_fluid_settings(m_ptr);
        }
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    return *this;
}
const fluid_settings_t *fl::FluidSynthSettings::get() const
{
    return m_ptr;
}
fluid_settings_t *fl::FluidSynthSettings::get()
{
    return m_ptr;
}
