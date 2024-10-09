#include "team.h"
namespace seneca {


    seneca::Team::Team(const char* name) :
        m_members(nullptr),
        m_size(0),
        m_capacity(0),
        m_name(name) {}

    seneca::Team::~Team()
    {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i]; 
        }
        delete[] m_members;
    }

    seneca::Team::Team(const Team& other) :
        m_size(other.m_size),
        m_capacity(other.m_capacity),
        m_name(other.m_name){
        m_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone(); 
        }
    }

    seneca::Team::Team(Team&& other) noexcept :
        m_members(other.m_members),
        m_size(other.m_size),
        m_capacity(other.m_capacity),
        m_name(std::move(other.m_name)) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
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

    Team& seneca::Team::operator=(Team&& other) noexcept
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
    void Team::addMember(const Character* c)
    {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                std::cout << "Character already in team." << std::endl;
                return;
            }
        }
        if (m_size >= m_capacity) {
            size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            Character** newArray = new Character * [newCapacity];
            for (size_t i = 0; i < m_size; ++i) {
                newArray[i] = m_members[i]; 
            }
            delete[] m_members; 
            m_members = newArray; 
            m_capacity = newCapacity; 
        }

        m_members[m_size++] = c->clone();
    }
    void Team::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i];
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }
        std::cout << "Character not found." << std::endl;
    }

    Character* Team::operator[](size_t idx) const
    {
        if (idx >= m_size) {
            return nullptr;
        }
        return m_members[idx];
    }
    void Team::showMembers() const
    {
        std::cout << "[Team] " << m_name << std::endl;
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
            return;
        }
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << "    " << (i + 1)
                << ": " << *m_members[i] << std::endl;
        }
    }
}