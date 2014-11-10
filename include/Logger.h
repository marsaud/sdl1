#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

#define LOG_BUFFER_SIZE     50

class Logger
{
public:
    Logger();
    virtual ~Logger();

    void push(std::string const text);
    void rewind();
    bool pop(std::string & logText);
    void clear();
protected:
private:
    std::vector<std::string> m_log;
    std::vector<std::string>::reverse_iterator m_it;
};

#endif // LOGGER_H
