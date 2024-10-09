#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include<iostream>
#include"characterTpl.h"
#include "character.h"
namespace seneca {

	template<typename Weapon_t>
	class Archer :public CharacterTpl<int> {//<seneca::SuperHealth>
	private:
		int	m_baseDefense;
		int m_baseAttack;
		Weapon_t m_weapon;
	public:
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon) :
			CharacterTpl<SuperHealth>(name, healthMax),
			m_baseAttack(baseAttack),
			m_baseDefense(baseDefense),
			m_weapon(weapon) {}

		int getAttackAmnt() const;

		int getDefenseAmnt() const;
		Character* clone() const override;
			

		void attack(Character* enemy) override;
			

		void takeDamage(int dmg) override;

		
	};

	

	

}





#endif