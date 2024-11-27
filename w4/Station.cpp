#include "Station.h"
#include<iomanip>

namespace seneca {
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;
    seneca::Station::Station(const std::string& record)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
        m_quantity = std::stoul(util.extractToken(record, next_pos, more));
        m_description = util.extractToken(record, next_pos, more);

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }

        m_id = ++id_generator;
    }

    const std::string& seneca::Station::getItemName() const
    {
        return m_name;
    }

    size_t seneca::Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    size_t seneca::Station::getQuantity() const
    {
        return m_quantity;
    }

    void seneca::Station::updateQuantity()
    {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void seneca::Station::display(std::ostream& os, bool full) const
    {
        //os << std::setw(3) << std::setfill('0') << m_id << " | ";

        //// Display the item name left-aligned and padded with spaces
        //os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << " | ";

        //// Display the serial number right-aligned and padded with zeros
        //os << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";

        //if (full) {
        //    // Display the quantity right-aligned and padded with spaces
        //    os << std::setw(4) << std::right << std::setfill(' ') << m_quantity << " | ";

        //    // Display the description as-is
        //    os << m_description;
        //}

        os << std::setw(3) << std::setfill('0') << m_id << " | ";
        os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << " | ";

        os << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::right << std::setfill(' ') << m_quantity << " | ";
            os << m_description;
        }
        os << std::endl;
    }

}