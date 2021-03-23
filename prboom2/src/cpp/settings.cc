//
// Created by kyle on 3/22/21.
//

#include "m_random.hh"

#include "settings.hh"

bool normally_distributed_damage;
int damage_multiplier;
int health_pickup_multiplier;
int armor_pickup_multiplier;
int ammo_pickup_multiplier;
int health_regeneration;

int normalDamage(int base)
{
    constexpr double sigma = 10.0;
    return std::normal_distribution<double>(base, sigma)(random_device);
}
