//
// Created by kyle on 3/16/21.
//

#pragma once

class actionf_t
{
    void (*m_v)();

    enum class D
    {
        v,
    };

    D m_d;

  public:
    actionf_t(void (*v)()) : m_v(v), m_d(D::v)
    {
    }
};
