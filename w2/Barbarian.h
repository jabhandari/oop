#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.cpp"
#include<iostream>
#include "character.h"

namespace seneca {
	
	template<typename T,typename Ability_t,typename Weapon_t>
	class Barbarian : public CharacterTpl<T> {
	private:
		int m_baseDefense;
		int m_baseAttack;
		Ability_t m_ability;
		Weapon_t primaryWeapon;
		Weapon_t secondaryWeapon;

	public:
		Barbarian(const char* name, int healthMax, int baseAttack,
			int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon);

		int getAttackAmnt() const;

		int getDefenseAmnt() const;

		Character* clone() const {
			return new Barbarian<T, Ability_t, Weapon_t>(*this);
		}

		void attack(Character* enemy) override { //over
			std::cout << this->getName() << " is attacking "
				<< enemy->getName() << "." << std::endl;

			m_ability.useAbility(this);
			int damage = getAttackAmnt();
			m_ability.transformDamage(damage);
			std::cout << "Barbarian deals " << damage <<
				"melee damage!" << std::endl;
		}
		void takeDamage(int dmg);


	};
	
}

#endif // !SENECA_BARBARIAN_H
