#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <cstring>
#include "character.h" 
#include <string>

namespace seneca {

	class Team {
	private:
		Character** m_members;
		size_t m_size{};
		size_t m_capacity{};
		std::string m_name;

	public:
		void resize(size_t newCapacity);
		Team();
		Team(const char* name);
		~Team();
		Team(const Team& other);
		Team(Team&& other) noexcept;
		Team& operator=(const Team& other);
		Team& operator=(Team&& other) noexcept;
		void addMember(const Character* c);
		void removeMember(const std::string& name);
		Character* operator[](size_t idx) const;
		void showMembers() const;
	};

}
#endif