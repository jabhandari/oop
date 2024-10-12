#include "guild.h"

namespace seneca {


    seneca::Guild::Guild() {
        m_members = nullptr;
        m_size = 0;
        m_capacity = 0;
        m_name = ("");

    }

    seneca::Guild::Guild(const char* name) {
        m_members=nullptr;
        m_size=0;
        m_capacity = 0;
        m_name = name;}

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
        m_name=other.m_name;

        m_members = new Character*[m_capacity]; 
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

            m_members = new Character*[m_capacity];

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
    void Guild::resize(size_t newCapacity)
    {
        if (newCapacity < m_size) {
            m_size = newCapacity; 
        }

        Character** temp = new Character*[newCapacity]; 

        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }

        delete[] m_members;

        m_members = temp;
        m_capacity = newCapacity;
    }
    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_members[i] == c)
            {
                return;
            }
        }

        if (m_size == m_capacity)
        {
            resize(m_capacity == 0 ? 2 : m_capacity * 2);
        }

        int newMaxHealth = c->getHealthMax() + 300;
        c->setHealthMax(newMaxHealth);
        m_members[m_size++] = c;
    }

    void Guild::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_members[i]->getName() == c)
            {
                int newMaxHealth = m_members[i]->getHealthMax() - 300;
                m_members[i]->setHealthMax(newMaxHealth);
                for (size_t j = i; j < m_size - 1; ++j)
                {
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