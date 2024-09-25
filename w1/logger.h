#pragma once
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include<iostream>
#include "event.h"
namespace seneca {
	class Logger {
		Event* m_events = NULL;
		size_t m_size = 0;
		size_t m_capacity = 0;

	public:
		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger(Logger&&) noexcept;
		Logger& operator=(Logger&&) noexcept;

		void addEvent(const Event& event);

		friend std::ostream& operator<<(std::ostream& os,const Logger& logger);

	};
}
#endif