#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include<iostream>
#include"characterTpl.h"
#include "character.h"
#include "health.h"
namespace seneca {

	template<typename Weapon_t>
	class Archer : public characterTpl<seneca::SuperHealth> {
		//<seneca::SuperHealth>
	private:
		int	m_baseDefense;
		int m_baseAttack;
		Weapon_t m_weapon;
	public:
		Archer(const char* name, int healthMax, int attack, int defense, Weapon_t weapon)
			: characterTpl(name, healthMax) {
			m_baseAttack = attack;
			m_baseDefense = defense;
			m_weapon = weapon;
		}


		int getAttackAmnt() const {
			return static_cast<int>(1.3 * m_baseAttack);
		}

		int getDefenseAmnt() const {
			return static_cast<int>(1.2 * m_baseDefense);
		}
		Character* clone() const override {
			//return new Archer<Weapon_t>(*this);
			return new Archer(*this);
		}


		void attack(Character* enemy) override {
			std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

			int damage = getAttackAmnt();
			std::cout << "    Archer deals " << damage
				<< " ranged damage!" << std::endl;
			enemy->takeDamage(damage);
		}


		void takeDamage(int dmg) override {
			std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Archer has a defense of " << getDefenseAmnt()
				<< ". Reducing damage received." << std::endl;

			dmg -= getDefenseAmnt();
			if (dmg < 0) {
				dmg = 0;
			}

			characterTpl::takeDamage(dmg); //<superhealth>
		}


	};
}

#endif