#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "character.h"
#include "weapons.h"
#include <iostream>
#include <cmath>

namespace seneca {

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue : public characterTpl<T> { 
	private:
		int m_baseDefense;
		int m_baseAttack;
		FirstAbility_t m_firstAbility;
		SecondAbility_t m_secondAbility;
		seneca::Dagger m_weapon;

	public:
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) :
			
			characterTpl<T>(name, healthMax) {
			m_baseAttack=baseAttack;
			m_baseDefense=baseDefense;
		}

		int getAttackAmnt() const {
			
			int weaponDamage = static_cast<int>(std::floor(static_cast<double>(m_weapon)));
			return m_baseAttack + 2 * weaponDamage + 1;

		}
		int getDefenseAmnt() const {
			return m_baseDefense;
		}
		Character* clone() const {
			return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
		}
		void attack(Character* enemy) {
			std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
			m_firstAbility.useAbility(this);
			m_secondAbility.useAbility(this);
			int damage = getAttackAmnt();
			m_firstAbility.transformDamageDealt(damage);
			m_secondAbility.transformDamageDealt(damage);
			std::cout << "    Rogue deals " << damage << " melee damage!" << std::endl;
			enemy->takeDamage(damage);
		}


		void takeDamage(int dmg) {
			std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Rogue has a defense of " << getDefenseAmnt()
				<< ". Reducing damage received." << std::endl;

			dmg -= getDefenseAmnt();
			if (dmg < 0) {
				dmg = 0; 
			}

			m_firstAbility.transformDamageReceived(dmg);
			m_secondAbility.transformDamageReceived(dmg);
			characterTpl<T>::takeDamage(dmg);
		}
	};

}



#endif
