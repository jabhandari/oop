#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca {

    class Guild {
        size_t m_size;
        size_t m_capacity;
        Character** m_members;
        std::string m_name;


    public:
        Guild();

        Guild(const char* name);

        Guild(const Guild& other);

        Guild& operator=(const Guild& other);

        Guild(Guild&& other) noexcept;

        Guild& operator=(Guild&& other) noexcept;

        ~Guild();

        void addMember(Character* c);

        void removeMember(const std::string& c);

        Character* operator[](size_t idx) const;

        void showMembers() const;
    };
} // namespace seneca

#endif