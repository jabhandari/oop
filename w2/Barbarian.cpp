#include "Barbarian.h"
#include "characterTpl.h"
#include<iostream>
#include "character.h"
namespace seneca {

   

    template<typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
        : CharacterTpl<T>(name, healthMax),
        m_baseAttack(baseAttack),
        m_baseDefense(baseDefense),
        m_primaryWeapon(primaryWeapon),
        m_secondaryWeapon(secondaryWeapon) {}  // Save the weapons individually


    template<typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const
    {
        int result= m_baseAttack + static_cast<int>(m_primaryWeapon) / 2
            + static_cast<int>(m_secondaryWeapon) / 2;
        return result;
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const
    {
        return m_baseDefense;
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg)
    {
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

        dmg -= m_baseDefense;
        if (dmg < 0) {
            dmg = 0;
        }
        m_ability.transformDamageReceived(dmg);

        characterTpl<T>::takeDamage(dmg);
    }

}
