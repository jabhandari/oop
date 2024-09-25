#define _CRT_SECURE_NO_WARNINGS
#include "event.h"
#include "settings.h"
#include<chrono>
#include<iomanip>
#include<string>
///
namespace seneca {
    seneca::Event::Event(const char* name, const std::chrono::nanoseconds& duration)
    {
        m_name = name;
        m_duration = duration;
    }

   
    std::ostream& operator<<(std::ostream& os, const Event& event)
    {   
            static int counter = 0;
            counter++;

            long long duration_value;
            int field_size;
            if (g_settings.m_time_units == "seconds") {
                duration_value = std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count();
                field_size = 2;
            }
            else if (g_settings.m_time_units == "milliseconds") {
                duration_value = std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count();
                field_size = 5;
            }
            else if (g_settings.m_time_units == "microseconds") {
                duration_value = std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count();
                field_size = 8;
            }
            else {
                duration_value = event.m_duration.count();
                field_size = 11;
            }

            os << std::right << std::setw(2) << counter << ": "
                << std::right << std::setw(40) << event.m_name << " -> "
                << std::right << std::setw(field_size) << duration_value << " "
                << g_settings.m_time_units << "\n";

            return os;

        
    }

}
