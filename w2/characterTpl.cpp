#ifndef SENECA_CHARACTER_H
#define SENECA_CHARACTER_H

#include<iostream>
#include<string>
#include "character.h"
namespace seneca {

	template<typename T>
	class CharacterTpl : public Character {
	private:
		int m_healthMax;
		T m_health;

	public:
		CharacterTpl(cont char* name, int healthMax) :
			chatacter(name), m_healthMax(healthMax), m_health(healthMax) {}
		void takeDamage(int dmg) override {
			m_health - +static_cast<T>(dmg);
			if (!isAlive()) {
				std::cout << getName() << "has been defeated!" << std::endl;
			}
			else {
				std::cout << getName() << " took " << dmg << " damage, " <<
					static_cast<int>(m_health) << " health remaining." << std::endl;
			}
		}

		int getHealth() const override {
			return static_cast<int>m_health;
		}

		int getHealthMax() const override {
			return m_healthMax;
		}

		void setHealth(int health) override {
			m_health = static_cast<T>(health);
			if (m_health > m_healthMax) {
				m_health = static_cast<T>(m_healthMax);
			}
		}

		void setHealthMax(int health) override {
			m_healthMax = health;
			if (m_health > m_healthMax) {
				m_health = static_cast<T>(m_healthMax);
			}
		}
	};



	

}
#endif // !SENECA_CHARACTER_H
