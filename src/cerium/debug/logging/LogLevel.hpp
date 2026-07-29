#ifndef CERIUM_DEBUG_LOGGING_LOGLEVEL_HPP_
#define CERIUM_DEBUG_LOGGING_LOGLEVEL_HPP_

#include <string>

enum class LogLevel { Debug, Info, Warn, Error, Fatal };

std::string logLevelToString(LogLevel level);

#endif // CERIUM_DEBUG_LOGGING_LOGLEVEL_HPP_
