#define _CRT_SECURE_NO_WARNINGS
#include "timeMonitor.h"
#include<chrono>
namespace seneca {

void seneca::TimeMonitor::startEvent(const char* name)
{
	m_start = std::chrono::steady_clock::now();
	m_eventName = name;
}

Event TimeMonitor::stopEvent()
{
	m_stop = std::chrono::steady_clock::now();
	std::chrono::nanoseconds duration=(m_stop - m_start);
	return Event(m_eventName.c_str(), duration);
}

}
