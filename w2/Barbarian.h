#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include<iostream>
#include "characterTpl.h"
#include "character.h"

namespace seneca {
	
	template<typename T,typename Ability_t,typename Weapon_t>
	class Barbarian : public characterTpl<T> {
	private:
		int m_baseDefense;
		int m_baseAttack;
		Ability_t m_ability;
		Weapon_t m_primaryWeapon;
		Weapon_t m_secondaryWeapon;

	public:
		Barbarian(const char* name, int healthMax, int baseAttack,
			int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon) : characterTpl<T>(name, healthMax)
			 {
			m_baseAttack=baseAttack;
			m_baseDefense=baseDefense;
			m_primaryWeapon=primaryWeapon;
			m_secondaryWeapon=secondaryWeapon;
		}

		/// 
		Barbarian(const Barbarian& other) : characterTpl<T>(other) {
			m_baseAttack = other.m_baseAttack;
			m_baseDefense = other.m_baseDefense;
			m_primaryWeapon = other.m_primaryWeapon;  // Ensure Weapon_t supports deep copy if needed
			m_secondaryWeapon = other.m_secondaryWeapon;
			m_ability = other.m_ability;              // Ensure Ability_t supports deep copy if needed
		}

		///

		int getAttackAmnt() const {
			int result = m_baseAttack + static_cast<double > (m_primaryWeapon) / 2
				+ static_cast<double>(m_secondaryWeapon) / 2;
			return result;
		}


		int getDefenseAmnt() const {
			return m_baseDefense;
		}

		Character* clone() const {
			return new Barbarian<T, Ability_t, Weapon_t>(*this);
		}

		void attack(Character* enemy) override { //over
			std::cout << this->getName() << " is attacking "
				<< enemy->getName() << "." << std::endl;

			m_ability.useAbility(this);
			int damage = getAttackAmnt();
			m_ability.transformDamageDealt(damage);
			std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}
		void takeDamage(int dmg) override {
			std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

			dmg -= m_baseDefense;
			if (dmg < 0) {
				dmg = 0;
			}
			m_ability.transformDamageReceived(dmg);

			characterTpl<T>::takeDamage(dmg);
		}


	};
	
}

#endif // !SENECA_BARBARIAN_H
