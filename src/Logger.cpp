#include "Logger.h"

Logger::Logger()
{
    rewind();
}

Logger::~Logger()
{
    m_log.clear();
}

void Logger::push(std::string text)
{
    m_log.push_back(text);
    while (m_log.size() > LOG_BUFFER_SIZE)
    {
        m_log.erase(m_log.begin());
    }
}

void Logger::rewind()
{
    m_it = m_log.rbegin();
}

bool Logger::pop(std::string& logText)
{
    if (m_log.rend() == m_it)
    {
        return false;
    }
    else
    {
        logText = *m_it;
        m_it++;
        return true;
    }
}

void Logger::clear()
{
    m_log.clear();
    rewind();
}




