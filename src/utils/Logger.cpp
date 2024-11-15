#include "Logger.h"

#include <format>
#include <ctime>
#include <iostream>

Logger Log{};

Logger::Logger()
{
        m_file = std::ofstream(BASE_PATH "/logs/latest-0.log");
        if (!m_file)
                throw std::runtime_error("Could not open log file.");
}

Logger::~Logger()
{
        m_file.close();
}

std::string Logger::_time()
{
        char buffer[80]{};
        time_t rawTime{};

        // Get time as formatted string
        std::time(&rawTime);
        std::tm tm{};
        localtime_s(&tm, &rawTime);
        std::strftime(buffer, sizeof(buffer), "%X", &tm);

        return buffer;
}

Logger::fatal_error::fatal_error(
        const std::string &message
) {
        // MAcro mainly used for disabling during tests.
#ifndef LOGGER_FATAL_ERROR_DISABLE_STDOUT
        std::cout << message << std::endl;
#endif // LOGGER_FATAL_ERROR_DISABLE_STDOUT

        // Flush (std::endl) forces to print everything that has not yet been printed.
        Log.m_file << message << std::endl;
}
