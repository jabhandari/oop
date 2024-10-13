#include "guild.h"

namespace seneca {


    seneca::Guild::Guild() {
        m_members = nullptr;
        m_size = 0;
        m_capacity = 0;
        m_name = ("");

    }

    seneca::Guild::Guild(const char* name) {
        m_members = nullptr;
        m_size = 0;
        m_capacity = 0;
        m_name = name;
    }

    seneca::Guild::~Guild()
    {

        if (m_members) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
        }
    }
    seneca::Guild::Guild(const Guild& other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_name = other.m_name;

        m_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone();
        }

    }
    seneca::Guild::Guild(Guild&& other) noexcept {
        m_members = other.m_members;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_name = std::move(other.m_name);

        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Guild& seneca::Guild::operator=(const Guild& other)
    {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            m_members = new Character * [m_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }


    Guild& seneca::Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other) {

            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_members = other.m_members;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_name = std::move(other.m_name);

            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }
    void Guild::resize()
    {
        size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        Character** newMembers = new Character * [newCapacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            newMembers[i] = m_members[i];
        }

        delete[] m_members;
        m_members = newMembers;
        m_capacity = newCapacity;
    }


    void Guild::addMember(Character* c) {
         if (!c) return;
         for (size_t i = 0; i < m_size; ++i) {
             if (m_members[i]->getName() == c->getName())
             {
                 return;
             }
         }
         if (m_size >= m_capacity) {
             resize();
         }
         c->setHealthMax(c->getHealthMax() + 300);
         m_members[m_size++] = c->clone();
         
    }   
   
   
    void Guild::removeMember(const std::string& name) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == name) {
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                delete m_members[i];
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }
    }

    Character* Guild::operator[](size_t idx) const
    {
        if (idx >= m_size) {
            return nullptr;
        }
        return m_members[idx];
    }

    void Guild::showMembers() const
    {
        if (m_members == nullptr) {
            std::cout << "No guild." << std::endl;
            return;
        }
        std::cout << "[Guild] " << m_name << std::endl;
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
        }


    }
}