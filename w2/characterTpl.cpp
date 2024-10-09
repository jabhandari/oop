#include<iostream>
#include<string>
#include "character.h"
namespace seneca {

	template<typename T>
	class characterTpl : public Character {
	private:
		int m_healthMax;
		T m_health;

	public:
		characterTpl(T m_health, int healthMax) :
			, m_healthMax(healthMax), m_health(healthMax) {}
		//Character(name)
		void takeDamage(int dmg) override { ////
			m_health -= static_cast<T>(dmg);
			if (!isAlive()) {
				std::cout << getName() << " has been defeated!" << std::endl;
			}
			else {
				std::cout << getName() << " took " << dmg << " damage, " <<
					static_cast<int>(m_health) << " health remaining." << std::endl;
			}
		}

		int getHealth() const override {
			return static_cast<int>(m_health);
		}

		int getHealthMax() const override {
			return m_healthMax;
		}

		void setHealth(int health) override {
			m_health = static_cast<T>(health);
			
		}

		void setHealthMax(int health) override {
			m_healthMax = health;
			m_health = health;
		}
	};
}
