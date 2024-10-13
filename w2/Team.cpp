#include "team.h"
namespace seneca {

    seneca::Team::Team() {
        m_name = ""; ///
        m_members = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    seneca::Team::Team(const char* name)
    {
        m_name = name;/// 
        m_members = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    seneca::Team::~Team()
    {
        if (m_members) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
        }
    }

    seneca::Team::Team(const Team& other) {
        m_name = other.m_name;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        m_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            m_members[i] = other.m_members[i]->clone();
        }
    }


    Team& seneca::Team::operator=(const Team& other)
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
    seneca::Team::Team(Team&& other) noexcept {
        m_name = (std::move(other.m_name));
        m_members = other.m_members;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Team& seneca::Team::operator=(Team&& other) noexcept
    {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }
    void Team::resize(size_t newCapacity) {

        Character** temp = new Character * [newCapacity];

        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }

        delete[] m_members;

        m_members = temp;
        m_capacity = newCapacity;
    }
    void Team::addMember(const Character* c)
    {

        if (!c) return;

        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;
            }
        }

        if (m_size >= m_capacity) {
            resize(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        m_members[m_size++] = c->clone();
       
    }


    void Team::removeMember(const std::string& name)
    {
        size_t idx = 0;
        while (idx < m_size && m_members[idx]->getName() != name) {
            ++idx;
        }
        if (idx < m_size) {
            delete m_members[idx];
            m_members[idx] = nullptr;
            Character** temp = new Character * [m_size - 1];
            for (size_t i = 0u; i < idx; ++i) {
                temp[i] = m_members[i];
            }
            for (size_t i = idx; i < m_size; ++i) {
                temp[i] = m_members[i + 1];
                m_members = temp;
                --m_size;
            }
        }

       /* for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i];
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }*/
    }

    Character* Team::operator[](size_t idx) const
    {
        return (idx <= m_size) ? m_members[idx] : nullptr;
    }
    void Team::showMembers() const
    {

        if (m_size == 0) {
            std::cout << "No team." << std::endl;
            return;
        }
        std::cout << "[Team] " << m_name << std::endl;
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
        }
    }
}