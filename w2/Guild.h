#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <cstring>
#include <string>
#include "character.h"  

namespace seneca {

	class Guild {
	private:
		Character** m_members;   
		size_t m_size;           
		size_t m_capacity;       
		std::string m_name;

	public:
		Guild();
		Guild(const char* name);
		~Guild();
		Guild(const Guild& other);
		Guild(Guild&& other) noexcept;
		// Copy assignment operator
		Guild& operator=(const Guild& other);
		Guild& operator=(Guild&& other) noexcept;
		
		void addMember(Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;

	};
}
#endif // !SENECA_GUILD_H
