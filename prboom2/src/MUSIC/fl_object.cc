//
// Created by kyle on 3/17/21.
//

#include "fl_object.hh"

fl::FluidSynthObject::FluidSynthObject(fl::FluidSynthSettings *settings)
{
    m_ptr = new_fluid_synth(settings->get());
}
fl::FluidSynthObject::~FluidSynthObject()
{
    if (m_ptr != nullptr)
    {
        delete_fluid_synth(m_ptr);
    }
}
fl::FluidSynthObject::FluidSynthObject(fl::FluidSynthObject &&other)
{
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}
fl::FluidSynthObject &fl::FluidSynthObject::operator=(
    fl::FluidSynthObject &&other
)
{
    if (&other != this)
    {
        if (m_ptr != nullptr)
        {
            delete_fluid_synth(m_ptr);
        }

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    return *this;
}
const fluid_synth_t *fl::FluidSynthObject::get() const
{
    return m_ptr;
}
fluid_synth_t *fl::FluidSynthObject::get()
{
    return m_ptr;
}
