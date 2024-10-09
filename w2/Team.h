#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <cstring>
#include "character.h" // Ensure Character class is defined
#include <string>

namespace seneca {

	class Team {
	private:
		Character** m_members;
		size_t m_size;
		size_t m_capacity;
		std::string m_name;

	public:
		Team() : m_members(nullptr), m_size(0), m_capacity(0), m_name("Unnamed Team") {}
		Team(const char* name);
		//Destructor
		~Team();
		// Copy constructor
		Team(const Team& other);
		// Move constructor
		Team(Team&& other) noexcept;
		// Copy assignment operator
		Team& operator=(const Team& other);
		// Move assignment operator
		Team& operator=(Team&& other) noexcept;
		void addMember(const Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;
	};

}
#endif