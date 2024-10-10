#pragma once
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include <iostream>

namespace seneca {

    template <typename T>
    class characterTpl : public Character {

    private:
        int m_healthMax;
        T m_health; 

    public:
        characterTpl(const char* name, int healthMax)
            : Character(name) {
            m_healthMax = healthMax;
            m_health = m_healthMax;
        }

        void takeDamage(int dmg) override {
            m_health -= dmg;
            //if (m_health< 0) 
            if (getHealth() <= 0) {
                m_health = 0; 
                std::cout << getName() << " has been defeated!" << std::endl;
            }
            else {
                std::cout << getName() << " took " << dmg
                    << " damage, " << getHealth()
                    << " health remaining." << std::endl;
            }
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override {
            return m_healthMax;
        }

        void setHealth(int health) override {
            m_health = static_cast<int>(health);
            if (m_health < 0) {
                m_health = static_cast<int>(0);
            }
        }

        void setHealthMax(int health) override {
            m_healthMax = health;
           m_health=health; 
        }
    };

} // namespace seneca

#endif // SENECA_CHARACTERTPL_H