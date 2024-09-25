#define _CRT_SECURE_NO_WARNINGS
#include "logger.h"
#include<utility>
namespace seneca {
	seneca::Logger::Logger() : m_events(nullptr), m_size(0), m_capacity(0) {}

	Logger::~Logger()
	{
		delete[] m_events;
	}

	Logger::Logger(Logger&& src) noexcept
	{
		*this = std::move(src);

	}

	Logger& Logger::operator=(Logger&& src) noexcept
	{
		if (this != &src) {
			m_events = std::move(src.m_events);
			m_size = src.m_size;
			m_capacity = src.m_capacity;

			src.m_size= 0;
			src.m_capacity = 0;
		}
		return *this;
	}


	void Logger::addEvent(const Event& event) {
		
		if (m_size >= m_capacity) {
			size_t new_capacity = m_capacity ? m_capacity * 2 : 1;
			Event* new_events = new Event[new_capacity];
			for (size_t i = 0; i < m_size; ++i) {
				new_events[i] = std::move(m_events[i]);
			}
			delete[] m_events;
			m_events = new_events;
			m_capacity = new_capacity;
		}
		m_events[m_size++] = event;
		
	}


	std::ostream& operator<<(std::ostream& os, const Logger& logger)
	{
		for (size_t i = 0; i < logger.m_size; ++i) {
			os << logger.m_events[i] ;/////endl
		}
		return os;
	}
	

}

