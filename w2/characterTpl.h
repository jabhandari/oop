#pragma once
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
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
		characterTpl(int healthMax) :
		m_healthMax(healthMax), m_health(healthMax) {}

		void takeDamage(int dmg) override;

		int getHealth() const override;

		int getHealthMax() const override;

		void setHealth(int health) override;

		void setHealthMax(int health) override;
	};
}
#endif