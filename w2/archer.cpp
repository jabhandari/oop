#include "archer.h"
#include "characterTpl.h"
#include<iostream>

namespace seneca {


	template<typename Weapon_t>
	 int Archer<Weapon_t>::getAttackAmnt() const
	{
		return static_cast<int>(1.3 * m_baseAttack);
	}
	
	template<typename Weapon_t>
	 int Archer<Weapon_t>::getDefenseAmnt() const
	{
			return static_cast<int>(1.2 * m_baseDefense);
	}
	
	template<typename Weapon_t>
	 Character* seneca::Archer<Weapon_t>::clone() const
	{
		return new Archer<Weapon_t>(*this);
	}

	template<typename Weapon_t>
	void Archer<Weapon_t>::attack(Character* enemy)
	{
		std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

		int damage = getAttackAmnt();
		std::cout << "    Archer deals " << damage
			<< " ranged damage!" << std::endl;
		enemy->takeDamage(damage);
	}

	template<typename Weapon_t>
	void seneca::Archer<Weapon_t>::takeDamage(int dmg)
	{
		std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
		std::cout << "    Archer has a defense of " << getDefenseAmnt()
			<< ". Reducing damage received." << std::endl;

		dmg -= getDefenseAmnt();
		if (dmg < 0) {
			dmg = 0;
		}

		CharacterTpl<int>::takeDamage(dmg); //<superhealth>
	}

}